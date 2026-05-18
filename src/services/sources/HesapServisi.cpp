#include "HesapServisi.h"
#include "databasemanager.h"
#include "Hesap.h"
#include <QSqlQuery>
#include <QVariant>

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
    // TODO(Abdullah): Veritabanina yeni hesap ekleme sorgusu burada yapilmali.
    // TODO(Durancan): Hesap sinifindan (veya Factory uzerinden) yeni bir nesne olusturup dondurme islemi buraya eklenmeli.
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
