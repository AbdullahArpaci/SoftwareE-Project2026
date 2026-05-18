#include "CustomerDashboard.h"
#include "databasemanager.h"
#include "SistemKontrolcusu.h"
#include <QSqlQuery>
#include <QDebug>
#include <QHeaderView>
#include <TransferWindow.h>

CustomerDashboard::CustomerDashboard(Kullanici* kullanici, QWidget* parent)
    : QWidget(parent), aktifKullanici(kullanici) {

    setWindowTitle("Müşteri Paneli");
    setWindowState(Qt::WindowMaximized);
    setStyleSheet("background-color: #1a1a2e; color: #ffffff;");

    // ========== ÜST BAR ==========
    baslikLabel = new QLabel("🏦  BANKA");
    baslikLabel->setStyleSheet(
        "color: #e2b96f;"
        "font-size: 22px;"
        "font-weight: bold;"
        "letter-spacing: 4px;"
        );

    kullaniciLabel = new QLabel("Hoş geldiniz!");
    kullaniciLabel->setStyleSheet(
        "color: #8888aa;"
        "font-size: 14px;"
        );

    cikisButon = new QPushButton("Çıkış");
    cikisButon->setFixedSize(90, 36);
    cikisButon->setCursor(Qt::PointingHandCursor);
    cikisButon->setStyleSheet(
        "background-color: #ff6b6b;"
        "color: #ffffff;"
        "border: none;"
        "border-radius: 6px;"
        "font-weight: bold;"
        "font-size: 13px;"
        );

    QHBoxLayout* ustBar = new QHBoxLayout();
    ustBar->addWidget(baslikLabel);
    ustBar->addStretch();
    ustBar->addWidget(kullaniciLabel);
    ustBar->addSpacing(20);
    ustBar->addWidget(cikisButon);

    // ========== KARTLAR ==========
    bakiyeKart = kartOlustur("Toplam Bakiye", bakiyeLabel, "Yükleniyor...");
    hesapKart  = kartOlustur("Hesap No",      hesapNoLabel, "Yükleniyor...");

    QHBoxLayout* kartLayout = new QHBoxLayout();
    kartLayout->setSpacing(20);
    kartLayout->addWidget(bakiyeKart);
    kartLayout->addWidget(hesapKart);

    // ========== BUTONLAR ==========
    transferButon = new QPushButton("💸   Para Transfer");
    transferButon->setFixedHeight(55);
    transferButon->setCursor(Qt::PointingHandCursor);
    transferButon->setStyleSheet(
        "background-color: #e2b96f;"
        "color: #1a1a2e;"
        "border: none;"
        "border-radius: 10px;"
        "font-size: 15px;"
        "font-weight: bold;"
        );

    islemGecmisiButon = new QPushButton("📋   İşlem Geçmişi");
    islemGecmisiButon->setFixedHeight(55);
    islemGecmisiButon->setCursor(Qt::PointingHandCursor);
    islemGecmisiButon->setStyleSheet(
        "background-color: #16213e;"
        "color: #e2b96f;"
        "border: 1px solid #e2b96f;"
        "border-radius: 10px;"
        "font-size: 15px;"
        "font-weight: bold;"
        );

    QHBoxLayout* butonLayout = new QHBoxLayout();
    butonLayout->setSpacing(20);
    butonLayout->addWidget(transferButon);
    butonLayout->addWidget(islemGecmisiButon);

    // ========== SON İŞLEMLER ==========
    sonIslemlerBaslik = new QLabel("Son İşlemler");
    sonIslemlerBaslik->setStyleSheet(
        "color: #e2b96f;"
        "font-size: 16px;"
        "font-weight: bold;"
        "margin-top: 10px;"
        );

    islemlerTablo = new QTableWidget();
    islemlerTablo->setColumnCount(4);
    islemlerTablo->setHorizontalHeaderLabels(
        {"Tarih", "İşlem Tipi", "Açıklama", "Tutar"}
        );
    islemlerTablo->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    islemlerTablo->verticalHeader()->setVisible(false);
    islemlerTablo->setEditTriggers(QAbstractItemView::NoEditTriggers);
    islemlerTablo->setSelectionBehavior(QAbstractItemView::SelectRows);
    islemlerTablo->setAlternatingRowColors(true);
    islemlerTablo->setStyleSheet(
        "QTableWidget {"
        "   background-color: #16213e;"
        "   border: 1px solid #0f3460;"
        "   border-radius: 10px;"
        "   gridline-color: #0f3460;"
        "   color: #ffffff;"
        "   font-size: 13px;"
        "}"
        "QTableWidget::item:selected {"
        "   background-color: #e2b96f;"
        "   color: #1a1a2e;"
        "}"
        "QHeaderView::section {"
        "   background-color: #0f3460;"
        "   color: #e2b96f;"
        "   padding: 10px;"
        "   border: none;"
        "   font-weight: bold;"
        "}"
        "QTableWidget::item:alternate {"
        "   background-color: #1a2a4a;"
        "}"
        );

    // ========== ANA LAYOUT ==========
    QVBoxLayout* anaLayout = new QVBoxLayout();
    anaLayout->setContentsMargins(40, 25, 40, 30);
    anaLayout->setSpacing(20);

    anaLayout->addLayout(ustBar);
    anaLayout->addLayout(kartLayout);
    anaLayout->addLayout(butonLayout);
    anaLayout->addWidget(sonIslemlerBaslik);
    anaLayout->addWidget(islemlerTablo);

    setLayout(anaLayout);

    // ========== SİNYALLER ==========
    connect(transferButon,     &QPushButton::clicked,
            this, &CustomerDashboard::onTransferClicked);
    connect(islemGecmisiButon, &QPushButton::clicked,
            this, &CustomerDashboard::onIslemGecmisiClicked);
    connect(cikisButon,        &QPushButton::clicked,
            this, &CustomerDashboard::onCikisClicked);

    // Verileri yükle
    bakiyeyiYukle();
    sonIslemleriYukle();
}

