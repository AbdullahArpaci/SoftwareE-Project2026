#include "CustomerProfileDialog.h"
#include "ui_CustomerProfileDialog.h"
#include "Musteri.h"
#include <QInputDialog>
#include <QMessageBox>
#include "databasemanager.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

CustomerProfileDialog::CustomerProfileDialog(Kullanici* kullanici, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CustomerProfileDialog),
    m_kullanici(kullanici)
{
    ui->setupUi(this);

    if (m_kullanici) {
        if (Musteri* m = dynamic_cast<Musteri*>(m_kullanici)) {
            m->profilGoruntule(); // Veritabanından en güncel bilgileri çek
        }
        
        ui->lblAdSoyad->setText(m_kullanici->getAd() + " " + m_kullanici->getSoyad());
        ui->lblTc->setText(m_kullanici->kimlikNoGetir());
        ui->lblEmail->setText(m_kullanici->getEmail());
        ui->lblTelefon->setText(m_kullanici->getTelefon());
        ui->lblRol->setText(m_kullanici->rolGetir() == "musteri" ? "Müşteri" : "Yönetici");
    }
}

CustomerProfileDialog::~CustomerProfileDialog()
{
    delete ui;
}

void CustomerProfileDialog::on_btnKapat_clicked()
{
    this->close();
}

void CustomerProfileDialog::on_btnSifreDegistir_clicked()
{
    if (!m_kullanici) return;

    bool ok;
    QString yeniSifre = QInputDialog::getText(this, "Şifre Değiştir",
                                              "Yeni şifrenizi girin:", QLineEdit::Password,
                                              "", &ok);
    if (ok && !yeniSifre.isEmpty()) {
        DataBaseManager* db = DataBaseManager::getInstance();
        QSqlQuery query;
        query.prepare("UPDATE KULLANICI SET sifre_hash = :sifre WHERE kullanici_id = :id");
        query.bindValue(":sifre", yeniSifre);
        query.bindValue(":id", m_kullanici->getKullaniciID());

        if (query.exec()) {
            m_kullanici->setSifreHash(yeniSifre);
            QMessageBox::information(this, "Başarılı", "Şifreniz başarıyla değiştirildi.");
        } else {
            QMessageBox::critical(this, "Hata", "Şifre güncellenirken hata oluştu.");
            qDebug() << "Şifre güncelleme hatası:" << query.lastError().text();
        }
    }
}
