#ifndef CUSTOMERDASHBOARD_H
#define CUSTOMERDASHBOARD_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QFrame>
#include <QTableWidget>
#include "Kullanici.h"
#include <LoginWindow.h>

class CustomerDashboard : public QWidget {
    Q_OBJECT

public:
    CustomerDashboard(Kullanici* kullanici, QWidget* parent = nullptr);
    ~CustomerDashboard();

private slots:
    void onTransferClicked();
    void onIslemGecmisiClicked();
    void onCikisClicked();
    void onParaYatirClicked();
    void onParaCekClicked();

private:
    Kullanici* aktifKullanici;

    // Üst bar
    QLabel* baslikLabel;
    QLabel* kullaniciLabel;
    QPushButton* cikisButon;

    // Kart 1 — Bakiye
    QFrame* bakiyeKart;
    QLabel* bakiyeBaslik;
    QLabel* bakiyeLabel;

    // Kart 2 — Hesap No
    QFrame* hesapKart;
    QLabel* hesapBaslik;
    QLabel* hesapNoLabel;

    // Butonlar
    QPushButton* transferButon;
    QPushButton* islemGecmisiButon;
    QPushButton* paraYatirButon;
    QPushButton* paraCekButon;

    // Son işlemler tablosu
    QLabel* sonIslemlerBaslik;
    QTableWidget* islemlerTablo;

    void bakiyeyiYukle();
    void sonIslemleriYukle();

    QFrame* kartOlustur(const QString& baslik,
                        QLabel*& degerLabel,
                        const QString& deger);
};

#endif // CUSTOMERDASHBOARD_H
