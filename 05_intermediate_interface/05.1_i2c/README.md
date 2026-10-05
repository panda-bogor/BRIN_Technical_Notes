# 05.1 — Pengujian LCD 16x2 melalui I2C

## Tujuan

Menguji komunikasi Arduino UNO (ATmega328P) dengan LCD karakter 16x2 melalui backpack PCF8574. Dua halaman berganti setiap 2 detik menggunakan `millis()`, tanpa `delay()` untuk penjadwalan di `loop()`.

## Perangkat dan konfigurasi

- Arduino UNO dengan ATmega328P dan kabel USB data.
- LCD 16x2 kompatibel HD44780 dengan backpack I2C PCF8574.
- Kabel jumper.
- PlatformIO dengan framework Arduino; board ID `uno`, platform `atmelavr`.
- Library `marcoschwartz/LiquidCrystal_I2C` versi `1.1.4`, dipilih eksplisit untuk menghindari tertukar dengan library bernama serupa yang API-nya berbeda.

## Struktur proyek

- `README.md`: wiring, prosedur pengujian, dan status validasi.
- `platformio.ini`: konfigurasi board, framework, library, dan Serial Monitor.
- `src/main.cpp`: pemindaian alamat I2C dan pengujian tampilan.

Buka folder `05_intermediate_interface/05.1_i2c/` sebagai proyek PlatformIO, bukan akar repository.

## Wiring

Matikan catu daya sebelum merangkai. Periksa label pin pada backpack; jangan hanya mengandalkan urutan fisiknya.

| Pin LCD/backpack | Pin Arduino UNO | Keterangan |
| --- | --- | --- |
| VCC | 5V | Catu daya modul LCD 5V |
| GND | GND | Ground bersama |
| SDA | A4 / SDA | Jalur data I2C |
| SCL | A5 / SCL | Jalur clock I2C |

Pada UNO R3, header SDA/SCL terhubung ke jalur yang sama dengan A4/A5. Rangkaian ini menggunakan domain logika 5V UNO; bukan wiring untuk ESP8266 3,3V.

## Verifikasi alamat I2C

`LCD_ADDRESS` diawali dengan alamat **7-bit `0x27`**, tetapi alamat ini belum dikonfirmasi. Program memindai alamat 1–126 sekali saat `setup()` dan menampilkan perangkat yang memberi ACK pada Serial Monitor 9600 baud.

1. Hubungkan hanya backpack LCD saat memverifikasi identitasnya.
2. Build dan upload kode, lalu buka Serial Monitor. Tekan reset UNO jika keluaran awal terlewat.
3. Catat alamat yang merespons. ACK menunjukkan respons perangkat I2C, bukan bukti identitas LCD atau keberhasilan tampilan.
4. Bila alamatnya berbeda, ubah `LCD_ADDRESS` pada `src/main.cpp` sesuai hasil pemindaian, kemudian build dan upload ulang. `0x3F` dapat ditemukan pada sebagian backpack varian PCF8574A; jangan langsung menganggapnya alamat modul ini.
5. Jika alamat yang dipilih tidak merespons, program melewati inisialisasi LCD dan meminta pemeriksaan wiring/alamat. Setelah perbaikan, reset atau upload ulang; kode tidak mencoba menyambungkan ulang secara otomatis.

## Build, upload, dan Serial Monitor

Gunakan tombol Build, Upload, dan Monitor di PlatformIO, atau jalankan dari folder proyek:

```sh
pio run
pio run --target upload
pio device monitor --baud 9600
```

PlatformIO mengunduh dependensi ketika diperlukan. Jika port tidak terdeteksi otomatis, tentukan `upload_port` dan `monitor_port` sesuai port komputer yang digunakan.

## Perilaku yang diharapkan

| Halaman | Baris 1 | Baris 2 |
| --- | --- | --- |
| Awal | `BRIN - Uji I2C` | `LCD 16x2 PCF8574` |
| Berikutnya | `UNO + millis()` | `Ganti: 1` |

Halaman berganti setiap sekitar 2 detik. Counter bertambah setiap pergantian; halaman counter menampilkan 1, 3, 5, dan seterusnya karena hanya muncul pada halaman kedua. Counter tampilan dibatasi 9 digit agar muat pada LCD. Saat reset, counter kembali nol.

Selisih waktu menggunakan aritmetika `unsigned long` agar penjadwalan tetap bekerja saat `millis()` rollover. Baris dibersihkan dengan spasi sebelum ditulis ulang untuk menghindari sisa karakter; `lcd.clear()` tidak dipanggil berulang dalam `loop()`.

**Batas non-blocking:** penjadwalan halaman memakai `millis()`, tetapi transaksi `Wire`, penulisan LCD, dan waktu tunggu internal library tetap sinkron. Ini bukan implementasi I2C asinkron atau jaminan seluruh eksekusi bebas blocking.

## Langkah pengujian fisik

1. Periksa wiring, ground, dan catu daya.
2. Build proyek dan catat hasilnya; lanjutkan upload bila build berhasil.
3. Verifikasi alamat melalui Serial Monitor.
4. Pastikan backlight dan tulisan terlihat; atur trimpot kontras secara perlahan.
5. Amati pergantian kedua halaman selama beberapa siklus. Periksa dua baris, counter, karakter tersisa, dan kedipan.
6. Tekan reset dan pastikan tampilan/counter kembali ke kondisi awal.
7. Catat tanggal, alamat, versi perangkat, hasil build/upload, dan dokumentasi foto. Ubah status pengujian hanya setelah eksperimen dilakukan.

## Troubleshooting

| Gejala | Pemeriksaan |
| --- | --- |
| Tidak ada alamat terdeteksi | Catu daya, ground, SDA/SCL tertukar, sambungan kabel, serta pull-up backpack |
| Backlight menyala tetapi tulisan tidak terlihat | Trimpot kontras, alamat I2C, dan kompatibilitas mapping pin backpack dengan library |
| Kotak gelap atau karakter salah | Kontras, koneksi, dan keberhasilan inisialisasi LCD |
| Library gagal ditemukan atau API berbeda | Pastikan dependensi persis seperti `platformio.ini`; jangan mengganti library hanya berdasarkan nama header |

## Status validasi

| Pemeriksaan | Status |
| --- | --- |
| Peninjauan source code dan konfigurasi | Ditinjau secara statis |
| Build PlatformIO untuk UNO | Belum dijalankan |
| Upload ke UNO | Belum dilakukan |
| Alamat I2C backpack aktual | Belum diverifikasi |
| Tampilan dan pergantian halaman pada LCD | Belum diuji secara fisik |

## Referensi

- [PlatformIO: Arduino UNO](https://docs.platformio.org/en/latest/boards/atmelavr/uno.html)
- [Library LiquidCrystal_I2C](https://github.com/johnrickman/LiquidCrystal_I2C)
- [Arduino: millis()](https://docs.arduino.cc/language-reference/en/functions/time/millis/)
