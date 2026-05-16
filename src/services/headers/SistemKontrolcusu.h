#ifndef SISTEMKONTROLCUSU_H
#define SISTEMKONTROLCUSU_H

#include <QString>
#include "HesapServisi.h"
#include "TransferServisi.h"

class Kullanici;
class Hesap;
class Islem;

class SistemKontrolcusu
{
private:
    static SistemKontrolcusu* instance;
    HesapServisi* hesapServisi;
    TransferServisi* transferServisi;

    SistemKontrolcusu();
    ~SistemKontrolcusu();

    SistemKontrolcusu(const SistemKontrolcusu&) = delete;
    SistemKontrolcusu& operator=(const SistemKontrolcusu&) = delete;

public:
    static SistemKontrolcusu* getInstance();

    Kullanici* kullaniciDogrula(QString kimlikNo, QString sifre);
    bool islemYonet(Hesap* hesap, Islem* islem);
    void oturumKapat();
};

#endif // SISTEMKONTROLCUSU_H
