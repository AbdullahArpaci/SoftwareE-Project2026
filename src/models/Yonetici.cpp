#include "Yonetici.h"
#include <databasemanager.h>
#include <QSqlQuery>
#include <QVariant>
#include <QSqlError>
#include <QDebug>

Yonetici::Yonetici() {
    rol = "yonetici";
}

Yonetici::~Yonetici() {
}

int Yonetici::kullaniciIDGetir() const {
    return kullaniciID;
}

bool Yonetici::musteriEkle(Musteri* musteri) {
    DataBaseManager* db = DataBaseManager::getInstance();
    QSqlQuery query;
    query.prepare("INSERT INTO KULLANICI (kimlik_no, ad, soyad, email, telefon, sifre_hash, rol) "
                  "VALUES (:kimlik, :ad, :soyad, :email, :tel, :sifre, 'musteri')");

    query.bindValue(":kimlik", musteri->kimlikNoGetir());
    query.bindValue(":ad", musteri->getAd());
    query.bindValue(":soyad", musteri->getSoyad());
    query.bindValue(":email", musteri->getEmail());
    query.bindValue(":tel", musteri->getTelefon());
    query.bindValue(":sifre", musteri->getSifreHash());

    return query.exec();
}

bool Yonetici::hesabiDondur(QString hesapNo) {
    DataBaseManager* db = DataBaseManager::getInstance();
    QSqlQuery query;
    query.prepare("UPDATE HESAP SET donduruldu = 1 WHERE hesap_no = :hesap_no");
    query.bindValue(":hesap_no", hesapNo);

    return query.exec();
}

bool Yonetici::musteriProfiliGuncelle(int id) {
    DataBaseManager* db = DataBaseManager::getInstance();
    QSqlQuery query;
    // TODO: Arayüzden gelecek verilere göre UPDATE sorgusu özelleştirilecek. Şimdilik temel örnek.
    query.prepare("UPDATE KULLANICI SET aktif = 1 WHERE kullanici_id = :id");
    query.bindValue(":id", id);
    return query.exec();
}

QList<Islem*> Yonetici::tumKayitlariGoruntule() {
    QList<Islem*> liste;
    DataBaseManager* db = DataBaseManager::getInstance();
    QSqlQuery query;

    // Log kayıtlarını en yeniden en eskiye doğru çekiyoruz
    query.prepare("SELECT * FROM LOG_KAYIT ORDER BY zaman_damgasi DESC");

    if (query.exec()) {
        while (query.next()) {
            Islem* log = new Islem();
            // TODO (Takım): Islem sınıfı veya yeni bir Log sınıfı üzerinden bu veriler (olay_tipi, detaylar vb.) nesneye doldurulabilir.
            liste.append(log);
        }
    } else {
        qDebug() << "Log kayitlari cekilirken hata:" << query.lastError().text();
    }

    return liste;
}

bool Yonetici::krediDegerlendir(int krediID, bool onay) {
    DataBaseManager* db = DataBaseManager::getInstance();
    QSqlQuery query;
    QString durum = onay ? "onaylandi" : "reddedildi";

    // SQL dosyasındaki yapıya tam uygun kredi güncelleme sorgusu
    query.prepare("UPDATE KREDI SET durum = :durum, onay_tarihi = datetime('now') WHERE kredi_id = :kredi_id");
    query.bindValue(":durum", durum);
    query.bindValue(":kredi_id", krediID);

    return query.exec();
}
