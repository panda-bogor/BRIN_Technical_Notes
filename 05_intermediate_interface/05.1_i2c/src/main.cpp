// STATUS: BELUM DIUJI SECARA FISIK pada Arduino UNO dan LCD.
#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Alamat awal; verifikasi melalui hasil pemindaian di Serial Monitor.
constexpr uint8_t LCD_ADDRESS = 0x27;
constexpr uint8_t LCD_COLUMNS = 16;
constexpr uint8_t LCD_ROWS = 2;
constexpr unsigned long PAGE_INTERVAL_MS = 2000UL;

LiquidCrystal_I2C lcd(LCD_ADDRESS, LCD_COLUMNS, LCD_ROWS);
unsigned long lastPageChangeMs = 0;
unsigned long pageChanges = 0;
bool secondPage = false;
bool lcdReady = false;

void scanI2c() {
    uint8_t found = 0;
    Serial.println(F("Pemindaian alamat I2C 7-bit:"));
    for (uint8_t address = 1; address < 127; ++address) {
        Wire.beginTransmission(address);
        const uint8_t error = Wire.endTransmission();
        if (error == 0) {
            Serial.print(F("ACK pada 0x"));
            if (address < 0x10) Serial.print('0');
            Serial.println(address, HEX);
            ++found;
        } else if (error == 4) {
            Serial.print(F("Kesalahan bus pada alamat "));
            Serial.println(address, HEX);
        }
    }
    if (found == 0) Serial.println(F("Tidak ada perangkat terdeteksi."));
    Serial.println(F("ACK belum membuktikan perangkat tersebut adalah LCD."));
}

// Tulis ulang satu baris tanpa lcd.clear() di loop agar mengurangi kedipan.
void clearRow(uint8_t row) {
    lcd.setCursor(0, row);
    lcd.print(F("                "));
    lcd.setCursor(0, row);
}

void renderPage() {
    clearRow(0);
    clearRow(1);
    lcd.setCursor(0, 0);
    if (!secondPage) {
        lcd.print(F("BRIN - Uji I2C"));
        lcd.setCursor(0, 1);
        lcd.print(F("LCD 16x2 PCF8574"));
    } else {
        lcd.print(F("UNO + millis()"));
        lcd.setCursor(0, 1);
        lcd.print(F("Ganti: "));
        // Maksimal 9 digit agar seluruh baris tetap muat dalam 16 kolom.
        lcd.print(pageChanges % 1000000000UL);
    }
}

void setup() {
    Serial.begin(9600);
    Serial.println(F("STATUS: BELUM DIUJI SECARA FISIK"));
    Wire.begin();  // Arduino UNO: SDA=A4, SCL=A5.
    Wire.setClock(100000UL);
    scanI2c();

    Wire.beginTransmission(LCD_ADDRESS);
    if (Wire.endTransmission() != 0) {
        Serial.print(F("Alamat LCD 0x"));
        Serial.print(LCD_ADDRESS, HEX);
        Serial.println(F(" tidak merespons."));
        Serial.println(F("Periksa wiring dan LCD_ADDRESS, lalu upload ulang."));
        return;
    }

    // Library memiliki waktu tunggu internal untuk inisialisasi/timing LCD.
    lcd.init();
    lcd.backlight();
    lcdReady = true;
    renderPage();
    lastPageChangeMs = millis();
    Serial.println(F("Uji tampilan dimulai; verifikasi tulisan pada LCD."));
}

void loop() {
    if (!lcdReady) return;

    const unsigned long now = millis();
    // Selisih unsigned tetap bekerja saat millis() mengalami rollover.
    if (now - lastPageChangeMs >= PAGE_INTERVAL_MS) {
        lastPageChangeMs = now;
        secondPage = !secondPage;
        ++pageChanges;
        renderPage();
    }
    // Tidak ada delay() untuk penjadwalan pergantian halaman.
}
