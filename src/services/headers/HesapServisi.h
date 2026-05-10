#ifndef HESAPSERVISI_H
#define HESAPSERVISI_H

#include <QString>

class Hesap;

class HesapServisi {
public:
    HesapServisi();
    ~HesapServisi();

    bool bakiyeKontrol(QString hesapNo, double tutar);
    bool bakiyeGuncelle(QString hesapNo, double fark);
    Hesap* hesapOlustur(int kullaniciID, QString tip);
    bool hesapKapat(QString hesapNo);
};

#endif // HESAPSERVISI_H
