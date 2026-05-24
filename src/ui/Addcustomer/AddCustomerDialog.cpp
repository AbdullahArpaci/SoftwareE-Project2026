#include "AddCustomerDialog.h"
#include "ui_AddCustomerDialog.h"
#include "Yonetici.h"
#include "Musteri.h"
#include <QMessageBox>

AddCustomerDialog::AddCustomerDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddCustomerDialog)
{
    ui->setupUi(this);
}

AddCustomerDialog::~AddCustomerDialog()
{
    delete ui;
}

void AddCustomerDialog::on_btnCancel_clicked()
{
    this->reject();
}

void AddCustomerDialog::on_btnSave_clicked()
{
    QString tc = ui->editTc->text();
    QString ad = ui->editAd->text();
    QString soyad = ui->editSoyad->text();
    QString sifre = ui->editSifre->text();

    if(tc.isEmpty() || ad.isEmpty() || soyad.isEmpty() || sifre.isEmpty()) {
        QMessageBox::warning(this, "Hata", "Lütfen tüm alanları doldurun.");
        return;
    }

    if(tc.length() != 11) {
        QMessageBox::warning(this, "Hata", "TC Kimlik No tam olarak 11 hane olmalıdır.");
        return;
    }

    bool isNumeric;
    tc.toLongLong(&isNumeric);
    if(!isNumeric) {
        QMessageBox::warning(this, "Hata", "TC Kimlik No sadece rakamlardan oluşmalıdır.");
        return;
    }

    Musteri* yeniMusteri = new Musteri();
    yeniMusteri->setKimlikNo(tc);
    yeniMusteri->setAd(ad);
    yeniMusteri->setSoyad(soyad);
    yeniMusteri->setSifreHash(sifre);
    yeniMusteri->setEmail(tc + "@banka.com"); // Varsayılan email
    yeniMusteri->setTelefon("0000000000");   // Varsayılan telefon

    Yonetici y;
    if (y.musteriEkle(yeniMusteri)) {
        QMessageBox::information(this, "Başarılı", "Müşteri başarıyla eklendi.");
        this->accept();
    } else {
        QMessageBox::critical(this, "Hata", "Müşteri eklenirken bir hata oluştu.");
    }
    
    delete yeniMusteri;
}
