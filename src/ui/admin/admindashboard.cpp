#include "admindashboard.h"
#include "databasemanager.h"
#include "SistemKontrolcusu.h"
#include "LoginWindow.h"
#include <QSqlQuery>
#include <QMessageBox>
#include <QDebug>

AdminDashboard::AdminDashboard(QWidget* parent) : QWidget(parent) {

    setWindowTitle("Yönetici Paneli");
    setWindowState(Qt::WindowMaximized);
    setStyleSheet("background-color: #1a1a2e; color: #ffffff;");

    // ========== ÜST BAR ==========
    baslikLabel = new QLabel("🏦  BANKA — Yönetici Paneli");
    baslikLabel->setStyleSheet(
        "color: #e2b96f;"
        "font-size: 22px;"
        "font-weight: bold;"
        "letter-spacing: 4px;"
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
        );

    QHBoxLayout* ustBar = new QHBoxLayout();
    ustBar->addWidget(baslikLabel);
    ustBar->addStretch();
    ustBar->addWidget(cikisButon);

    // ========== MÜŞTERİ TABLOSU ==========
    musteriBaslik = new QLabel("Müşteriler");
    musteriBaslik->setStyleSheet(
        "color: #e2b96f;"
        "font-size: 16px;"
        "font-weight: bold;"
        "margin-top: 10px;"
        );

    musteriTablo = new QTableWidget();
    musteriTablo->setColumnCount(5);
    musteriTablo->setHorizontalHeaderLabels(
        {"Ad", "Soyad", "Kimlik No", "Hesap No", "Durum"}
        );
    musteriTablo->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    musteriTablo->verticalHeader()->setVisible(false);
    musteriTablo->setEditTriggers(QAbstractItemView::NoEditTriggers);
    musteriTablo->setSelectionBehavior(QAbstractItemView::SelectRows);
    musteriTablo->setFixedHeight(200);
    musteriTablo->setStyleSheet(
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
        );

    hesapDondurButon = new QPushButton("🔒  Seçili Hesabı Dondur");
    hesapDondurButon->setFixedHeight(45);
    hesapDondurButon->setCursor(Qt::PointingHandCursor);
    hesapDondurButon->setStyleSheet(
        "background-color: #ff6b6b;"
        "color: #ffffff;"
        "border: none;"
        "border-radius: 8px;"
        "font-size: 14px;"
        "font-weight: bold;"
        );

    // ========== LOG TABLOSU ==========
    logBaslik = new QLabel("Sistem Logları");
    logBaslik->setStyleSheet(
        "color: #e2b96f;"
        "font-size: 16px;"
        "font-weight: bold;"
        "margin-top: 10px;"
        );

    logTablo = new QTableWidget();
    logTablo->setColumnCount(4);
    logTablo->setHorizontalHeaderLabels(
        {"Tarih", "Kullanıcı ID", "Olay", "Detay"}
        );
    logTablo->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    logTablo->verticalHeader()->setVisible(false);
    logTablo->setEditTriggers(QAbstractItemView::NoEditTriggers);
    logTablo->setSelectionBehavior(QAbstractItemView::SelectRows);
    logTablo->setStyleSheet(musteriTablo->styleSheet());

    // ========== ANA LAYOUT ==========
    QVBoxLayout* anaLayout = new QVBoxLayout();
    anaLayout->setContentsMargins(40, 25, 40, 30);
    anaLayout->setSpacing(12);

    anaLayout->addLayout(ustBar);
    anaLayout->addWidget(musteriBaslik);
    anaLayout->addWidget(musteriTablo);
    anaLayout->addWidget(hesapDondurButon);
    anaLayout->addWidget(logBaslik);
    anaLayout->addWidget(logTablo);

    setLayout(anaLayout);

    // ========== SİNYALLER ==========
    connect(hesapDondurButon, &QPushButton::clicked,
            this, &AdminDashboard::onHesapDondurClicked);
    connect(cikisButon, &QPushButton::clicked,
            this, &AdminDashboard::onCikisClicked);

    // Verileri yükle
    musterileriYukle();
    loglarıYukle();
}

