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

    // --- TAKIM İÇİN NOTLAR ---
    // TODO (Yusuf): paraCek() isleminden once Bakiye Kontrolu (UC-12) servisi calismalidir. [cite: 2, 334]
    // TODO (Yusuf & Abdullah): paraYatir ve paraCek islemleri SistemKontrolcusu::IslemYonet() uzerinden gecmeli [cite: 2, 447] ve ACID prensiplerine uygun kaydedilmelidir. [cite: 1, 20]
};

#endif // HESAP_H
