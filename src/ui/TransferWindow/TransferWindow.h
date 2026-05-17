#ifndef TRANSFERWINDOW_H
#define TRANSFERWINDOW_H

#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>

class TransferWindow : public QDialog
{
    Q_OBJECT

public:
    TransferWindow(QWidget *parent = nullptr);
    ~TransferWindow();

private slots:
    void transfer_islemini_baslat();

private:
    QLineEdit* alici_hesap_input;
    QLineEdit* tutar_input;
    QPushButton* transfer_butonu;
    QLabel* baslik_etiketi;

    void arayuzu_hazirla();
    void stil_uygula();
};

#endif // TRANSFERWINDOW_H
