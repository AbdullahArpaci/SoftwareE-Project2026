#ifndef ISLEM_H
#define ISLEM_H

#include <QString>
#include <QDateTime>

class Islem {
protected:
    int islemID;
    QString gonderenHesapNo;
    QString aliciHesapNo;
    double tutar;
    QString islemTipi;
    QString durum;
    QDateTime zamanDamgasi;
    QString aciklama;

public:
    Islem();
    virtual ~Islem();

    virtual bool islemGerceklestir();
    QString durumGetir();

    // --- TAKIM İÇİN NOTLAR ---
    // TODO (Abdullah): islemGerceklestir() true dondugunde, VeritabaniYoneticisi::IslemKaydet() calistirilmalidir. [cite: 2, 452]
};

class Transfer : public Islem {
public:
    Transfer();
    ~Transfer();

    bool transferYap();

    // --- TAKIM İÇİN NOTLAR ---
    // TODO (Yusuf): transferYap() metodu, senin Transfer Servisi icindeki bakiyeKontrol mantigini cagirmalidir. [cite: 2, 572]
};

#endif // ISLEM_H
