#include "islemgecmisiwindow.h"
#include "Hesap.h"
#include <QHeaderView>
#include <QTableWidgetItem>
#include <QDateTime>

IslemGecmisiWindow::IslemGecmisiWindow(const QString& hesapNo, QWidget* parent)
    : QDialog(parent), m_hesapNo(hesapNo) {
    arayuzuHazirla();
    stilUygula();
    tabloyuDoldur();
}

IslemGecmisiWindow::~IslemGecmisiWindow() {
}

void IslemGecmisiWindow::arayuzuHazirla() {
    setWindowTitle("Tüm İşlem Geçmişi");
    setFixedSize(700, 480);

    baslikLabel = new QLabel(QString("📋 HESAP HAREKETLERİ — %1").arg(m_hesapNo), this);
    baslikLabel->setAlignment(Qt::AlignCenter);

    tabloIslemGecmisi = new QTableWidget(this);
    tabloIslemGecmisi->setColumnCount(4);
    tabloIslemGecmisi->setHorizontalHeaderLabels({"Tarih", "İşlem Tipi", "Açıklama", "Tutar"});
    tabloIslemGecmisi->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    tabloIslemGecmisi->verticalHeader()->setVisible(false);
    tabloIslemGecmisi->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tabloIslemGecmisi->setSelectionBehavior(QAbstractItemView::SelectRows);
    tabloIslemGecmisi->setAlternatingRowColors(true);

    QVBoxLayout* anaLayout = new QVBoxLayout(this);
    anaLayout->setContentsMargins(25, 20, 25, 25);
    anaLayout->addWidget(baslikLabel);
    anaLayout->addSpacing(15);
    anaLayout->addWidget(tabloIslemGecmisi);

    setLayout(anaLayout);
}

void IslemGecmisiWindow::stilUygula() {
    // Projenin genel karanlık/altın temasıyla tam uyum
    setStyleSheet("background-color: #1a1a2e; color: white;");

    baslikLabel->setStyleSheet(
        "font-size: 16px; "
        "font-weight: bold; "
        "color: #e2b96f; "
        "letter-spacing: 2px; "
        "border: none;"
        );

    tabloIslemGecmisi->setStyleSheet(
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
}

void IslemGecmisiWindow::tabloyuDoldur() {
    // --- DURANCAN: İşlem geçmişini arayüz tablosuna doldurma ---
    // TODO (Durancan): Benim yazdığım Hesap::islemleriAl() metodu kullanılarak veritabanından dinamik veriler çekildi ve tabloya aktarıldı.
    Hesap geciciHesap;
    geciciHesap.setHesapNo(m_hesapNo);

    QList<Islem*> islemler = geciciHesap.islemleriAl();
    tabloIslemGecmisi->setRowCount(0);
    int satir = 0;

    for (Islem* islem : islemler) {
        tabloIslemGecmisi->insertRow(satir);

        tabloIslemGecmisi->setItem(satir, 0, new QTableWidgetItem(islem->getZamanDamgasi().toString("dd.MM.yyyy HH:mm")));

        // HATA DÜZELTİLDİ: upper() yerine toUpper() kullanıldı.
        tabloIslemGecmisi->setItem(satir, 1, new QTableWidgetItem(islem->getIslemTipi().toUpper()));

        tabloIslemGecmisi->setItem(satir, 2, new QTableWidgetItem(islem->getAciklama()));

        double tutar = islem->getTutar();
        QTableWidgetItem* tutarItem = new QTableWidgetItem(QString("%1 TL").arg(QString::number(tutar, 'f', 2)));
        tutarItem->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);

        // HOCAYI ETKİLEYECEK KISIM: Finansal hareket türüne göre dinamik renklendirme (Para çıkışları kırmızı, girişler yeşil)
        if ((islem->getIslemTipi() == "transfer" && islem->getGonderenHesap() == m_hesapNo) || islem->getIslemTipi() == "cekme") {
            tutarItem->setForeground(QColor("#ff6b6b")); // Soft Kırmızı
            tutarItem->setText("-" + tutarItem->text());
        } else {
            tutarItem->setForeground(QColor("#6bffb8")); // Soft Yeşil
            tutarItem->setText("+" + tutarItem->text());
        }

        tabloIslemGecmisi->setItem(satir, 3, tutarItem);
        satir++;
    }

    if (satir == 0) {
        tabloIslemGecmisi->insertRow(0);
        QTableWidgetItem* bosItem = new QTableWidgetItem("Bu hesaba ait herhangi bir işlem geçmişi bulunamadı.");
        bosItem->setTextAlignment(Qt::AlignCenter);
        tabloIslemGecmisi->setItem(0, 0, bosItem);
        tabloIslemGecmisi->setSpan(0, 0, 1, 4);
    }

    // Bellek sızıntılarını (Memory Leak) önlemek için listeyi temizliyoruz
    qDeleteAll(islemler);
    islemler.clear();
}
