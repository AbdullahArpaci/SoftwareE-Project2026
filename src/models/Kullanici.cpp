#include "Kullanici.h"
#include <databasemanager.h>
#include <QSqlQuery>
#include <QVariant>

Kullanici::Kullanici() {
    aktif = true;
}

Kullanici::~Kullanici() {
}

bool Kullanici::girisYap() {

    QSqlQuery query;
    query.prepare("SELECT * FROM KULLANICI WHERE kimlik_no = :kimlik_no AND sifre_hash = :sifre_hash AND aktif = 1");
    query.bindValue(":kimlik_no", kimlikNo);
    query.bindValue(":sifre_hash", sifreHash);

    if(query.exec() && query.next()) {
        kullaniciID = query.value("kullanici_id").toInt();
        ad = query.value("ad").toString();
        soyad = query.value("soyad").toString();
        rol = query.value("rol").toString();

        // TODO (Yusuf): SistemKontrolcusu tarafında oturum açma işlemleri devam etmeli.
        return true;
    }
    return false;
}

void Kullanici::cikisYap() {
    // TODO (Yusuf): SistemKontrolcusu::oturumKapat() çağrılacak.
    kullaniciID = 0;
    kimlikNo = "";
}

QString Kullanici::kimlikNoGetir() {
    return kimlikNo;
}

QString Kullanici::rolGetir() {
    return rol;
}
