#include "HesapServisi.h"
#include "databasemanager.h"
#include "Hesap.h"
#include <QSqlQuery>
#include <QVariant>
#include <QSqlError>
#include <QDebug>
#include <QDateTime> // Otomatik hesap no üretimi için eklendi

HesapServisi::HesapServisi()
{
}

HesapServisi::~HesapServisi()
{
}

bool HesapServisi::bakiyeKontrol(QString hesapNo, double tutar)
{
    DataBaseManager* db = DataBaseManager::getInstance();
    if(tutar <= 0) return false;

    QSqlQuery query(db->getDatabase());
    query.prepare("SELECT bakiye FROM HESAP WHERE hesap_no = :no");
    query.bindValue(":no", hesapNo);

    qDebug() << "Bakiye kontrol - Hesap:" << hesapNo << "İstenen:" << tutar;

    if (query.exec() && query.next()) {
        double mevcutBakiye = query.value(0).toDouble();
        qDebug() << "Bulunan bakiye:" << mevcutBakiye;
        qDebug() << "Yeterli mi:" << (mevcutBakiye >= tutar);
        return (mevcutBakiye >= tutar);
    }

    qDebug() << "Hesap bulunamadı!";
    qDebug() << "Sorgu hatası:" << query.lastError().text();
    return false;
}

bool HesapServisi::bakiyeGuncelle(QString hesapNo, double fark)
{
    DataBaseManager* db = DataBaseManager::getInstance();

    QSqlQuery query;
    query.prepare("UPDATE HESAP SET bakiye = bakiye + :fark WHERE hesap_no = :no");
    query.bindValue(":fark", fark);
    query.bindValue(":no", hesapNo);

    return query.exec();
}

Hesap* HesapServisi::hesapOlustur(int kullaniciID, QString tip)
{
    DataBaseManager* db = DataBaseManager::getInstance();

    // Yeni bir hesap numarası üretiyoruz (Örn: TR + O anki zamanın milisaniyesi)
    QString yeniHesapNo = QString("TR%1").arg(QDateTime::currentMSecsSinceEpoch());

    // TODO(Abdullah): Veritabanina yeni hesap ekleme sorgusu burada yapilmali. (Durancan tarafından test için tamamlandı)
    QSqlQuery query(db->getDatabase());
    query.prepare("INSERT INTO HESAP (hesap_no, kullanici_id, hesap_tipi, bakiye, para_birimi, aktif, donduruldu) "
                  "VALUES (:hesap_no, :kullanici_id, :hesap_tipi, 0.0, 'TRY', 1, 0)");
    query.bindValue(":hesap_no", yeniHesapNo);
    query.bindValue(":kullanici_id", kullaniciID);
    query.bindValue(":hesap_tipi", tip);

    if (query.exec()) {
        // --- DURANCAN: Hesap sınıfından nesne oluşturup döndürme ---
        // TODO(Durancan): Veritabanına kayıt başarılıysa, yeni Hesap nesnesi oluşturulup bilgileri atanarak döndürüldü.
        Hesap* yeniHesap = new Hesap();
        yeniHesap->setHesapNo(yeniHesapNo);
        yeniHesap->setKullaniciID(kullaniciID);
        yeniHesap->setHesapTipi(tip);
        yeniHesap->setBakiye(0.0);
        yeniHesap->setParaBirimi("TRY");

        qDebug() << "Yeni hesap başarıyla oluşturuldu:" << yeniHesapNo;
        return yeniHesap;
    }

    qDebug() << "Hesap oluşturulamadı:" << query.lastError().text();
    return nullptr;
}

bool HesapServisi::hesapKapat(QString hesapNo)
{
    DataBaseManager* db = DataBaseManager::getInstance();

    QSqlQuery query;
    query.prepare("UPDATE HESAP SET aktif = 0 WHERE hesap_no = :no AND bakiye = 0");
    query.bindValue(":no", hesapNo);

    return query.exec();
}

bool HesapServisi::paraYatir(QString hesapNo, double tutar)
{
    if(tutar <= 0) return false;

    DataBaseManager* db = DataBaseManager::getInstance();
    db->beginTransaction();

    if (bakiyeGuncelle(hesapNo, tutar)) {
        QSqlQuery islemSorgu(db->getDatabase());
        islemSorgu.prepare(
            "INSERT INTO ISLEM (gonderici_hesap, alici_hesap, tutar, islem_tipi, durum, aciklama) "
            "VALUES (:hesap, :hesap, :tutar, 'yatirma', 'tamamlandi', 'Şubeden para yatırma')"
            );
        islemSorgu.bindValue(":hesap", hesapNo);
        islemSorgu.bindValue(":tutar", tutar);

        if (islemSorgu.exec()) {
            db->commit();
            return true;
        }
    }

    db->rollback();
    return false;
}

bool HesapServisi::paraCek(QString hesapNo, double tutar)
{
    if(tutar <= 0) return false;

    DataBaseManager* db = DataBaseManager::getInstance();

    if (!bakiyeKontrol(hesapNo, tutar)) return false;

    db->beginTransaction();

    if (bakiyeGuncelle(hesapNo, -tutar)) {
        QSqlQuery islemSorgu(db->getDatabase());
        islemSorgu.prepare(
            "INSERT INTO ISLEM (gonderici_hesap, alici_hesap, tutar, islem_tipi, durum, aciklama) "
            "VALUES (:hesap, :hesap, :tutar, 'cekme', 'tamamlandi', 'ATM üzerinden para çekme')"
            );
        islemSorgu.bindValue(":hesap", hesapNo);
        islemSorgu.bindValue(":tutar", tutar);

        if (islemSorgu.exec()) {
            db->commit();
            return true;
        }
    }

    db->rollback();
    return false;
}
