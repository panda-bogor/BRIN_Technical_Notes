# 05.2 — Pengujian SPI W25Qxx: Read JEDEC ID


## Tujuan

Menguji komunikasi Arduino UNO (ATmega328P) dengan SPI Flash Memory W25Qxx varian 3,3 V menggunakan perintah Read JEDEC ID `0x9F`. Program membaca tiga byte identitas secara berkala dan menampilkannya di Serial Monitor 9600 baud. Praktikum ini tidak menjalankan write enable, program, atau erase.

## Dasar singkat SPI

SPI memakai SCK untuk clock, MOSI/COPI untuk data dari UNO, MISO/CIPO untuk data menuju UNO, dan CS untuk memilih flash. CS flash aktif LOW. Setelah CS diturunkan, UNO mengirim `0x9F` lalu menghasilkan clock untuk menerima Manufacturer ID, Memory Type, dan Capacity. CS tetap LOW selama seluruh urutan dan kembali HIGH sesudahnya.

Konfigurasi awal: **500 kHz, MSB-first, SPI mode 0 (CPOL=0, CPHA=0)**. Ini pilihan awal untuk pengujian dengan kabel pendek; verifikasi dukungan mode, timing, dan karakteristik translator terhadap datasheet IC yang benar-benar digunakan.

## Perangkat

- Arduino UNO ATmega328P, kabel USB data, dan PlatformIO dengan framework Arduino.
- IC/modul W25Qxx **varian 3,3 V** dengan identitas lengkap yang dapat dibaca.
- Suplai 3,3 V teratur dengan kemampuan arus memadai untuk flash dan rangkaian translator, termasuk kebutuhan maksimum dan transien menurut datasheet.
- Level translator/buffer untuk SPI push-pull: tiga kanal 5 V menuju 3,3 V dan satu kanal 3,3 V menuju 5 V.
- Kabel pendek, multimeter, serta decoupling sesuai rekomendasi komponen. Untuk IC lepas, mulai dengan kapasitor keramik 100 nF dekat VCC–GND dan kapasitor suplai pendukung sesuai rancangan regulator.
- Logic analyzer/osiloskop bila tersedia untuk memeriksa clock dan tegangan sinyal.

Jangan menganggap semua suffix W25Qxx memiliki tegangan yang sama: cek marking dan datasheet. Project ini tidak ditujukan untuk varian 1,8 V. Periksa skematik modul; regulator di modul tidak otomatis berarti input logikanya tahan 5 V.

## Konfigurasi pin UNO

| Fungsi | Pin UNO | Arah |
| --- | --- | --- |
| CS / SS | D10 | UNO menuju flash |
| MOSI / COPI | D11 | UNO menuju flash |
| MISO / CIPO | D12 | Flash menuju UNO |
| SCK | D13 | UNO menuju flash |
| GND | GND | Ground bersama |

SCK, MOSI, dan MISO juga tersedia di header ICSP UNO. D10 tetap dipakai sebagai CS dan diatur OUTPUT agar UNO tetap beroperasi sebagai SPI master.

## Wiring dengan penyesuaian level logika

**Jangan menyambungkan D10, D11, atau D13 yang berlogika 5 V langsung ke input flash 3,3 V. Jangan memberikan 5 V pada VCC flash.** Sambungkan dengan daya dimatikan dan periksa lagi sebelum menyalakan.

| Sumber | Jalur penyesuaian level | Tujuan |
| --- | --- | --- |
| UNO D10 | Kanal 5 V → 3,3 V | Flash /CS |
| UNO D11 | Kanal 5 V → 3,3 V | Flash DI / IO0 / MOSI |
| UNO D13 | Kanal 5 V → 3,3 V | Flash CLK / SCK |
| Flash DO / IO1 / MISO | Kanal 3,3 V → 5 V | UNO D12 |
| Suplai 3,3 V | Langsung sesuai domain suplai | Flash VCC |
| Ground suplai, UNO, translator | Ground bersama | Flash GND |
| Rail 3,3 V | Pull-up sekitar 10 kΩ | Flash /CS, agar tidak terpilih saat UNO reset |

