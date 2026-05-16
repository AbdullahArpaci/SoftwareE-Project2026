#ifndef MUSTERI_H
#define MUSTERI_H

#include "Kullanici.h"
#include "Hesap.h"
#include <QList>

class Musteri : public Kullanici {
private:
    QList<Hesap*> hesaplar;

public:
    Musteri();
    ~Musteri();

    void profilGoruntule();
    QList<Hesap*> hesapDetaylariAl();
    void hesapEkle(Hesap* hesap);

    // Yusuf ve Abdullah'ın servislerde kullanabilmesi için eklenen getter
    int kullaniciIDGetir() const;

    // --- TAKIM İÇİN NOTLAR ---
    // TODO (Abdullah): profilGoruntule() cagirildiginda Musteri'nin verileri VeritabaniYoneticisi::kullaniciVerisiYukle() ile cekilmelidir.
};

#endif // MUSTERI_H
