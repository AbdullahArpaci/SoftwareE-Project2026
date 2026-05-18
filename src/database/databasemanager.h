#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>


class DataBaseManager{
public:
    static DataBaseManager* getInstance();
    bool connect(const QString& yol);
    void disconnect();
    QSqlQuery execute(const QString& sql);
    void beginTransaction();
    void commit();
    void rollback();
    bool isConnected() const;
    QSqlDatabase getDatabase() const { return db; }
private:
    DataBaseManager();
    ~DataBaseManager();
    static DataBaseManager* instance;
    QSqlDatabase db;
};




#endif // DATABASEMANAGER_H
