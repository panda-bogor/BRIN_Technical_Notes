
# 04.1 – Introduction to Interface: Operating Condition

## 1. Deskripsi

Percobaan ini bertujuan untuk memahami karakteristik
tegangan kerja (operating voltage) pada microcontroller,
khususnya perbedaan antara tegangan catu daya dan level
logika digital (HIGH dan LOW).

Pengujian dilakukan menggunakan Arduino UNO berbasis
ATmega328P dengan melakukan pengukuran tegangan secara
langsung menggunakan digital multimeter.

## 2. Tujuan Percobaan

- Memahami operating voltage (12V, 5V, dan 3.3V).
- Membedakan supply voltage dan interface voltage.
- Memahami karakteristik logic HIGH dan LOW.
- Mengenal voltage tolerance dan 5V-tolerant I/O.
- Memahami fungsi voltage regulator dan level translator.
- Mengukur tegangan aktual pada digital pin Arduino UNO.

## 3. Perangkat yang Digunakan

| Komponen | Keterangan |
|---|---|
| Microcontroller | Arduino UNO (ATmega328P) |
| Software | VS Code + PlatformIO |
| Framework | Arduino |
| Power Supply | USB (nominal 5V) |
| Digital Output | D9 (LED + resistor 330Ω) |
| Digital Input | D2 (Push Button) |
| Alat Ukur | Digital Multimeter |

## 4. Implementasi Percobaan

Push button dihubungkan ke pin D2 dengan konfigurasi
INPUT_PULLUP, sedangkan LED dihubungkan ke pin D9
sebagai digital output.

Setiap penekanan tombol yang valid akan mengubah
kondisi LED secara bergantian (ON/OFF).

Program menggunakan metode software debouncing
berbasis millis() dengan interval sebesar 50 ms.

Pengukuran tegangan dilakukan pada beberapa kondisi:

1. Tegangan rail 5V terhadap GND.
2. Tegangan output D9 ketika HIGH (LED ON).
3. Tegangan output D9 ketika LOW (LED OFF).
4. Tegangan input D2 dengan konfigurasi INPUT_PULLUP.

## 5. Konfigurasi Pin

| Pin | Mode | Fungsi |
|---|---|---|
| D9 | OUTPUT | Mengendalikan LED |
| D2 | INPUT_PULLUP | Membaca push button |
| 5V | Power | Titik pengukuran tegangan rail |
| GND | Reference | Referensi pengukuran |

## 6. Konfigurasi PlatformIO

Project dikembangkan menggunakan framework Arduino
melalui PlatformIO pada VS Code.

Isi file `platformio.ini`:

    [env:uno]
    platform = atmelavr
    board = uno
    framework = arduino
    monitor_speed = 9600

## 7. Source Code

Source code utama tersedia pada:

`src/main.cpp`

Program digunakan untuk mengatur perubahan status
digital output D9 berdasarkan input dari push button D2.

## 8. Dokumentasi Percobaan

Dokumentasi lengkap yang mencakup dasar teori,
wiring diagram, foto pengukuran, tabel hasil percobaan,
dan analisis teknis tersedia pada Technical Notes.

**Technical Notes:**

[Introduction to Interface Operating Condition](MASUKKAN_LINK_TN_DI_SINI)

## 9. Penulis

Senthelee Vannessa Lai

D4 Teknologi Rekayasa Komputer  
Sekolah Vokasi, IPB University

Magang BRIN – Kelompok Riset Embedded Electronics System
