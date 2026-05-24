#ifndef DEKONTSERVISI_H
#define DEKONTSERVISI_H

#include <QMainWindow>
#include <QString>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QDate>
QT_BEGIN_NAMESPACE
namespace Ui {
class DekontServisi;
}
QT_END_NAMESPACE

class DekontServisi : public QMainWindow
{
    Q_OBJECT

public:
    DekontServisi(QWidget *parent = nullptr);
    ~DekontServisi();

private slots:
    void on_btn_TXTolarakkaydet_clicked();

private:
    Ui::DekontServisi *ui;
    void dosyayayaz(QString gonder,QString al,QString tutarmiktari);
};
#endif // DEKONTSERVISI_H
