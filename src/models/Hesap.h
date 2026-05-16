#ifndef HESAP_H
#define HESAP_H

#include <QString>
#include <QDate>
#include <QList>
#include "Islem.h"

class Hesap {
private:
    QString hesapNo;
    int kullaniciID;
    QString hesapTipi;
    double bakiye;
    QString paraBirimi;
    QDate olusturmaTarihi;
    bool donduruldu;
    bool aktif;

public:
    Hesap();
    ~Hesap();

    bool paraYatir(double miktar);
    bool paraCek(double miktar);
    double bakiyeGetir();
    QList<Islem*> islemleriAl();
    bool dondurulduMu();

    // --- YUSUF'UN TODO'SU İÇİN EKLENEN SETTER VE GETTER'LAR ---
    void setHesapNo(QString no);
    void setKullaniciID(int id);
    void setHesapTipi(QString tip);
    void setBakiye(double b);
    void setParaBirimi(QString pb);
    QString hesapNoGetir();

    // --- TAKIM İÇİN NOTLAR ---
    // TODO (Yusuf): paraCek() isleminden once Bakiye Kontrolu (UC-12) servisi calismalidir.
    // TODO (Yusuf & Abdullah): paraYatir ve paraCek islemleri SistemKontrolcusu::IslemYonet() uzerinden gecmeli ve ACID prensiplerine uygun kaydedilmelidir.
};

#endif // HESAP_H
