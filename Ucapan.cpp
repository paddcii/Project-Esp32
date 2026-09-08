#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

byte heartFull[8] = {
  0b00000,
  0b01010,
  0b11111,
  0b11111,
  0b11111,
  0b01110,
  0b00100,
  0b00000
};

byte heartEmpty[8] = {
  0b00000,
  0b01010,
  0b10101,
  0b10001,
  0b01010,
  0b00100,
  0b00000,
  0b00000
};

#define HATI_PENUH  "\x01"
#define HATI_KOSONG "\x02"

void jantungBerdetak(int kolom, int baris, int kali = 3) {
  for (int k = 0; k < kali; k++) {
    lcd.setCursor(kolom, baris);
    lcd.write(byte(2)); 
    delay(120);
    lcd.setCursor(kolom, baris);
    lcd.write(byte(1)); 
    delay(160);
  }
}

#define NOTE_B0  31
#define NOTE_C1  33
#define NOTE_CS1 35
#define NOTE_D1  37
#define NOTE_DS1 39
#define NOTE_E1  41
#define NOTE_F1  44
#define NOTE_FS1 46
#define NOTE_G1  49
#define NOTE_GS1 52
#define NOTE_A1  55
#define NOTE_AS1 58
#define NOTE_B1  62
#define NOTE_C2  65
#define NOTE_CS2 69
#define NOTE_D2  73
#define NOTE_DS2 78
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_FS2 93
#define NOTE_G2  98
#define NOTE_GS2 104
#define NOTE_A2  110
#define NOTE_AS2 117
#define NOTE_B2  123
#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951
#define NOTE_C8  4186
#define NOTE_CS8 4435
#define NOTE_D8  4699
#define NOTE_DS8 4978
#define REST      0

int tempo = 140;
int buzzer = 14;

int melody[] = {

  NOTE_C4,4, NOTE_C4,8,
  NOTE_D4,-4, NOTE_C4,-4, NOTE_F4,-4,
  NOTE_E4,-2, NOTE_C4,4, NOTE_C4,8,
  NOTE_D4,-4, NOTE_C4,-4, NOTE_G4,-4,
  NOTE_F4,-2, NOTE_C4,4, NOTE_C4,8,

  NOTE_C5,-4, NOTE_A4,-4, NOTE_F4,-4,
  NOTE_E4,-4, NOTE_D4,-4, NOTE_AS4,4, NOTE_AS4,8,
  NOTE_A4,-4, NOTE_F4,-4, NOTE_G4,-4,
  NOTE_F4,-2,

};

int notes = sizeof(melody) / sizeof(melody[0]) / 2;
int wholenote = (60000 * 4) / tempo;
int divider = 0, noteDuration = 0;

const char* pesanAtas[] = {
  "HAPPY BIRTHDAY",
  "UNTUK PACARKU",
  "SEMOGA HARIMU",
  "PANJANG UMUR",
  "AKU BERSYUKUR",
  "TERIMA KASIH",
  HATI_PENUH "I LOVE YOU" HATI_PENUH,
  "HAPPY"
};

const char* pesanBawah[] = {
  "RUMIDA DWINISA",
  "TERSAYANGKU",
  "PENUH BAHAGIA",
  "SEHAT SELALU",
  "PUNYA KAMU",
  "SUDAH HADIR",
  HATI_PENUH "MIDAAA " HATI_PENUH,
  "BIRTHDAY!! " HATI_PENUH
};

const int jumlahPesan = 8;

void bootAnimation() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("LOADING SYSTEM...");
  lcd.setCursor(0, 1);
  lcd.print("[              ]");

  for (int i = 0; i < 14; i++) {
    lcd.setCursor(1 + i, 1);
    lcd.print("#");

    if (i % 2 == 0) {
      tone(buzzer, NOTE_C5, 80);
      delay(100);
      noTone(buzzer);
    }
    delay(120);
  }

  delay(400);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("SYSTEM READY");
  lcd.setCursor(0, 1);
  lcd.print("MODE LOVE ON");

  for (int i = 0; i < 3; i++) {
    tone(buzzer, NOTE_A4, 150);
    delay(200);
    noTone(buzzer);
    delay(150);
  }

  delay(800);
}

void heartSplash() {
  lcd.clear();
  lcd.setCursor(3, 0);
  lcd.print("WITH LOVE");

  int tengah = 7;

  for (int jarak = 0; jarak <= tengah; jarak++) {
    int kolomKiri = tengah - jarak;
    int kolomKanan = tengah + 1 + jarak;

    for (int k = 0; k < 2; k++) {
      lcd.setCursor(kolomKiri, 1);
      lcd.write(byte(2));
      lcd.setCursor(kolomKanan, 1);
      lcd.write(byte(2));
      tone(buzzer, NOTE_E5, 50);
      delay(70);
      noTone(buzzer);

      lcd.setCursor(kolomKiri, 1);
      lcd.write(byte(1));
      lcd.setCursor(kolomKanan, 1);
      lcd.write(byte(1));
      delay(90);
    }
  }

  for (int k = 0; k < 3; k++) {
    for (int c = 0; c < 16; c++) {
      lcd.setCursor(c, 1);
      lcd.write(byte(2));
    }
    tone(buzzer, NOTE_E5, 80);
    delay(120);
    noTone(buzzer);

    for (int c = 0; c < 16; c++) {
      lcd.setCursor(c, 1);
      lcd.write(byte(1));
    }
    delay(150);
  }

  delay(700);
}

