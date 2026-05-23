#ifndef CUSTOMERPROFILEDIALOG_H
#define CUSTOMERPROFILEDIALOG_H

#include <QDialog>
#include "Kullanici.h"

namespace Ui {
class CustomerProfileDialog;
}

class CustomerProfileDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CustomerProfileDialog(Kullanici* kullanici, QWidget *parent = nullptr);
    ~CustomerProfileDialog();

private slots:
    void on_btnKapat_clicked();
    void on_btnSifreDegistir_clicked();

private:
    Ui::CustomerProfileDialog *ui;
    Kullanici* m_kullanici;
};

#endif // CUSTOMERPROFILEDIALOG_H
