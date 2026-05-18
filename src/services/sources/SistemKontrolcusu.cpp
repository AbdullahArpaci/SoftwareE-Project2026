#include "SistemKontrolcusu.h"
#include "databasemanager.h"
#include "LogServisi.h"
#include "Hesap.h"
#include "Islem.h"
#include "Musteri.h"
#include "Yonetici.h"
#include <mutex>
#include <QSqlQuery>
#include <QVariant>

std::mutex islemMutex;

// Singleton ornegi baslangicta nullptr olmali
SistemKontrolcusu* SistemKontrolcusu::instance = nullptr;

SistemKontrolcusu* SistemKontrolcusu::getInstance()
{
    if (instance == nullptr)
    {
        instance = new SistemKontrolcusu();
    }
    return instance;
}

SistemKontrolcusu::SistemKontrolcusu()
{
    hesapServisi = new HesapServisi();
    transferServisi = new TransferServisi();
}

SistemKontrolcusu::~SistemKontrolcusu()
{
    delete hesapServisi;
    delete transferServisi;
}

Kullanici* SistemKontrolcusu::kullaniciDogrula(QString kimlikNo, QString sifre)
{
    DataBaseManager* db = DataBaseManager::getInstance();
    LogServisi logSrv;

    QSqlQuery query;
    query.prepare("SELECT * FROM KULLANICI WHERE kimlik_no = :kimlik AND sifre_hash = :sifre AND aktif = 1");
    query.bindValue(":kimlik", kimlikNo);
    query.bindValue(":sifre", sifre);

    if (query.exec() && query.next())
    {
        int     kullaniciID = query.value("kullanici_id").toInt();
        QString rol         = query.value("rol").toString();
        QString ad          = query.value("ad").toString();
        QString soyad       = query.value("soyad").toString();
        QString kimlik      = query.value("kimlik_no").toString();

        QString mesaj = QString("%1 kimlik numarali kullanici sisteme giris yapti.").arg(kimlikNo);
        logSrv.logKaydet(kullaniciID, "Giris Basarili", mesaj);

        Kullanici* aktifKullanici = nullptr;

        if (rol == "yonetici") {
            aktifKullanici = new Yonetici();
        } else {
            aktifKullanici = new Musteri();
        }

        // Setter'ları çağır
        aktifKullanici->setKullaniciID(kullaniciID);
        aktifKullanici->setKimlikNo(kimlik);
        aktifKullanici->setAd(ad);
        aktifKullanici->setSoyad(soyad);
        aktifKullanici->setRol(rol);

        return aktifKullanici;
    }
    else
    {
        QString hataMesaji = QString("%1 kimlik numarasi ile hatali giris denemesi yapildi.").arg(kimlikNo);
        logSrv.logKaydet(0, "Hatali Giris", hataMesaji);

        return nullptr;
    }
}

bool SistemKontrolcusu::islemYonet(Hesap* hesap, Islem* islem)
{
    std::lock_guard<std::mutex> lock(islemMutex);
    DataBaseManager* db = DataBaseManager::getInstance();

    db->beginTransaction();

    if (islem->islemGerceklestir())
    {
        db->commit();
        return true;
    }

    db->rollback();
    return false;
}

void SistemKontrolcusu::oturumKapat()
{
}