String tengahkanTeks(String teks) {
  int panjang = teks.length();
  if (panjang >= 16) return teks.substring(0, 16);

  int totalSpasi = 16 - panjang;
  int kiri = totalSpasi / 2;
  int kanan = totalSpasi - kiri;

  String hasil = "";
  for (int i = 0; i < kiri; i++) hasil += " ";
  hasil += teks;
  for (int i = 0; i < kanan; i++) hasil += " ";
  return hasil;
}

void cetakBarisAnimasi(String teks, int baris, int kaliDetak = 2) {
  int panjang = teks.length();
  for (int i = 0; i < panjang; i++) {
    char c = teks.charAt(i);
    lcd.setCursor(i, baris);
    if ((byte)c == 1) {
      jantungBerdetak(i, baris, kaliDetak);
    } else {
      lcd.print(c);
    }
  }
}

void tampilkanPesan(String atas, String bawah, int durasi = 1500) {
  lcd.clear();
  cetakBarisAnimasi(tengahkanTeks(atas), 0);
  cetakBarisAnimasi(tengahkanTeks(bawah), 1);
  delay(durasi);
}

void tampilkanPenutupDenganHati() {
  lcd.clear();

  String baris1 = "JANGAN LUPA";
  String baris2 = "MAKAN YA..";

  int lebar = 14;
  int pad1 = (lebar - baris1.length()) / 2;
  int pad2 = (lebar - baris2.length()) / 2;

  lcd.setCursor(1 + pad1, 0);
  lcd.print(baris1);
  lcd.setCursor(1 + pad2, 1);
  lcd.print(baris2);

  for (int k = 0; k < 6; k++) {
    lcd.setCursor(0, 0);  lcd.write(byte(2));
    lcd.setCursor(15, 0); lcd.write(byte(2));
    lcd.setCursor(0, 1);  lcd.write(byte(2));
    lcd.setCursor(15, 1); lcd.write(byte(2));

    tone(buzzer, NOTE_E5, 60);
    delay(140);
    noTone(buzzer);

    lcd.setCursor(0, 0);  lcd.write(byte(1));
    lcd.setCursor(15, 0); lcd.write(byte(1));
    lcd.setCursor(0, 1);  lcd.write(byte(1));
    lcd.setCursor(15, 1); lcd.write(byte(1));
    delay(160);
  }
}

void mainkanMusik() {
  for (int thisNote = 0; thisNote < notes * 2; thisNote = thisNote + 2) {

    divider = melody[thisNote + 1];
    if (divider > 0) {
      noteDuration = (wholenote) / divider;
    } else if (divider < 0) {
      noteDuration = (wholenote) / abs(divider);
      noteDuration *= 1.5;
    }

    tone(buzzer, melody[thisNote], noteDuration * 0.9);
    delay(noteDuration);
    noTone(buzzer);
  }
}

void mainkanMusikDenganTeksBerjalan() {
  int indexPesan = 1;
  const int notePerGantiPesan = 5;
  int hitungNote = 0;

  for (int thisNote = 0; thisNote < notes * 2; thisNote = thisNote + 2) {

    divider = melody[thisNote + 1];
    if (divider > 0) {
      noteDuration = (wholenote) / divider;
    } else if (divider < 0) {
      noteDuration = (wholenote) / abs(divider);
      noteDuration *= 1.5;
    }

    tone(buzzer, melody[thisNote], noteDuration * 0.9);
    delay(noteDuration);
    noTone(buzzer);

    hitungNote++;
    if (hitungNote % notePerGantiPesan == 0 && jumlahPesan > 1) {
      cetakBarisAnimasi(tengahkanTeks(pesanAtas[indexPesan]), 0, 1);
      cetakBarisAnimasi(tengahkanTeks(pesanBawah[indexPesan]), 1, 1);

      indexPesan++;
      if (indexPesan >= jumlahPesan) {
        indexPesan = 1;
      }
    }
  }
}

// ================== SETUP ==================
void setup() {
  pinMode(buzzer, OUTPUT);

  lcd.init();
  lcd.backlight();

  lcd.createChar(1, heartFull);
  lcd.createChar(2, heartEmpty);

  bootAnimation();
  heartSplash();

  tampilkanPesan(pesanAtas[0], pesanBawah[0], 1200);
  mainkanMusikDenganTeksBerjalan();
  tampilkanPenutupDenganHati();
}

void loop() {

}
