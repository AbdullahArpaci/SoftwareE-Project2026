CREATE TABLE KULLANICI (
    kullanici_id INTEGER PRIMARY KEY AUTOINCREMENT,
    kimlik_no    VARCHAR(11)  NOT NULL UNIQUE,
    ad           VARCHAR(50)  NOT NULL,
    soyad        VARCHAR(50)  NOT NULL,
    email        VARCHAR(100) UNIQUE,
    telefon      VARCHAR(15),
    sifre_hash   VARCHAR(255) NOT NULL,
    rol          VARCHAR(20)  NOT NULL DEFAULT 'musteri',
    kayit_tarihi DATETIME     DEFAULT (datetime('now')),
    aktif        BOOLEAN      DEFAULT 1
);

CREATE TABLE HESAP (
    hesap_id         INTEGER     PRIMARY KEY AUTOINCREMENT,
    hesap_no         VARCHAR(26) NOT NULL UNIQUE,
    kullanici_id     INTEGER     NOT NULL,
    hesap_tipi       VARCHAR(20) NOT NULL DEFAULT 'vadesiz',
    bakiye           REAL        NOT NULL DEFAULT 0.0,
    para_birimi      VARCHAR(5)  NOT NULL DEFAULT 'TRY',
    olusturma_tarihi DATETIME    DEFAULT (datetime('now')),
    donduruldu       BOOLEAN     DEFAULT 0,
    aktif            BOOLEAN     DEFAULT 1,

    FOREIGN KEY (kullanici_id) REFERENCES KULLANICI(kullanici_id)
);

CREATE TABLE ISLEM (
    islem_id         INTEGER      PRIMARY KEY AUTOINCREMENT,
    gonderici_hesap  VARCHAR(26)  NOT NULL,
    alici_hesap      VARCHAR(26),

    tutar            REAL         NOT NULL,
    islem_tipi       VARCHAR(20)  NOT NULL,

    durum            VARCHAR(20)  NOT NULL DEFAULT 'beklemede',

    zaman_damgasi    DATETIME     DEFAULT (datetime('now')),
    aciklama         VARCHAR(255),

    FOREIGN KEY (gonderici_hesap) REFERENCES HESAP(hesap_no)
);

CREATE TABLE DEKONT (
    dekont_id        INTEGER     PRIMARY KEY AUTOINCREMENT,
    islem_id         INTEGER     NOT NULL UNIQUE,

    dekont_no        VARCHAR(50) NOT NULL UNIQUE,
    olusturma_tarihi DATETIME    DEFAULT (datetime('now')),
    detay_json       TEXT,

    FOREIGN KEY (islem_id) REFERENCES ISLEM(islem_id)
);

CREATE TABLE KREDI (
    kredi_id         INTEGER     PRIMARY KEY AUTOINCREMENT,
    kullanici_id     INTEGER     NOT NULL,
    hesap_no         VARCHAR(26) NOT NULL,
    kredi_tutari     REAL        NOT NULL,
    faiz_orani       REAL        NOT NULL,
    taksit_sayisi    INTEGER     NOT NULL,
    odenen_taksit    INTEGER     DEFAULT 0,
    aylik_taksit     REAL        NOT NULL,
    durum            VARCHAR(20) DEFAULT 'beklemede',

    red_gerekce      VARCHAR(255),
    kredi_skoru      INTEGER,
    basvuru_tarihi   DATETIME    DEFAULT (datetime('now')),
    onay_tarihi      DATETIME,

    FOREIGN KEY (kullanici_id) REFERENCES KULLANICI(kullanici_id),
    FOREIGN KEY (hesap_no)     REFERENCES HESAP(hesap_no)
);

CREATE TABLE LOG_KAYIT (
    kayit_id         INTEGER     PRIMARY KEY AUTOINCREMENT,
    kullanici_id     INTEGER     NOT NULL,
    zaman_damgasi    DATETIME    DEFAULT (datetime('now')),
    olay_tipi        VARCHAR(50) NOT NULL,


    ip_adresi        VARCHAR(45),
    detaylar         TEXT,

    FOREIGN KEY (kullanici_id) REFERENCES KULLANICI(kullanici_id)
);

CREATE TABLE BILDIRIM (
    bildirim_id      INTEGER     PRIMARY KEY AUTOINCREMENT,
    kullanici_id     INTEGER     NOT NULL,
    tip              VARCHAR(20) NOT NULL,

    baslik           VARCHAR(100),
    icerik           TEXT,
    okundu           BOOLEAN     DEFAULT 0,
    olusturma_tarihi DATETIME    DEFAULT (datetime('now')),

    FOREIGN KEY (kullanici_id) REFERENCES KULLANICI(kullanici_id)
);