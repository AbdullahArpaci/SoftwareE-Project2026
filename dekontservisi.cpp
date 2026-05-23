#include "dekontservisi.h"
#include "ui_dekontservisi.h"


DekontServisi::DekontServisi(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::DekontServisi)
{
    ui->setupUi(this);
    QString gonderici = "Eymen ";
    QString alici = "Yaşar Samet Üçoğlan";
    QString tutar = "1000";
    ui->Gonderici_KA->setText(gonderici);
    ui->Alici_KA->setText(alici);
    ui->Tutar->setText(tutar + " TRY");
}
DekontServisi::~DekontServisi()
{
    delete ui;
}
void DekontServisi::dosyayayaz(QString gonder,QString al,QString tutarmiktari){
    QFile dosya("C:/Users/MSI/Desktop/Görsel Programlama/DekontServisi/Dekontlar.txt"); //Dosya yolu şahsi PC'ye göre ayarlanmıştır.
    QDate tarih;
    QString mevcut = tarih.currentDate().toString();
    if (!dosya.open(QIODevice::WriteOnly | QIODevice::Text)) {
        ui->durum->setText("Kaydedilmedi");
        qDebug() << "Dosya açılırken hata oluştu!";
        return;
    }
    QTextStream yaz(&dosya);
    yaz.setEncoding(QStringConverter::Utf8);
    yaz << "========================================" << Qt::endl;
    yaz << "             BANKA DEKONTU              " << Qt::endl;
    yaz << "========================================" << Qt::endl;
    yaz << "Gönderen : " << gonder << Qt::endl;
    yaz << "Alıcı    : " << al << Qt::endl;
    yaz << "Tutar    : " << tutarmiktari << Qt::endl;
    yaz << "========================================" << Qt::endl;
    yaz << "İşlem Tarihi: "<< mevcut << Qt::endl;
    ui->durum->setText("Kaydedildi");
}
void DekontServisi::on_btn_TXTolarakkaydet_clicked()
{
    QString gonderici = "Eymen Üçoğlan";
    QString alici = "Yaşar Samet Üçoğlan";
    QString tutar = "1000";
    dosyayayaz(gonderici,alici,tutar);
}

//Kod veritabanı bağlantısını kuradamadım çünkü programın veritabanı dosyasını bulamadım
