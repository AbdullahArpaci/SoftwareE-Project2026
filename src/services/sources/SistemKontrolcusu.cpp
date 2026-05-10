#include "SistemKontrolcusu.h"
#include "VeritabaniYoneticisi.h"
#include "LogServisi.h"
#include "Hesap.h"
#include "Islem.h"
#include <mutex>

std::mutex islemMutex;

SistemKontrolcusu::SistemKontrolcusu() {
    hesapServisi = new HesapServisi();
    transferServisi = new TransferServisi();
}

SistemKontrolcusu::~SistemKontrolcusu() {
    delete hesapServisi;
    delete transferServisi;
}

Kullanici* SistemKontrolcusu::kullaniciDogrula(QString kimlikNo, QString sifre) {
    VeritabaniYoneticisi* db = VeritabaniYoneticisi::getInstance();
    LogServisi logSrv;

    QString sql = "SELECT * FROM KULLANICI WHERE kimlikNo = '" + kimlikNo + "' AND sifreHash = '" + sifre + "'";
    QSqlQuery query = db->sorguCalistir(sql);

    if (query.next()) {

        int kullaniciID = query.value("kullaniciID").toInt();
        QString mesaj = QString("%1 kimlik numaralı kullanıcı sisteme giriş yaptı.").arg(kimlikNo);
        logSrv.logKaydet(kullaniciID, "Giriş Başarılı", mesaj);

        // TODO(Durancan): Veritabanindan gelen verilerle uygun Kullanici,Müşteri veya Yönetici nesnesini olusturup (veya Factory uzerinden uretip) burada dondurulmeli.
        return nullptr;
    } else {

        QString hataMesaji = QString("%1 kimlik numarası ile hatalı giriş denemesi yapıldı.").arg(kimlikNo);
        logSrv.logKaydet(0, "Hatalı Giriş", hataMesaji);

        return nullptr;
    }
}

bool SistemKontrolcusu::islemYonet(Hesap* hesap, Islem* islem) {
    std::lock_guard<std::mutex> lock(islemMutex);
    VeritabaniYoneticisi* db = VeritabaniYoneticisi::getInstance();
    db->transactionBaslat();
    if (islem->islemGerceklestir()) {
        db->commit();
        return true;
    }
    db->rollback();
    return false;
}

void SistemKontrolcusu::oturumKapat() {}
