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

    // --- YUSUF'UN TODO'SU İÇİN EKLENEN SETTER METOTLARI ---
    void setKullaniciID(int id);
    void setKimlikNo(QString kimlik);
    void setAd(QString a);
    void setSoyad(QString s);
    void setRol(QString r);

    // --- TAKIM İÇİN NOTLAR (Abdullah ve Yusuf'un Dikkatine) ---
    // TODO (Yusuf): girisYap() metodu cagirildiginda SistemKontrolcusu::kullaniciDogrula() metodu calismalidir.
    // TODO (Abdullah): Giris isleminin basarili/basarisiz durumu VeritabaniYoneticisi::etkinlikKaydet() ile loglanmalidir.
};

#endif // KULLANICI_H
