#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>


class DataBaseManager{
public:
    DataBaseManager();
    bool connect();

private:
    QSqlDatabase db;
};




#endif // DATABASEMANAGER_H
