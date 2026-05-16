#include "LogServisi.h"
#include "databasemanager.h"
#include <QSqlQuery>
#include <QVariant>

LogServisi::LogServisi()
{
}

LogServisi::~LogServisi()
{
}

bool LogServisi::logKaydet(int kullaniciID, QString olayTipi, QString detaylar)
{
    DataBaseManager* db = DataBaseManager::getInstance();

    QSqlQuery query;

    query.prepare("INSERT INTO LOG_KAYIT (kullanici_id, olay_tipi, detaylar) VALUES (:id, :olay, :detay)");
    query.bindValue(":id", kullaniciID);
    query.bindValue(":olay", olayTipi);
    query.bindValue(":detay", detaylar);

    // TODO(Abdullah): Kullanicinin gercek IP adresi network arayuzunden tespit edilip buradaki sorguya sonradan eklenebilir
    return query.exec();
}
