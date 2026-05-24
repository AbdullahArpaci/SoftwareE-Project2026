# Banka Yonetim Sistemi

BIL 204 Yazilim Muhendisligi dersi kapsaminda gelistirilmis masaustu bankacilik simulasyonu.

Grup 2 | Necmettin Erbakan Universitesi | Bilgisayar Muhendisligi

GitHub: https://github.com/AbdullahArpaci/SoftwareE-Project2026

---

## Teknolojiler

- C++17
- Qt 6.x Framework
- SQLite
- Git / GitHub

---

## Sistem Gereksinimleri

- Qt 6.x Framework (MinGW 64-bit): https://www.qt.io/download
- Qt Creator IDE (Qt kurulumu ile birlikte gelir)
- Git: https://git-scm.com/downloads
- DB Browser for SQLite: https://sqlitebrowser.org

---

## Kurulum

### Adim 1 — Repoyu Klonlayin

```bash
git clone https://github.com/AbdullahArpaci/SoftwareE-Project2026.git
cd SoftwareE-Project2026
```

### Adim 2 — Qt Creator'da Acin

1. Qt Creator'i baslatin
2. File > Open File or Project secin
3. BankaYonetimiSistemi.pro dosyasini acin
4. Configure Project ekraninda Desktop Qt 6.x MinGW 64-bit secin
5. OK tiklayin

### Adim 3 — Veritabanini Kurun

**3.1. Projeyi derleyin:**

Qt Creator icerisinde Build > Build Project yolunu izleyin.
Bu adim debug klasorunu otomatik olusturur.

**3.2. Debug klasorunu bulun:**

```
Windows:
proje_klasoru/build/Desktop_Qt_6_x_MinGW_64_bit-Debug/debug/
```

**3.3. SQLite dosyasi olusturun:**

- DB Browser for SQLite'i acin
- New Database tiklayin
- Debug klasorune gidin
- Dosya adini banka.sqlite olarak belirleyin ve kaydedin

**3.4. Tablolari olusturun:**

- DB Browser'da Execute SQL sekmesine gecin
- src/database/schema.sql dosyasinin icerigini kopyalayip yapistirin
- Execute butonuna basin

**3.5. Test verilerini ekleyin:**

```sql
-- Kullanicilar
INSERT INTO KULLANICI (kimlik_no, ad, soyad, email, telefon, sifre_hash, rol)
VALUES ('12345678901', 'Ahmet', 'Yilmaz', 'ahmet@mail.com', '05321234567', 'hash_buraya', 'musteri');

INSERT INTO KULLANICI (kimlik_no, ad, soyad, email, telefon, sifre_hash, rol)
VALUES ('23456789012', 'Ayse', 'Kara', 'ayse@mail.com', '05331234567', 'hash_buraya', 'musteri');

INSERT INTO KULLANICI (kimlik_no, ad, soyad, email, telefon, sifre_hash, rol)
VALUES ('98765432100', 'Fatma', 'Kaya', 'fatma@mail.com', '05351234567', 'hash_buraya', 'yonetici');

-- Hesaplar
INSERT INTO HESAP (hesap_no, kullanici_id, hesap_tipi, bakiye, para_birimi)
VALUES ('TR001', 1, 'vadesiz', 50000.0, 'TRY');

INSERT INTO HESAP (hesap_no, kullanici_id, hesap_tipi, bakiye, para_birimi)
VALUES ('TR002', 1, 'vadeli', 25000.0, 'TRY');

INSERT INTO HESAP (hesap_no, kullanici_id, hesap_tipi, bakiye, para_birimi)
VALUES ('TR003', 2, 'vadesiz', 15000.0, 'TRY');

INSERT INTO HESAP (hesap_no, kullanici_id, hesap_tipi, bakiye, para_birimi)
VALUES ('TR004', 3, 'vadesiz', 100000.0, 'TRY');
```

### Adim 4 — Calistirin

Qt Creator icerisinde Ctrl + R tusuna basin.
Banka Yonetim Sistemi giris ekrani basariyla acilacaktir.

---

## Test Kullanici Bilgileri

| Rol       | TC Kimlik No | Sifre      |
|-----------|-------------|------------|
| Musteri   | 12345678901 | hash_buraya |
| Musteri   | 23456789012 | hash_buraya |
| Yonetici  | 98765432100 | hash_buraya |


---

## Grup Uyeleri

- Abdullah Arpaci — 23100011033
- Yemliha Can Yasti — 24100011016
- Duran Can Cetin — 24100011024
- Yasar Samet Ucoglan — 24100011032
- Muhammed Yusuf Erzi — 24100011052
