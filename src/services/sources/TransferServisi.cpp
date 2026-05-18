#include "TransferServisi.h"
#include "HesapServisi.h"
#include "databasemanager.h"
#include "LogServisi.h"
#include <QSqlQuery>
#include <QVariant>

TransferServisi::TransferServisi()
{
}

TransferServisi::~TransferServisi()
{
}

bool TransferServisi::aliciHesapDogrula(QString hesapNo)
{
    DataBaseManager* db = DataBaseManager::getInstance();

    QSqlQuery query;
    query.prepare("SELECT * FROM HESAP WHERE hesap_no = :no AND aktif = 1");
    query.bindValue(":no", hesapNo);

    return query.exec() && query.next();
}

bool TransferServisi::transferYap(QString gonderen, QString alici, double tutar)
{
    DataBaseManager* db = DataBaseManager::getInstance();
    HesapServisi hesapSrv;
    LogServisi logSrv;

    if (!aliciHesapDogrula(alici) || tutar <= 0) return false;

    db->beginTransaction();

    if (hesapSrv.bakiyeKontrol(gonderen, tutar)) {
        if (hesapSrv.bakiyeGuncelle(gonderen, -tutar) &&
            hesapSrv.bakiyeGuncelle(alici, tutar)) {

            QSqlQuery islemSorgu;
            islemSorgu.prepare(
                "INSERT INTO ISLEM "
                "(gonderici_hesap, alici_hesap, tutar, islem_tipi, durum, aciklama) "
                "VALUES (:gonderen, :alici, :tutar, 'transfer', 'tamamlandi', 'Para transferi')"
                );
            islemSorgu.bindValue(":gonderen", gonderen);
            islemSorgu.bindValue(":alici",    alici);
            islemSorgu.bindValue(":tutar",    tutar);
            islemSorgu.exec();

            db->commit();

            QString detay = QString("%1 hesabından %2 hesabına %3 TL transfer.")
                                .arg(gonderen).arg(alici).arg(tutar);
            logSrv.logKaydet(0, "Para Transferi", detay);
            return true;
        }
    }

    db->rollback();
    return false;
}