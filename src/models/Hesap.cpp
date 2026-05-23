#include "Hesap.h"
#include <databasemanager.h>
#include <QSqlQuery>
#include <QVariant>
#include <QSqlError>
#include <QDebug>

Hesap::Hesap() {
    bakiye = 0.0;
    donduruldu = false;
    aktif = true;
}

Hesap::~Hesap() {
}

// --- SETTER VE GETTER METOTLARININ İÇERİKLERİ ---
void Hesap::setHesapNo(QString no) { hesapNo = no; }
void Hesap::setKullaniciID(int id) { kullaniciID = id; }
void Hesap::setHesapTipi(QString tip) { hesapTipi = tip; }
void Hesap::setBakiye(double b) { bakiye = b; }
void Hesap::setParaBirimi(QString pb) { paraBirimi = pb; }
QString Hesap::hesapNoGetir() { return hesapNo; }

bool Hesap::paraYatir(double miktar) {
    if (miktar <= 0 || donduruldu) return false;

    QSqlQuery query;
    query.prepare("UPDATE HESAP SET bakiye = bakiye + :miktar WHERE hesap_no = :hesap_no");
    query.bindValue(":miktar", miktar);
    query.bindValue(":hesap_no", hesapNo);

    if(query.exec()) {
        bakiye += miktar;
        return true;
    }
    return false;
}

bool Hesap::paraCek(double miktar) {
    if (miktar <= 0 || bakiye < miktar || donduruldu) return false;

    QSqlQuery query;
    query.prepare("UPDATE HESAP SET bakiye = bakiye - :miktar WHERE hesap_no = :hesap_no");
    query.bindValue(":miktar", miktar);
    query.bindValue(":hesap_no", hesapNo);

    if(query.exec()) {
        bakiye -= miktar;
        return true;
    }
    return false;
}

double Hesap::bakiyeGetir() {
    return bakiye;
}

QList<Islem*> Hesap::islemleriAl() {
    QList<Islem*> liste;
    DataBaseManager* db = DataBaseManager::getInstance();
    QSqlQuery query;

    // --- DURANCAN: İşlem geçmişini çekme ---
    // TODO (Durancan): ISLEM tablosundan bu hesaba ait işlemler (gelen ve giden) çekilip nesnelere aktarıldı.
    query.prepare("SELECT * FROM ISLEM WHERE gonderici_hesap = :hesap_no OR alici_hesap = :hesap_no ORDER BY zaman_damgasi DESC");
    query.bindValue(":hesap_no", hesapNo);

    if (query.exec()) {
        while (query.next()) {
            Islem* islem = new Islem();
            islem->setGonderenHesap(query.value("gonderici_hesap").toString());
            islem->setAliciHesap(query.value("alici_hesap").toString());
            islem->setTutar(query.value("tutar").toDouble());
            islem->setIslemTipi(query.value("islem_tipi").toString());
            islem->setDurum(query.value("durum").toString());
            islem->setZamanDamgasi(query.value("zaman_damgasi").toDateTime());
            islem->setAciklama(query.value("aciklama").toString());

            liste.append(islem);
        }
    } else {
        qDebug() << "İşlemler çekilirken hata oluştu:" << query.lastError().text();
    }

    return liste;
}

bool Hesap::dondurulduMu() {
    return donduruldu;
}
