#ifndef ADMINDASHBOARD_H
#define ADMINDASHBOARD_H

#include <QWidget>
#include <QTableWidget>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QComboBox>
#include <QLineEdit>

class AdminDashboard : public QWidget {
    Q_OBJECT

public:
    explicit AdminDashboard(QWidget* parent = nullptr);
    ~AdminDashboard();

private slots:
    void onHesapDondurClicked();
    void onCikisClicked();
    void onYeniMusteriClicked();

private:
    // Üst bar
    QLabel*      baslikLabel;
    QPushButton* cikisButon;

    // Müşteriler
    QLabel*       musteriBaslik;
    QTableWidget* musteriTablo;
    QPushButton*  hesapDondurButon;
    QPushButton*  yeniMusteriButon;

    // Loglar
    QLabel*       logBaslik;
    QTableWidget* logTablo;

    void musterileriYukle();
    void loglarıYukle();
    void onFiltreClicked();

    QLineEdit*  aramaInput;
    QComboBox*  filtreCombo;
    QPushButton* filtreButon;
};

#endif // ADMINDASHBOARD_H
