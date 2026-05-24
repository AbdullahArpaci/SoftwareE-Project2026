#include <QApplication>
#include "databasemanager.h"
#include "LoginWindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Veritabanı bağlantısı
    DataBaseManager* db = DataBaseManager::getInstance();
    db->connect(QCoreApplication::applicationDirPath() + "/banka.sqlite");

    // Hangi yolda bağlandı görelim
    qDebug() << "DB Yolu:" << QCoreApplication::applicationDirPath() + "/banka.sqlite";

    // Kullanıcıları listele
    QSqlQuery test = db->execute("SELECT kimlik_no, sifre_hash FROM KULLANICI");
    while(test.next()) {
        qDebug() << test.value(0).toString() << test.value(1).toString();
    }

    // Login ekranını aç
    LoginWindow w;
    w.show();

    return a.exec();
}