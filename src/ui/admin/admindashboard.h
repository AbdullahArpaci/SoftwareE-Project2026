#ifndef ADMINDASHBOARD_H
#define ADMINDASHBOARD_H

#include <QWidget>
#include <QTableWidget>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QHeaderView>

class AdminDashboard : public QWidget {
    Q_OBJECT

public:
    explicit AdminDashboard(QWidget* parent = nullptr);
    ~AdminDashboard();

private slots:
    void onHesapDondurClicked();
    void onCikisClicked();

private:
    // Üst bar
    QLabel*      baslikLabel;
    QPushButton* cikisButon;

    // Müşteriler
    QLabel*       musteriBaslik;
    QTableWidget* musteriTablo;
    QPushButton*  hesapDondurButon;

    // Loglar
    QLabel*       logBaslik;
    QTableWidget* logTablo;

    void musterileriYukle();
    void loglarıYukle();
};

#endif // ADMINDASHBOARD_H