Untuk SPI standar, pin /WP dan /HOLD atau /RESET yang berlaku pada IC tersebut perlu berada pada keadaan tidak aktif sesuai datasheet, misalnya pull-up ke **3,3 V**, bukan 5 V. Jangan biarkan input kontrol mengambang. Nomor pin fisik bergantung pada package; cocokkan label di atas dengan datasheet/skematik modul, bukan hanya posisi konektor.

Contoh pilihan buffer untuk rangkaian satu flash:

- **SN74LVC125A**, diberi VCC 3,3 V, dapat dipakai untuk tiga jalur UNO menuju flash karena inputnya menerima hingga 5,5 V. Pastikan part yang digunakan benar-benar memiliki kemampuan ini.
- **SN74AHCT125**, diberi VCC 5 V dan memiliki input kompatibel TTL, dapat dipakai untuk jalur MISO 3,3 V menuju UNO. Jangan memakai jenis HC sebagai pengganti tanpa memeriksa ambang inputnya.

Implementasi buffer harus mengikuti datasheet, termasuk pin enable aktif LOW, decoupling, input kanal yang tidak digunakan, dan perilaku saat salah satu rail mati. Untuk rangkaian satu flash, MISO dapat di-enable hanya saat flash dipilih; untuk bus bersama, outputnya wajib high-impedance ketika tidak dipilih. Jaga output translator tidak aktif saat suplai belum stabil, dan cegah back-powering.

Pilih translator yang sesuai untuk SPI push-pull dan clock yang digunakan. Modul BSS138 umum untuk I2C/open-drain tidak boleh diasumsikan cocok untuk rangkaian SPI ini. Sambungan MISO langsung 3,3 V ke UNO 5 V juga tidak diasumsikan memenuhi margin logika; rancangan di atas memakai penyesuaian level pada jalur balik.

**Suplai:** hitung kebutuhan total dari spesifikasi maksimum komponen dan beri margin. Jangan menganggap pin 3V3 UNO atau regulator modul otomatis mencukupi. Ukur rail 3,3 V pada flash saat aktif, dan pastikan tegangan stabil serta tidak melampaui batas IC. Jika memakai suplai eksternal, jangan menghubungkan dua output regulator 3,3 V menjadi satu; tetap satukan ground.

## Struktur dan konfigurasi PlatformIO

- `README.md`: dokumentasi dan status validasi.
- `platformio.ini`: environment `uno`, platform `atmelavr`, framework `arduino`, monitor 9600 baud.
- `src/main.cpp`: pembacaan JEDEC ID melalui library bawaan `SPI.h`.

Buka folder `05_intermediate_interface/05.2_spi/` sebagai proyek. `SPI.h` tersedia di framework Arduino AVR sehingga tidak perlu dependensi library flash tambahan.

## Penjelasan program

1. `setup()` membuat D10 OUTPUT dengan kondisi awal HIGH, menjalankan `SPI.begin()`, lalu membuka Serial 9600 baud.
2. `millis()` menjadwalkan pembacaan pertama setelah sekitar 2 detik dan mengulanginya setiap sekitar 2 detik. Selisih `unsigned long` tetap bekerja saat rollover.
3. `SPI.beginTransaction(SPISettings(500000, MSBFIRST, SPI_MODE0))` menerapkan konfigurasi transaksi sebelum CS LOW.
4. Kode mengirim `0x9F`, lalu tiga transfer `0x00` untuk menghasilkan clock pembacaan ID. Byte pengisi itu bukan perintah baru dan tidak menambahkan address/dummy-cycle ke protokol `0x9F`.
5. CS dikembalikan HIGH sebelum `SPI.endTransaction()`. Hasil dicetak setelah transaksi selesai.
6. Semua byte ditampilkan dalam dua digit heksadesimal. `FF FF FF` dan `00 00 00` diberi peringatan sebagai respons mencurigakan; `EF` pada Manufacturer ID cocok dengan Winbond, tetapi seluruh ID tetap harus dibandingkan dengan datasheet.

