// Definisi Pin LED Kiri
const int ledKiri[] = {2, 3, 4};
// Definisi Pin LED Kanan
const int ledKanan[] = {5, 6, 7};

// Definisi Pin Tombol
const int btnKiri = 8;
const int btnTengah = 9; // Hazard
const int btnKanan = 10;

// Definisi Buzzer
const int Buzzer = 11;

// Status Mode: 0 = OFF, 1 = SEIN KIRI, 2 = HAZARD, 3 = SEIN KANAN
int modeAktif = 0;

// Simpan status tombol sebelumnya (untuk memantau klik)
int lastKiri = HIGH;
int lastTengah = HIGH;
int lastKanan = HIGH;

void setup() {
  // Set Pin LED sebagai Output
  for (int i = 0; i < 3; i++) {
    pinMode(ledKiri[i], OUTPUT);
    pinMode(ledKanan[i], OUTPUT);
  }
  
  // Set Buzzer sebagai Output 
  pinMode(Buzzer, OUTPUT);

  // Set Pin Tombol sebagai Input Pull-up
  pinMode(btnKiri, INPUT_PULLUP);
  pinMode(btnTengah, INPUT_PULLUP);
  pinMode(btnKanan, INPUT_PULLUP);
}

void loop() {
  int statusKiri = digitalRead(btnKiri);
  int statusTengah = digitalRead(btnTengah);
  int statusKanan = digitalRead(btnKanan);

  // 1. KLIK TOMBOL KIRI -> Khusus Sein Kiri
  if (statusKiri == LOW && lastKiri == HIGH) {
    if (modeAktif == 1) modeAktif = 0; // Jika sudah aktif, matikan
    else modeAktif = 1;                // Aktifkan Sein Kiri
    delay(150); 
  }

  // 2. KLIK TOMBOL TENGAH -> Khusus Hazard (6 LED)
  if (statusTengah == LOW && lastTengah == HIGH) {
    if (modeAktif == 2) modeAktif = 0; // Jika sudah aktif, matikan
    else modeAktif = 2;                // Aktifkan Hazard
    delay(150);
  }

  // 3. KLIK TOMBOL KANAN -> Khusus Sein Kanan
  if (statusKanan == LOW && lastKanan == HIGH) {
    if (modeAktif == 3) modeAktif = 0; // Jika sudah aktif, matikan
    else modeAktif = 3;                // Aktifkan Sein Kanan
    delay(150);
  }

  lastKiri = statusKiri;
  lastTengah = statusTengah;
  lastKanan = statusKanan;

  // JALANKAN LAMPU SESUAI TOMBOL YANG AKTIF
  if (modeAktif == 1) {
    kedipLED(true, false); // Hanya LED Kiri
  } else if (modeAktif == 2) {
    kedipLED(true, true);  // Hazard (LED Kiri + Kanan / 6 LED)
  } else if (modeAktif == 3) {
    kedipLED(false, true); // Hanya LED Kanan
  } else {
    matiSemua();           // Semua Mati
  }
}

// Fungsi kedip lampu dan bunyi buzzer
void kedipLED(bool kiri, bool kanan) {
  // 1. NYALAKAN LED
  for (int i = 0; i < 3; i++) {
    if (kiri) digitalWrite(ledKiri[i], HIGH);
    if (kanan) digitalWrite(ledKanan[i], HIGH);
  }

  // 2. NYALAKAN BUZZER HANYA SAAT HAZARD (kiri & kanan bernilai true)
  if (kiri && kanan) {
    tone(Buzzer, 1000); // Frekuensi 1000 Hz
  }

  delayRespon(150); // Waktu nyala (0.15 detik)

  // 3. MATIKAN LED DAN BUZZER
  matiSemua();
  delayRespon(200); // Waktu mati (0.15 detik)
}

// Fungsi delay agar tetap bisa mendeteksi klik tombol saat lampu berkedip
void delayRespon(int durasi) {
  for (int i = 0; i < durasi / 10; i++) {
    if (digitalRead(btnKiri) == LOW || digitalRead(btnTengah) == LOW || digitalRead(btnKanan) == LOW) {
      break;
    }
    delay(10);
  }
}

// Fungsi mematikan seluruh LED dan Buzzer
void matiSemua() {
  for (int i = 0; i < 3; i++) {
    digitalWrite(ledKiri[i], LOW);
    digitalWrite(ledKanan[i], LOW);
  }
  noTone(Buzzer); // Matikan suara buzzer
}