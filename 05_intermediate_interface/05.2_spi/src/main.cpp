// Pending Hardware Verification - BELUM DIUJI SECARA FISIK.
// UNO berlogika 5V: gunakan level translator sebelum flash 3,3V.
// Sesuaikan juga jalur balik MISO dan pastikan suplai flash mencukupi.
#include <Arduino.h>
#include <SPI.h>

constexpr uint8_t FLASH_CS_PIN = 10;
constexpr uint8_t READ_JEDEC_ID = 0x9F;
constexpr unsigned long SPI_CLOCK_HZ = 500000UL;
constexpr unsigned long READ_INTERVAL_MS = 2000UL;

const SPISettings flashSettings(SPI_CLOCK_HZ, MSBFIRST, SPI_MODE0);
unsigned long lastReadMs = 0;

struct JedecId {
    uint8_t manufacturer;
    uint8_t memoryType;
    uint8_t capacity;
};

JedecId readJedecId() {
    JedecId id{};
    SPI.beginTransaction(flashSettings);
    digitalWrite(FLASH_CS_PIN, LOW);

    SPI.transfer(READ_JEDEC_ID);
    // Byte 0x00 hanya menyediakan clock untuk menerima tiga byte ID.
    // Perintah 0x9F ini tidak membutuhkan alamat atau dummy-cycle tambahan.
    id.manufacturer = SPI.transfer(0x00);
    id.memoryType = SPI.transfer(0x00);
    id.capacity = SPI.transfer(0x00);

    digitalWrite(FLASH_CS_PIN, HIGH);
    SPI.endTransaction();
    return id;
}

void printHexByte(uint8_t value) {
    if (value < 0x10) Serial.print('0');
    Serial.print(value, HEX);
}

void printJedecId(const JedecId &id) {
    Serial.print(F("JEDEC ID: "));
    printHexByte(id.manufacturer);
    Serial.print(' ');
    printHexByte(id.memoryType);
    Serial.print(' ');
    printHexByte(id.capacity);
    Serial.println();

    const bool allZero = id.manufacturer == 0x00 &&
                         id.memoryType == 0x00 && id.capacity == 0x00;
    const bool allOnes = id.manufacturer == 0xFF &&
                         id.memoryType == 0xFF && id.capacity == 0xFF;
    if (allZero || allOnes) {
        Serial.println(F("Respons mencurigakan: periksa power, wiring, CS, dan level translator."));
    } else if (id.manufacturer == 0xEF) {
        Serial.println(F("Manufacturer cocok dengan Winbond; cocokkan seluruh ID dengan datasheet IC."));
    } else {
        Serial.println(F("Manufacturer tidak sesuai ekspektasi Winbond; verifikasi IC dan komunikasi."));
    }
    // Respons saja belum membuktikan komunikasi benar; verifikasi semua byte.
}

void setup() {
    // Set latch HIGH sebelum OUTPUT agar CS tidak sengaja aktif saat setup.
    digitalWrite(FLASH_CS_PIN, HIGH);
    pinMode(FLASH_CS_PIN, OUTPUT);  // D10/SS harus OUTPUT pada UNO master.
    SPI.begin();                  // MOSI=D11, MISO=D12, SCK=D13.
    Serial.begin(9600);
    Serial.println(F("Pending Hardware Verification - BELUM DIUJI SECARA FISIK"));
    Serial.println(F("UNO + W25Qxx: JEDEC 0x9F, mode 0, MSB-first, 500 kHz."));
    Serial.println(F("Gunakan suplai flash 3,3V dan penyesuaian level logika."));
    lastReadMs = millis();  // Pembacaan pertama setelah sekitar 2 detik.
}

void loop() {
    const unsigned long now = millis();
    // Selisih unsigned aman terhadap rollover millis().
    if (now - lastReadMs >= READ_INTERVAL_MS) {
        lastReadMs = now;
        const JedecId id = readJedecId();
        // Cetak setelah CS kembali HIGH dan transaksi SPI selesai.
        printJedecId(id);
    }
    // Tidak menggunakan delay() atau perintah program/erase flash.
}
