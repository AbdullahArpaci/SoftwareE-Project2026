#ifndef KULLANICI_H
#define KULLANICI_H

#include <QString>
#include <QDateTime>

class Kullanici {
protected:
    int kullaniciID;
    QString kimlikNo;
    QString ad;
    QString soyad;
    QString email;
    QString telefon;
    QString sifreHash;
    QString rol;
    QDateTime kayitTarihi;
    bool aktif;

public:
    Kullanici();
    virtual ~Kullanici();

    virtual bool girisYap();
    virtual void cikisYap();
    QString kimlikNoGetir();
    QString rolGetir();

    // --- TAKIM İÇİN NOTLAR (Abdullah ve Yusuf'un Dikkatine) ---
    // TODO (Yusuf): girisYap() metodu cagirildiginda SistemKontrolcusu::kullaniciDogrula() metodu calismalidir. [cite: 2, 446]
    // TODO (Abdullah): Giris isleminin basarili/basarisiz durumu VeritabaniYoneticisi::etkinlikKaydet() ile loglanmalidir. [cite: 2, 453]
};

#endif // KULLANICI_H
