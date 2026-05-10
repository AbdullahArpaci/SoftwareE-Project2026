#ifndef TRANSFERSERVISI_H
#define TRANSFERSERVISI_H

#include <QString>

class TransferServisi {
public:
    TransferServisi();
    ~TransferServisi();

    bool transferYap(QString gonderen, QString alici, double tutar);
    bool aliciHesapDogrula(QString hesapNo);
};

#endif // TRANSFERSERVISI_H
