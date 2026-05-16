#include "LoginWindow.h"
#include "SistemKontrolcusu.h"
#include "Kullanici.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QDebug>
#include "CustomerDashboard.h"

LoginWindow::LoginWindow(QWidget* parent) : QWidget(parent) {

    // Pencere ayarları
    setWindowTitle("Banka Yönetim Sistemi");
    setFixedSize(400, 500);

    // Arka plan rengi
    setStyleSheet("background-color: #1a1a2e;");

    // --- Bileşenler ---
    baslikLabel = new QLabel("🏦 BANKA");
    baslikLabel->setAlignment(Qt::AlignCenter);
    baslikLabel->setStyleSheet(
        "color: #e2b96f;"
        "font-size: 36px;"
        "font-weight: bold;"
        "letter-spacing: 8px;"
        "margin-top: 40px;"
        );

    altBaslikLabel = new QLabel("YÖNETİM SİSTEMİ");
    altBaslikLabel->setAlignment(Qt::AlignCenter);
    altBaslikLabel->setStyleSheet(
        "color: #8888aa;"
        "font-size: 11px;"
        "letter-spacing: 4px;"
        "margin-bottom: 40px;"
        );

    kimlikNoInput = new QLineEdit();
    kimlikNoInput->setPlaceholderText("TC Kimlik No");
    kimlikNoInput->setMaxLength(11);
    kimlikNoInput->setStyleSheet(
        "background-color: #16213e;"
        "color: #ffffff;"
        "border: 1px solid #e2b96f;"
        "border-radius: 8px;"
        "padding: 12px 16px;"
        "font-size: 14px;"
        "margin: 8px 0;"
        );

    sifreInput = new QLineEdit();
    sifreInput->setPlaceholderText("Şifre");
    sifreInput->setEchoMode(QLineEdit::Password);
    sifreInput->setStyleSheet(
        "background-color: #16213e;"
        "color: #ffffff;"
        "border: 1px solid #e2b96f;"
        "border-radius: 8px;"
        "padding: 12px 16px;"
        "font-size: 14px;"
        "margin: 8px 0;"
        );

    girisButon = new QPushButton("GİRİŞ YAP");
    girisButon->setFixedHeight(50);
    girisButon->setCursor(Qt::PointingHandCursor);
    girisButon->setStyleSheet(
        "background-color: #e2b96f;"
        "color: #1a1a2e;"
        "border: none;"
        "border-radius: 8px;"
        "font-size: 14px;"
        "font-weight: bold;"
        "letter-spacing: 2px;"
        "margin-top: 16px;"
        );

    hataLabel = new QLabel("");
    hataLabel->setAlignment(Qt::AlignCenter);
    hataLabel->setStyleSheet(
        "color: #ff6b6b;"
        "font-size: 12px;"
        );

    // --- Layout ---
    QVBoxLayout* layout = new QVBoxLayout();
    layout->setContentsMargins(50, 20, 50, 40);
    layout->setSpacing(4);

    layout->addWidget(baslikLabel);
    layout->addWidget(altBaslikLabel);
    layout->addStretch();
    layout->addWidget(kimlikNoInput);
    layout->addWidget(sifreInput);
    layout->addWidget(girisButon);
    layout->addWidget(hataLabel);
    layout->addStretch();

    setLayout(layout);

    // --- Sinyal ---
    connect(girisButon, &QPushButton::clicked, this, &LoginWindow::onGirisClicked);
    connect(sifreInput, &QLineEdit::returnPressed, this, &LoginWindow::onGirisClicked);
}

LoginWindow::~LoginWindow() {}

void LoginWindow::onGirisClicked() {

    QString kimlikNo = kimlikNoInput->text().trimmed();
    QString sifre = sifreInput->text();

    if(kimlikNo.isEmpty() || sifre.isEmpty()) {
        hataLabel->setText("⚠ Lütfen tüm alanları doldurun.");
        return;
    }

    if(kimlikNo.length() != 11) {
        hataLabel->setText("⚠ TC Kimlik No 11 haneli olmalıdır.");
        return;
    }

    SistemKontrolcusu* sk = SistemKontrolcusu::getInstance();
    Kullanici* kullanici = sk->kullaniciDogrula(kimlikNo, sifre);

    if(kullanici != nullptr) {
        if(kullanici->rolGetir() == "musteri") {
            CustomerDashboard* dashboard = new CustomerDashboard(kullanici);
            dashboard->show();
        } else {
            qDebug() << "Admin girişi";
        }
        this->close();
    } else {
        hataLabel->setText("⚠ Hatalı kimlik no veya şifre!");
        sifreInput->clear();
        sifreInput->setFocus();
    }
}