#include "Yonetici.h"
#include "../database/databasemanager.h"
#include <QSqlQuery>
#include <QVariant>

Yonetici::Yonetici() {
    rol = "yonetici";
}

Yonetici::~Yonetici() {
}

bool Yonetici::musteriEkle(Musteri* musteri) {
    QSqlQuery query;
    query.prepare("INSERT INTO KULLANICI (kimlik_no, ad, soyad, email, telefon, sifre_hash, rol) "
                  "VALUES (:kimlik, :ad, :soyad, :email, :tel, :sifre, 'musteri')");

    query.bindValue(":kimlik", musteri->kimlikNoGetir());
    // TODO (Yusuf): Müşteri nesnesindeki diğer veriler de buraya bind edilecek.

    return query.exec();
}

bool Yonetici::hesabiDondur(QString hesapNo) {
    QSqlQuery query;
    query.prepare("UPDATE HESAP SET donduruldu = 1 WHERE hesap_no = :hesap_no");
    query.bindValue(":hesap_no", hesapNo);

    return query.exec();
}

bool Yonetici::musteriProfiliGuncelle(int id) {
    // TODO: Arayüzden gelecek verilere göre UPDATE sorgusu yazılacak.
    return true;
}

QList<Islem*> Yonetici::tumKayitlariGoruntule() {
    QList<Islem*> liste;
    // TODO: LOG_KAYIT tablosundan tüm sistem logları çekilecek.
    return liste;
}

bool Yonetici::krediDegerlendir(int krediID, bool onay) {
    QSqlQuery query;
    QString durum = onay ? "onaylandi" : "reddedildi";

    query.prepare("UPDATE KREDI SET durum = :durum WHERE kredi_id = :kredi_id");
    query.bindValue(":durum", durum);
    query.bindValue(":kredi_id", krediID);

    return query.exec();
}
