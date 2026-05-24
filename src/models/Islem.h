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

    // --- DURANCAN: İşlem geçmişi tablosu için eklenen Setter ve Getter metotları ---
    // TODO (Durancan): Bu metotlar Hesap::islemleriAl() içinde veritabanından çekilen verileri nesneye aktarmak için kullanılacak.
    void setGonderenHesap(QString gonderen) { gonderenHesapNo = gonderen; }
    void setAliciHesap(QString alici) { aliciHesapNo = alici; }
    void setTutar(double t) { tutar = t; }
    void setIslemTipi(QString tip) { islemTipi = tip; }
    void setDurum(QString d) { durum = d; }
    void setZamanDamgasi(QDateTime zaman) { zamanDamgasi = zaman; }
    void setAciklama(QString acik) { aciklama = acik; }

    QString getGonderenHesap() const { return gonderenHesapNo; }
    QString getAliciHesap() const { return aliciHesapNo; }
    double getTutar() const { return tutar; }
    QString getIslemTipi() const { return islemTipi; }
    QDateTime getZamanDamgasi() const { return zamanDamgasi; }
    QString getAciklama() const { return aciklama; }

    // --- TAKIM İÇİN NOTLAR ---
    // TODO (Abdullah): islemGerceklestir() true dondugunde, VeritabaniYoneticisi::IslemKaydet() calistirilmalidir.
};

class Transfer : public Islem {
public:
    Transfer();
    ~Transfer();

    bool transferYap();

    // --- TAKIM İÇİN NOTLAR ---
    // TODO (Yusuf): transferYap() metodu, senin Transfer Servisi icindeki bakiyeKontrol mantigini cagirmalidir.
};

#endif // ISLEM_H
