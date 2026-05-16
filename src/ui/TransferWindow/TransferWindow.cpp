#include "TransferWindow.h"
#include <QMessageBox>
#include <QDoubleValidator>

TransferWindow::TransferWindow(QWidget *parent) : QDialog(parent)
{
    arayuzu_hazirla();
    stil_uygula();
}

TransferWindow::~TransferWindow()
{
}

void TransferWindow::arayuzu_hazirla()
{
    this->setWindowTitle("Para Transferi");
    this->setFixedSize(350, 250);

    baslik_etiketi = new QLabel("Transfer Bilgileri", this);
    baslik_etiketi->setAlignment(Qt::AlignCenter);

    alici_hesap_input = new QLineEdit(this);
    alici_hesap_input->setPlaceholderText("Alıcı Hesap No (Örn: 1234567890)");

    tutar_input = new QLineEdit(this);
    tutar_input->setPlaceholderText("Tutar (TL)");
    tutar_input->setValidator(new QDoubleValidator(0.01, 1000000.0, 2, this));

    transfer_butonu = new QPushButton("Transfer Yap", this);

    QVBoxLayout* ana_duzen = new QVBoxLayout(this);
    ana_duzen->addWidget(baslik_etiketi);
    ana_duzen->addSpacing(15);
    ana_duzen->addWidget(alici_hesap_input);
    ana_duzen->addSpacing(10);
    ana_duzen->addWidget(tutar_input);
    ana_duzen->addSpacing(25);
    ana_duzen->addWidget(transfer_butonu);

    connect(transfer_butonu, &QPushButton::clicked, this, &TransferWindow::transfer_islemini_baslat);
}

void TransferWindow::stil_uygula()
{
    this->setStyleSheet("background-color: #1a1a2e; color: white;");

    QString input_stili = "QLineEdit {"
                          "background-color: #16213e; "
                          "color: white; "
                          "border: 2px solid #e2b96f; "
                          "border-radius: 5px; "
                          "padding: 8px; "
                          "font-size: 14px;"
                          "}";
    alici_hesap_input->setStyleSheet(input_stili);
    tutar_input->setStyleSheet(input_stili);

    QString buton_stili = "QPushButton {"
                          "background-color: #e2b96f; "
                          "color: #1a1a2e; "
                          "font-weight: bold; "
                          "font-size: 14px;"
                          "border: none; "
                          "border-radius: 5px; "
                          "padding: 10px; "
                          "}"
                          "QPushButton:hover {"
                          "background-color: #f3c97f; "
                          "}";
    transfer_butonu->setStyleSheet(buton_stili);

    baslik_etiketi->setStyleSheet("font-size: 18px; font-weight: bold; color: #e2b96f; border: none;");
}

void TransferWindow::transfer_islemini_baslat()
{
    QString alici_hesap = alici_hesap_input->text();
    QString transfer_tutari = tutar_input->text();

    if (alici_hesap.isEmpty() || transfer_tutari.isEmpty())
    {
        QMessageBox::warning(this, "Hata", "Lütfen tüm alanları doldurun!");
        return;
    }

    // TODO(Abdullah): TransferServisi backend entegrasyonu burada yapilmalidir
    // TODO(Durancan): Aktif oturum acan gonderen kullanici bilgisi SistemKontrolcusu uzerinden buraya baglanmalidir

    QString dekont_mesaji = QString("Transfer Başarıyla Gerçekleşti!\n\nAlıcı Hesap: %1\nTutar: %2 TL\n\nBizi tercih ettiğiniz için teşekkür ederiz.")
                                .arg(alici_hesap)
                                .arg(transfer_tutari);

    QMessageBox dekont_popup(this);
    dekont_popup.setWindowTitle("İşlem Dekontu");
    dekont_popup.setText(dekont_mesaji);

    QString popup_stili = "QMessageBox { background-color: #1a1a2e; border: 1px solid #e2b96f; }"
                          "QLabel { color: white; font-size: 14px; }"
                          "QPushButton { background-color: #e2b96f; color: #1a1a2e; font-weight: bold; padding: 8px 15px; border-radius: 4px; }";
    dekont_popup.setStyleSheet(popup_stili);

    dekont_popup.exec();

    this->accept();
}
