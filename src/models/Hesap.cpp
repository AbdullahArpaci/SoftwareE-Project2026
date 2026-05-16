#include "Hesap.h"
#include <databasemanager.h>
#include <QSqlQuery>
#include <QVariant>

Hesap::Hesap() {
    bakiye = 0.0;
    donduruldu = false;
    aktif = true;
}

Hesap::~Hesap() {
}

bool Hesap::paraYatir(double miktar) {
    if (miktar <= 0 || donduruldu) return false;

    QSqlQuery query;
    query.prepare("UPDATE HESAP SET bakiye = bakiye + :miktar WHERE hesap_no = :hesap_no");
    query.bindValue(":miktar", miktar);
    query.bindValue(":hesap_no", hesapNo);

    if(query.exec()) {
        bakiye += miktar;
        return true;
    }
    return false;
}

bool Hesap::paraCek(double miktar) {
    // TODO (Yusuf): Bu işlem öncesi HesapServisi::bakiyeKontrol çalışmalı
    if (miktar <= 0 || bakiye < miktar || donduruldu) return false;

    QSqlQuery query;
    query.prepare("UPDATE HESAP SET bakiye = bakiye - :miktar WHERE hesap_no = :hesap_no");
    query.bindValue(":miktar", miktar);
    query.bindValue(":hesap_no", hesapNo);

    if(query.exec()) {
        bakiye -= miktar;
        return true;
    }
    return false;
}

double Hesap::bakiyeGetir() {
    return bakiye;
}

QList<Islem*> Hesap::islemleriAl() {
    QList<Islem*> liste;
    // TODO: ISLEM tablosundan bu hesap_no'ya ait işlemler çekilecek.
    return liste;
}

bool Hesap::dondurulduMu() {
    return donduruldu;
}
