   
   PROJECT: UCAPAN ULANG TAHUN ROMANTIS - ESP32 + LCD I2C + BUZZER
   FOR SOMEONE SPECIAL
   =
  HARDWARE:
   - ESP32   : board
   - LCD I2C : menampilkan teks ucapan (2 baris, huruf kapital)
   - Buzzer  : efek boot + lagu 

   WIRING:
   - LCD I2C  -> SDA = GPIO21, SCL = GPIO22, VCC = 5V/3V3, GND = GND
   - Buzzer   -> (+) = GPIO14, (-) = GND
   (Sesuaikan alamat I2C LCD, default 0x27. Jika layar tidak
    menyala coba 0x3F menggunakan I2C scanner)
  ===========================================================


