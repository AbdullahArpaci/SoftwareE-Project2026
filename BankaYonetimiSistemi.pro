QT += core gui sql
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
CONFIG += c++17

TARGET = BankaYonetimSistemi
TEMPLATE = app

INCLUDEPATH += src/database \
               src/models \
               src/services \
               src/ui

SOURCES += \
    main.cpp \
    src/database/databasemanager.cpp \
    src/models/Kullanici.cpp \
    src/models/Musteri.cpp \
    src/models/Yonetici.cpp \
    src/models/Hesap.cpp \
    src/models/Islem.cpp \
    src/services/HesapServisi.cpp \
    src/services/TransferServisi.cpp \
    src/services/SistemKontrolcusu.cpp \
    src/services/LogServisi.cpp \

HEADERS += \
    src/database/databasemanager.h \
    src/models/Kullanici.h \
    src/models/Musteri.h \
    src/models/Yonetici.h \
    src/models/Hesap.h \
    src/models/Islem.h \
    src/services/HesapServisi.h \
    src/services/TransferServisi.h \
    src/services/SistemKontrolcusu.h \
    src/services/LogServisi.h \

FORMS += \
    src/ui/admindashboard.ui \
    src/ui/moneytransfer.ui \
    src/ui/receiptdialog.ui \
    src/ui/transactionhistorywindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target