CustomerDashboard::~CustomerDashboard() {}

// Kart oluşturucu yardımcı fonksiyon
QFrame* CustomerDashboard::kartOlustur(const QString& baslik,
                                       QLabel*& degerLabel,
                                       const QString& deger) {
    QFrame* kart = new QFrame();
    kart->setStyleSheet(
        "QFrame {"
        "   background-color: #16213e;"
        "   border-radius: 12px;"
        "   border: 1px solid #e2b96f;"
        "}"
        );
    kart->setFixedHeight(120);

    QLabel* baslikLabel = new QLabel(baslik);
    baslikLabel->setAlignment(Qt::AlignCenter);
    baslikLabel->setStyleSheet(
        "color: #8888aa;"
        "font-size: 13px;"
        "border: none;"
        "padding-top: 10px;"
        );

    degerLabel = new QLabel(deger);
    degerLabel->setAlignment(Qt::AlignCenter);
    degerLabel->setStyleSheet(
        "color: #e2b96f;"
        "font-size: 26px;"
        "font-weight: bold;"
        "border: none;"
        );

    QVBoxLayout* kartLayout = new QVBoxLayout(kart);
    kartLayout->addWidget(baslikLabel);
    kartLayout->addWidget(degerLabel);

    return kart;
}

void CustomerDashboard::bakiyeyiYukle() {
    DataBaseManager* db = DataBaseManager::getInstance();

    int kullaniciID = aktifKullanici->getKullaniciID();

    // Önce hesap no'yu al
    QSqlQuery hesapSorgu = db->execute(
        "SELECT hesap_no FROM HESAP WHERE kullanici_id = " +
        QString::number(kullaniciID) + " AND hesap_tipi = 'vadesiz' LIMIT 1"
        );

    if(hesapSorgu.next()) {
        QString hesapNo = hesapSorgu.value(0).toString();
        hesapNoLabel->setText(hesapNo);

        // Sadece o hesabın bakiyesini al
        QSqlQuery bakiyeSorgu = db->execute(
            "SELECT bakiye FROM HESAP WHERE hesap_no = '" + hesapNo + "'"
            );

        if(bakiyeSorgu.next()) {
            double bakiye = bakiyeSorgu.value(0).toDouble();
            bakiyeLabel->setText(QString("%L1 TL").arg(bakiye, 0, 'f', 2));
        }
    }
}

void CustomerDashboard::sonIslemleriYukle() {
    DataBaseManager* db = DataBaseManager::getInstance();

    QSqlQuery sorgu = db->execute(
        "SELECT zaman_damgasi, islem_tipi, aciklama, tutar "
        "FROM ISLEM "
        "WHERE gonderici_hesap IN "
        "(SELECT hesap_no FROM HESAP WHERE kullanici_id = 1) "
        "ORDER BY zaman_damgasi DESC LIMIT 10"
        );

    islemlerTablo->setRowCount(0);
    int satir = 0;

    while(sorgu.next()) {
        islemlerTablo->insertRow(satir);

        islemlerTablo->setItem(satir, 0,
                               new QTableWidgetItem(sorgu.value(0).toString()));
        islemlerTablo->setItem(satir, 1,
                               new QTableWidgetItem(sorgu.value(1).toString()));
        islemlerTablo->setItem(satir, 2,
                               new QTableWidgetItem(sorgu.value(2).toString()));

        double tutar = sorgu.value(3).toDouble();
        QTableWidgetItem* tutarItem = new QTableWidgetItem(
            QString::number(tutar, 'f', 2) + " TL"
            );
        tutarItem->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
        islemlerTablo->setItem(satir, 3, tutarItem);

        satir++;
    }

    if(satir == 0) {
        islemlerTablo->insertRow(0);
        QTableWidgetItem* bos = new QTableWidgetItem("Henüz işlem yok");
        bos->setTextAlignment(Qt::AlignCenter);
        islemlerTablo->setItem(0, 0, bos);
        islemlerTablo->setSpan(0, 0, 1, 4);
    }
}

void CustomerDashboard::onTransferClicked() {
    QString hesapNo = hesapNoLabel->text(); // TR001, TR003 vs.
    TransferWindow* tw = new TransferWindow(hesapNo, this);
    if(tw->exec() == QDialog::Accepted) {
        bakiyeyiYukle();
        sonIslemleriYukle();
    }
}

void CustomerDashboard::onIslemGecmisiClicked() {
    // TODO: TransactionHistory açılacak
    qDebug() << "İşlem geçmişi butonuna basıldı";
}

void CustomerDashboard::onCikisClicked() {
    SistemKontrolcusu::getInstance()->oturumKapat();
    LoginWindow* login = new LoginWindow();
    login->show();
    this->close();
}