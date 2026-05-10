#include <databasemanager.h>


DataBaseManager::DataBaseManager(){
    db = QSqlDatabase::addDatabase("QSQLITE");
}

DataBaseManager* DataBaseManager::instance = nullptr;

DataBaseManager* DataBaseManager::getInstance()
{
    if(instance == nullptr){
        instance = new DataBaseManager();
    }

    return instance;
}

bool DataBaseManager::connect(const QString& yol){
    db.setDatabaseName(yol);

    if(!db.open()){
        qDebug() << "Veritabanı bağlantı hatası" << db.lastError().text();
        return false;
    }

    qDebug() <<"Veri tabanına bağlanıldı";
    return true;
}

void DataBaseManager::disconnect(){
    if(db.isOpen()){
        db.close();
        qDebug() << "Veritabanı bağlantısı kapatıldı.";
    } else {
        qDebug() << "Zaten bağlantı yok.";
    }
}

DataBaseManager::~DataBaseManager(){
    disconnect();
}

QSqlQuery DataBaseManager::execute(const QString& sql){
    QSqlQuery sorgu(db);

    if(!sorgu.exec(sql)){
        qDebug() << "Sorgu hatası:" << sorgu.lastError().text();
    }

    return sorgu;
}

void DataBaseManager::beginTransaction(){
    if(db.transaction()){
        qDebug() << "Transaction başlatıldı.";
    } else {
        qDebug() << "Transaction hatası:" << db.lastError().text();
    }
}

void DataBaseManager::commit(){
    if(db.commit()){
        qDebug() << "Commit başarılı, değişiklikler kaydedildi.";
    } else {
        qDebug() << "Commit hatası:" << db.lastError().text();
    }
}

void DataBaseManager::rollback(){
    if(db.rollback()){
        qDebug() << "Rollback yapıldı, işlem geri alındı.";
    } else {
        qDebug() << "Rollback hatası:" << db.lastError().text();
    }
}

bool DataBaseManager::isConnected() const {
    return db.isOpen();
}