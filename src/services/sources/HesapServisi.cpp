#include "HesapServisi.h"
#include "VeritabaniYoneticisi.h"
#include "Hesap.h"
#include <QSqlQuery>
#include <QVariant>

HesapServisi::HesapServisi() {}
HesapServisi::~HesapServisi() {}

bool HesapServisi::bakiyeKontrol(QString hesapNo, double tutar) {
    VeritabaniYoneticisi* db = VeritabaniYoneticisi::getInstance();
    if(tutar <= 0) return false;
    QString sql = "SELECT bakiye FROM HESAP WHERE hesapNo = '" + hesapNo + "'";
    QSqlQuery query = db->sorguCalistir(sql);
    if (query.next()) {
        double mevcutBakiye = query.value(0).toDouble();
        return (mevcutBakiye >= tutar);
    }
    return false;
}

bool HesapServisi::bakiyeGuncelle(QString hesapNo, double fark) {
    VeritabaniYoneticisi* db = VeritabaniYoneticisi::getInstance();
    QString sql = QString("UPDATE HESAP SET bakiye = bakiye + (%1) WHERE hesapNo = '%2'").arg(fark).arg(hesapNo);
    QSqlQuery query = db->sorguCalistir(sql);
    return query.numRowsAffected() > 0;
}

Hesap* HesapServisi::hesapOlustur(int kullaniciID, QString tip) {
    // TODO(Abdullah): Veritabanina yeni hesap ekleme sorgusu burada yapilmali.
    // TODO(Durancan): Hesap sinifindan (veya Factory uzerinden) yeni bir nesne olusturup dondurme islemi buraya eklenmeli.
    return nullptr;
}

bool HesapServisi::hesapKapat(QString hesapNo) {
    VeritabaniYoneticisi* db = VeritabaniYoneticisi::getInstance();
    QString sql = "UPDATE HESAP SET aktif = 0 WHERE hesapNo = '" + hesapNo + "' AND bakiye = 0";
    QSqlQuery query = db->sorguCalistir(sql);
    return query.numRowsAffected() > 0;
}
