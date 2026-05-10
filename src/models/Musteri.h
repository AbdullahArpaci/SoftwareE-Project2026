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

    // --- TAKIM İÇİN NOTLAR ---
    // TODO (Abdullah): profilGoruntule() cagirildiginda Musteri'nin verileri VeritabaniYoneticisi::kullaniciVerisiYukle() ile cekilmelidir. [cite: 2, 451]
};

#endif // MUSTERI_H
