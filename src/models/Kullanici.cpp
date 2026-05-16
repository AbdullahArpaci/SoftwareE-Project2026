#include "Kullanici.h"
#include <databasemanager.h>
#include <QSqlQuery>
#include <QVariant>

Kullanici::Kullanici() {
    aktif = true;
}

Kullanici::~Kullanici() {
}

// --- SETTER METOTLARININ İÇERİKLERİ ---
void Kullanici::setKullaniciID(int id) { kullaniciID = id; }
void Kullanici::setKimlikNo(QString kimlik) { kimlikNo = kimlik; }
void Kullanici::setAd(QString a) { ad = a; }
void Kullanici::setSoyad(QString s) { soyad = s; }
void Kullanici::setRol(QString r) { rol = r; }

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

        return true;
    }
    return false;
}

void Kullanici::cikisYap() {
    kullaniciID = 0;
    kimlikNo = "";
}

QString Kullanici::kimlikNoGetir() {
    return kimlikNo;
}

QString Kullanici::rolGetir() {
    return rol;
}
