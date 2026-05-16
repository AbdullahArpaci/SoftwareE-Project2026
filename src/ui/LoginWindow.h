#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>


class LoginWindow : public QWidget {
    Q_OBJECT

public:
    LoginWindow(QWidget* parent = nullptr);
    ~LoginWindow();

private slots:
    void onGirisClicked();

private:
    QLabel*      baslikLabel;
    QLabel*      altBaslikLabel;
    QLineEdit*   kimlikNoInput;
    QLineEdit*   sifreInput;
    QPushButton* girisButon;
    QLabel*      hataLabel;
};

#endif // LOGINWINDOW_H