#include "Musteri.h"
#include <databasemanager.h>
#include <QSqlQuery>
#include <QVariant>
#include <QSqlError>
#include <QDebug>

Musteri::Musteri() {
    rol = "musteri";
}

Musteri::~Musteri() {
    // Bellek sızıntısını önlemek için listedeki hesap nesnelerini temizliyoruz
    qDeleteAll(hesaplar);
    hesaplar.clear();
}

int Musteri::kullaniciIDGetir() const {
    return kullaniciID;
}

void Musteri::profilGoruntule() {
    // TODO (Yusuf/Abdullah): Arayüze müşterinin bilgileri (ad, soyad, email) gönderilecek.
}

// --- YUSUF'UN TODO NOTUNA GÖRE DOLDURULAN SEÇKİN METOT ---
QList<Hesap*> Musteri::hesapDetaylariAl() {
    // Mükerrer kayıt olmaması için mevcut listeyi temizleyip veritabanından güncel hali çekiyoruz
    qDeleteAll(hesaplar);
    hesaplar.clear();

    DataBaseManager* db = DataBaseManager::getInstance();
    QSqlQuery query;

    // Abdullah'ın sütun isimleri ve bindValue kuralına tam uyum
    query.prepare("SELECT * FROM HESAP WHERE kullanici_id = :kullanici_id AND aktif = 1");
    query.bindValue(":kullanici_id", kullaniciID);

    if (query.exec()) {
        while (query.next()) {
            Hesap* h = new Hesap();
            h->setHesapNo(query.value("hesap_no").toString());
            h->setKullaniciID(query.value("kullanici_id").toInt());
            h->setHesapTipi(query.value("hesap_tipi").toString());
            h->setBakiye(query.value("bakiye").toDouble());
            h->setParaBirimi(query.value("para_birimi").toString());

            hesaplar.append(h);
        }
    } else {
        qDebug() << "Hesaplar yuklenirken hata olustu:" << query.lastError().text();
    }

    return hesaplar;
}

void Musteri::hesapEkle(Hesap* hesap) {
    hesaplar.append(hesap);
}
