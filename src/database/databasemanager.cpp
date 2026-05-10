#include <databasemanager.h>


DataBaseManager::DataBaseManager(){
    connect();
}

bool DataBaseManager::connect(){
    db = QSqlDatabase::addDatabase("QSQLite");
    db.setDatabaseName("banka.db");

    if(db.isOpen() == false){
        qDebug() << "Veritabanı bağlantı hatası" << db.lastError().text();
        return false;
    }

    qDebug() <<"Veri tabanına bağlanıldı";
    return true;
}
