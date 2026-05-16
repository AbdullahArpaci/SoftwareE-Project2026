#ifndef YONETICI_H
#define YONETICI_H

#include "Kullanici.h"
#include "Musteri.h"
#include "Islem.h"

class Yonetici : public Kullanici {
public:
    Yonetici();
    ~Yonetici();

    bool musteriEkle(Musteri* musteri);
    bool musteriProfiliGuncelle(int id);
    bool hesabiDondur(QString hesapNo);
    QList<Islem*> tumKayitlariGoruntule();
    bool krediDegerlendir(int krediID, bool onay);

    // Yusuf'un servis katmanında kullanabilmesi için ID Getter'ı
    int kullaniciIDGetir() const;

    // --- TAKIM İÇİN NOTLAR ---
    // TODO (Abdullah): musteriEkle() ve hesabiDondur() calistiginda veritabani update islemleri yapilmalidir.
};

#endif // YONETICI_H
