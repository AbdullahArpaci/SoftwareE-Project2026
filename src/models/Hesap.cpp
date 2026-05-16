#include "Hesap.h"
#include <databasemanager.h>
#include <QSqlQuery>
#include <QVariant>

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
    // TODO: ISLEM tablosundan bu hesap_no'ya ait işlemler çekilecek.
    return liste;
}

bool Hesap::dondurulduMu() {
    return donduruldu;
}
