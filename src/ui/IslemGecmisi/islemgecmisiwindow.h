#ifndef ISLEMGECMISIWINDOW_H
#define ISLEMGECMISIWINDOW_H

#include <QDialog>
#include <QTableWidget>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QHeaderView>
#include "Islem.h"

class IslemGecmisiWindow : public QDialog {
    Q_OBJECT

public:
    // Constructor parametresi olarak aktif hesap numarasını alıyoruz
    explicit IslemGecmisiWindow(const QString& hesapNo, QWidget* parent = nullptr);
    ~IslemGecmisiWindow();

private:
    QString m_hesapNo;
    QLabel* baslikLabel;
    QTableWidget* tabloIslemGecmisi;

    void arayuzuHazirla();
    void stilUygula();
    void tabloyuDoldur();
};

#endif // ISLEMGECMISIWINDOW_H
