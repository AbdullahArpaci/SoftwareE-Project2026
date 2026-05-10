#include "TransferServisi.h"
#include "HesapServisi.h"
#include "VeritabaniYoneticisi.h"
#include "LogServisi.h"
#include <QSqlQuery>

TransferServisi::TransferServisi() {}
TransferServisi::~TransferServisi() {}

bool TransferServisi::aliciHesapDogrula(QString hesapNo) {
    VeritabaniYoneticisi* db = VeritabaniYoneticisi::getInstance();
    QString sql = "SELECT * FROM HESAP WHERE hesapNo = '" + hesapNo + "' AND aktif = 1";
    QSqlQuery query = db->sorguCalistir(sql);
    return query.next();
}

bool TransferServisi::transferYap(QString gonderen, QString alici, double tutar) {
    VeritabaniYoneticisi* db = VeritabaniYoneticisi::getInstance();
    HesapServisi hesapSrv;
    LogServisi logSrv;

    if (!aliciHesapDogrula(alici) || tutar <= 0) return false;

    db->transactionBaslat();

    if (hesapSrv.bakiyeKontrol(gonderen, tutar)) {
        if (hesapSrv.bakiyeGuncelle(gonderen, -tutar) && hesapSrv.bakiyeGuncelle(alici, tutar)) {
            db->commit();

            QString detay = QString("%1 nolu hesaptan %2 nolu hesaba %3 TL tutarında transfer başarıyla gerçekleştirildi.")
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
