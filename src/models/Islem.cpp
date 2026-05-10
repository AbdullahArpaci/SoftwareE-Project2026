#include "Islem.h"
#include "../database/databasemanager.h"
#include <QSqlQuery>
#include <QVariant>

Islem::Islem() {
    durum = "beklemede";
    zamanDamgasi = QDateTime::currentDateTime();
}

Islem::~Islem() {
}

bool Islem::islemGerceklestir() {
    QSqlQuery query;
    query.prepare("INSERT INTO ISLEM (gonderici_hesap, alici_hesap, tutar, islem_tipi, durum, aciklama) "
                  "VALUES (:gonderici, :alici, :tutar, :tip, :durum, :aciklama)");

    query.bindValue(":gonderici", gonderenHesapNo);
    query.bindValue(":alici", aliciHesapNo);
    query.bindValue(":tutar", tutar);
    query.bindValue(":tip", islemTipi);
    query.bindValue(":durum", "tamamlandi");
    query.bindValue(":aciklama", aciklama);

    return query.exec();
}

QString Islem::durumGetir() {
    return durum;
}

// --- Transfer Sınıfı ---

Transfer::Transfer() {
    islemTipi = "Transfer";
}

Transfer::~Transfer() {
}

bool Transfer::transferYap() {
    // TODO (Yusuf): TransferServisi::transferYap metodu çağrılarak DataBaseManager::beginTransaction() ve commit() işlemleri yönetilecek.
    return true;
}
