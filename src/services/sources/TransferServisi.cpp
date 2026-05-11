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

    if (hesapSrv.bakiyeKontrol(gonderen, tutar))
    {
        if (hesapSrv.bakiyeGuncelle(gonderen, -tutar) && hesapSrv.bakiyeGuncelle(alici, tutar))
        {
            db->commit();

            QString detay = QString("%1 nolu hesaptan %2 nolu hesaba %3 TL tutarinda transfer basariyla gerceklestirildi.")
                                .arg(gonderen)
                                .arg(alici)
                                .arg(tutar);

            // TODO(Abdullah/Durancan): Buradaki 0 (kullaniciID degeri) temsili olarak verilmistir. Gonderen hesabin sahibinin gercek ID sini veritabanindan veya nesneden cekilerek buraya eklenmeli.
            logSrv.logKaydet(0, "Para Transferi", detay);

            return true;
        }
    }

    db->rollback();
    return false;
}
