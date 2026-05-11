#include "Musteri.h"
#include "../database/databasemanager.h"
#include <QSqlQuery>
#include <QVariant>

Musteri::Musteri() {
    rol = "musteri";
}

Musteri::~Musteri() {
}

void Musteri::profilGoruntule() {
    // TODO (Yusuf/Abdullah): Arayüze müşterinin bilgileri (ad, soyad, email) gönderilecek.
}

QList<Hesap*> Musteri::hesapDetaylariAl() {
    // TODO: HESAP tablosundan bu müşteriye ait (kullanici_id) hesaplar QList'e doldurulup döndürülecek.
    return hesaplar;
}

void Musteri::hesapEkle(Hesap* hesap) {
    hesaplar.append(hesap);
}