AdminDashboard::~AdminDashboard() {}

void AdminDashboard::musterileriYukle() {
    DataBaseManager* db = DataBaseManager::getInstance();

    QSqlQuery sorgu = db->execute(
        "SELECT K.ad, K.soyad, K.kimlik_no, H.hesap_no, "
        "CASE WHEN H.donduruldu = 1 THEN 'Dondurulmuş' ELSE 'Aktif' END as durum "
        "FROM KULLANICI K "
        "LEFT JOIN HESAP H ON K.kullanici_id = H.kullanici_id "
        "WHERE K.rol = 'musteri'"
        );

    musteriTablo->setRowCount(0);
    int satir = 0;

    while(sorgu.next()) {
        musteriTablo->insertRow(satir);
        musteriTablo->setItem(satir, 0,
                              new QTableWidgetItem(sorgu.value(0).toString()));
        musteriTablo->setItem(satir, 1,
                              new QTableWidgetItem(sorgu.value(1).toString()));
        musteriTablo->setItem(satir, 2,
                              new QTableWidgetItem(sorgu.value(2).toString()));
        musteriTablo->setItem(satir, 3,
                              new QTableWidgetItem(sorgu.value(3).toString()));

        QString durum = sorgu.value(4).toString();
        QTableWidgetItem* durumItem = new QTableWidgetItem(durum);
        if(durum == "Dondurulmuş") {
            durumItem->setForeground(QColor("#ff6b6b"));
        } else {
            durumItem->setForeground(QColor("#6bffb8"));
        }
        musteriTablo->setItem(satir, 4, durumItem);
        satir++;
    }
}

void AdminDashboard::loglarıYukle() {
    DataBaseManager* db = DataBaseManager::getInstance();

    QSqlQuery sorgu = db->execute(
        "SELECT zaman_damgasi, kullanici_id, olay_tipi, detaylar "
        "FROM LOG_KAYIT "
        "ORDER BY zaman_damgasi DESC "
        "LIMIT 20"
        );

    logTablo->setRowCount(0);
    int satir = 0;

    while(sorgu.next()) {
        logTablo->insertRow(satir);
        logTablo->setItem(satir, 0,
                          new QTableWidgetItem(sorgu.value(0).toString()));
        logTablo->setItem(satir, 1,
                          new QTableWidgetItem(sorgu.value(1).toString()));
        logTablo->setItem(satir, 2,
                          new QTableWidgetItem(sorgu.value(2).toString()));
        logTablo->setItem(satir, 3,
                          new QTableWidgetItem(sorgu.value(3).toString()));
        satir++;
    }
}

void AdminDashboard::onHesapDondurClicked() {
    int secilenSatir = musteriTablo->currentRow();

    if(secilenSatir < 0) {
        QMessageBox::warning(this, "Uyarı", "Lütfen bir müşteri seçin!");
        return;
    }

    QString hesapNo = musteriTablo->item(secilenSatir, 3)->text();
    QString ad      = musteriTablo->item(secilenSatir, 0)->text();
    QString soyad   = musteriTablo->item(secilenSatir, 1)->text();

    // Onay iste
    QMessageBox::StandardButton cevap = QMessageBox::question(
        this, "Hesap Dondur",
        ad + " " + soyad + " adlı müşterinin hesabı dondurulsun mu?",
        QMessageBox::Yes | QMessageBox::No
        );

    if(cevap == QMessageBox::Yes) {
        DataBaseManager* db = DataBaseManager::getInstance();
        db->execute(
            "UPDATE HESAP SET donduruldu = 1 WHERE hesap_no = '" + hesapNo + "'"
            );

        QMessageBox::information(this, "Başarılı",
                                 hesapNo + " numaralı hesap donduruldu!");

        // Tabloyu yenile
        musterileriYukle();
        loglarıYukle();
    }
}

void AdminDashboard::onCikisClicked() {
    SistemKontrolcusu::getInstance()->oturumKapat();
    LoginWindow* login = new LoginWindow();
    login->show();
    this->close();
}