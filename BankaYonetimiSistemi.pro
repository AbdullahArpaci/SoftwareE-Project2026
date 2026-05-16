QT += core gui sql
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
CONFIG += c++17

INCLUDEPATH += src/database \
               src/models \
               src/services/sources \
               src/services/headers \
               src/ui \
               src/ui/customer \
               src/ui/admin \


HEADERS += \
    src/database/databasemanager.h \
    src/models/Hesap.h \
    src/models/Islem.h \
    src/models/Kullanici.h \
    src/models/Musteri.h \
    src/models/Yonetici.h \
    src/services/headers/HesapServisi.h \
    src/services/headers/TransferServisi.h \
    src/services/headers/SistemKontrolcusu.h \
    src/services/headers/LogServisi.h \
    src/ui/Customer/CustomerDashboard.h \
    src/ui/LoginWindow.h

SOURCES += \
    main.cpp \
    src/database/databasemanager.cpp \
    src/models/Hesap.cpp \
    src/models/Islem.cpp \
    src/models/Kullanici.cpp \
    src/models/Musteri.cpp \
    src/models/Yonetici.cpp \
    src/services/sources/HesapServisi.cpp \
    src/services/sources/TransferServisi.cpp \
    src/services/sources/SistemKontrolcusu.cpp \
    src/services/sources/LogServisi.cpp \
    src/ui/Customer/CustomerDashboard.cpp \
    src/ui/LoginWindow.cpp