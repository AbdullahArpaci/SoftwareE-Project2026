#include "admindashboard.h"
#include "ui_admindashboard.h"

AdminDashboard::AdminDashboard(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AdminDashboard)
{
    ui->setupUi(this);

    // TODO: Veritabanından (DatabaseManager) aktif müşteri bilgilerini çek ve 'tableMusteriler' tablosuna listele.
    // TODO: Sistemdeki tüm işlem geçmişini (LogServisi) çek ve 'tableLoglar' tablosuna aktar.

    // TODO: 'btnHesapDondur' butonuna tıklandığında çalışacak slot bağlantısını (connect) kur.
}

AdminDashboard::~AdminDashboard()
{
    delete ui;
}

// TODO: btnHesapDondur butonuna tıklandığında çalışacak olan fonksiyonu (Slot) buraya tanımla.
// TODO: Tablodan seçilen müşterinin durumunu veritabanında dondurulmuş (Frozen) olarak güncelle.
// TODO: Hesap dondurma işlemini LogServisi üzerinden sistem loglarına yeni bir kayıt olarak ekle.