Penjadwalan tidak memakai `delay()`. Transfer SPI empat byte dan pencetakan Serial tetap sinkron; program ini bukan driver SPI asinkron. Kode hanya mengirim perintah baca ID dan tidak mengubah mode/perlindungan flash.

## Prosedur pengujian

1. Catat marking lengkap flash, package, dan skematik modul. Pastikan kompatibel dengan suplai 3,3 V dan mode SPI standar yang dipakai.
2. Dengan daya mati, rakit ground, suplai, translator, dan jalur SPI. Periksa arah kanal, pin enable, serta idle HIGH pada CS flash.
3. Verifikasi suplai dan level output translator sebelum menghubungkannya ke input flash. Gunakan multimeter untuk rail/DC dan osiloskop jika perlu memeriksa sinyal yang berubah.
4. Build proyek melalui PlatformIO atau dari folder project:

```sh
pio run
pio run --target upload
pio device monitor --baud 9600
```

5. Tentukan `upload_port`/`monitor_port` jika deteksi otomatis gagal. Buka Serial Monitor, kemudian reset UNO untuk melihat banner status.
6. Amati tiga byte ID setiap sekitar 2 detik. Bandingkan ketiganya dengan tabel JEDEC pada datasheet varian yang dipasang; jangan menetapkan satu ID untuk seluruh keluarga W25Qxx.
7. Ulangi beberapa siklus dan setelah reset. ID harus konsisten serta sesuai datasheet sebelum menyimpulkan komunikasi berhasil.
8. Catat versi board/flash, rail aktual, translator, clock, keluaran Serial, dan hasil build/upload. Lampirkan foto wiring atau capture analyzer bila tersedia.

Belum ada hasil pengukuran atau ID aktual dalam project ini. Ubah status hanya setelah pengujian nyata dilakukan.

## Troubleshooting

| Gejala | Pemeriksaan |
| --- | --- |
| Serial kosong | Port, kabel USB data, baud 9600, keberhasilan upload; reset setelah membuka monitor |
| `FF FF FF` | Flash tidak terpilih/tidak memberi data, MISO mengambang, power atau translator bermasalah; ini petunjuk, bukan diagnosis pasti |
| `00 00 00` | Jalur data tertahan LOW, sambungan salah, input kontrol atau suplai bermasalah; periksa level logika |
| ID berubah-ubah | Kabel terlalu panjang, ground/decoupling buruk, margin logika, enable translator, dan bentuk clock |
| ID stabil tetapi tidak cocok | Marking IC/varian, mode SPI, bit order, atau salah memilih perangkat |
| Flash tidak merespons | Selain wiring, periksa apakah perangkat berada di deep power-down atau mode lain; gunakan prosedur datasheet dan power-cycle yang benar, jangan mengirim reset sembarang |

Jika perlu, turunkan `SPI_CLOCK_HZ` untuk diagnosis dan dokumentasikan perubahan. Penurunan clock tidak menggantikan penyesuaian level tegangan.

## Status validasi

| Pemeriksaan | Status |
| --- | --- |
| Source code dan konfigurasi | Ditinjau secara statis |
| Build PlatformIO | Belum dijalankan |
| Upload ke Arduino UNO | Belum dilakukan |
| Suplai, translator, dan wiring aktual | Pending Hardware Verification |
| JEDEC ID dan kestabilan komunikasi | Pending Hardware Verification |

## Referensi

- [Arduino: SPI dan pin board](https://github.com/arduino/reference-en/blob/master/Language/Functions/Communication/SPI.adoc)
- [Winbond W25Q64JV datasheet, contoh varian — Read JEDEC ID](https://media.digikey.com/pdf/Data%20Sheets/Winbond%20PDFs/W25Q64JV_Rev_C.pdf)
- [TI: SN74LVC125A](https://www.ti.com/product/SN74LVC125A)
- [TI: SN74AHCT125](https://www.ti.com/product/SN74AHCT125)

Datasheet W25Q64JV di atas adalah contoh referensi; gunakan datasheet part lengkap milikmu untuk keputusan wiring, daya, timing, dan interpretasi ID.
