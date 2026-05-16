#ifndef LOGSERVISI_H
#define LOGSERVISI_H

#include <QString>

class LogServisi 
{
public:
    LogServisi();
    ~LogServisi();

    bool logKaydet(int kullaniciID, QString olayTipi, QString detaylar);
};

#endif // LOGSERVISI_H
