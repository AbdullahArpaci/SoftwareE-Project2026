#include "SistemKontrolcusu.h"
#include "databasemanager.h"
#include "LogServisi.h"
#include "Hesap.h"
#include "Islem.h"
#include <mutex>
#include <QSqlQuery>
#include <QVariant>

std::mutex islemMutex;

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
        int kullaniciID = query.value("kullanici_id").toInt();
        QString mesaj = QString("%1 kimlik numarali kullanici sisteme giris yapti.").arg(kimlikNo);
        logSrv.logKaydet(kullaniciID, "Giris Basarili", mesaj);

        // TODO(Durancan): Veritabanindan gelen verilerle uygun Kullanici, Musteri veya Yonetici nesnesini olusturup (veya Factory uzerinden uretip) burada dondurulmeli.
        return nullptr;
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
