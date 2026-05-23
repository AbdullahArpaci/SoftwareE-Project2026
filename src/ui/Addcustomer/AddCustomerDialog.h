#ifndef ADDCUSTOMERDIALOG_H
#define ADDCUSTOMERDIALOG_H

#include <QDialog>

namespace Ui {
class AddCustomerDialog;
}

class AddCustomerDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddCustomerDialog(QWidget *parent = nullptr);
    ~AddCustomerDialog();

private slots:
    void on_btnCancel_clicked();
    void on_btnSave_clicked();

private:
    Ui::AddCustomerDialog *ui;
};

#endif // ADDCUSTOMERDIALOG_H
