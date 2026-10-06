[dokumentasi_proyek.md](https://github.com/user-attachments/files/33081889/dokumentasi_proyek.md)
# Sistem Lampu Sein & Hazard Otomatis dengan Arduino

Proyek ini adalah sistem kontrol **Lampu Sein (Sign) dan Hazard** berbasis Arduino. Sistem ini dilengkapi dengan 6 buah LED (3 kiri, 3 kanan), 3 tombol navigasi, serta sebuah Buzzer sebagai indikator suara yang khusus aktif pada mode Hazard.

---

## 📌 Fitur Utama

- **Mode Sein Kiri**: Mengedipkan 3 LED sebelah kiri.
- **Mode Sein Kanan**: Mengedipkan 3 LED sebelah kanan.
- **Mode Hazard**: Mengedipkan seluruh LED (6 LED) secara bersamaan disertai bunyi **Buzzer** sebagai peringatan.
- **Tombol Push Toggle**: Tekan sekali untuk mengaktifkan, dan tekan kembali untuk mematikan mode yang berjalan.
- **Respon Cepat (Non-Blocking Delay)**: Menggunakan pembagian fungsi delay khusus agar tombol tetap responsif saat lampu sedang berkedip.

---

## 🛠️ Skema Pin & Komponen

| Komponen | Pin Arduino | Keterangan |
| :--- | :--- | :--- |
| **LED Kiri** | `Pin 2, 3, 4` | Array LED Sisi Kiri |
| **LED Kanan** | `Pin 5, 6, 7` | Array LED Sisi Kanan |
| **Tombol Kiri** | `Pin 8` | Dipasang dengan `INPUT_PULLUP` |
| **Tombol Hazard (Tengah)** | `Pin 9` | Dipasang dengan `INPUT_PULLUP` |
| **Tombol Kanan** | `Pin 10` | Dipasang dengan `INPUT_PULLUP` |
| **Buzzer** | `Pin 11` | Indikator Suara Hazard |

> **Catatan Hardware:** 
> - Karena menggunakan `INPUT_PULLUP`, sambungkan salah satu kaki tombol ke **Pin Arduino** dan kaki lainnya ke **GND**.
> - Jangan lupa menambahkan resistor pembatas arus (misal: 220Ω) pada tiap LED.

---

## 🕹️ Cara Kerja & Mode Sistem

Sistem memiliki 4 status (`modeAktif`):

1. **`modeAktif = 0` (OFF)**  
   Seluruh LED dan Buzzer dalam kondisi mati.
2. **`modeAktif = 1` (Sein Kiri)**  
   Hanya LED Kiri (Pin 2, 3, 4) yang berkedip.
3. **`modeAktif = 2` (Hazard)**  
   Semua LED (Kiri & Kanan) berkedip dan Buzzer berbunyi pada frekuensi 1000 Hz secara bersamaan.
4. **`modeAktif = 3` (Sein Kanan)**  
   Hanya LED Kanan (Pin 5, 6, 7) yang berkedip.

---

## 📋 Struktur Fungsi Kode

- `setup()` — Menginisialisasi pin LED dan Buzzer sebagai `OUTPUT`, serta tombol sebagai `INPUT_PULLUP`.
- `loop()` — Membaca input tombol dan memproses perpindahan mode.
- `kedipLED(bool kiri, bool kanan)` — Mengontrol penyalaan LED serta Buzzer berdasarkan mode yang aktif.
- `delayRespon(int durasi)` — Mengatur jeda kedipan lampu tanpa mengunci pembacaan tombol.
- `matiSemua()` — Mematikan seluruh LED dan perintah `noTone()` untuk Buzzer.

---

## 🚀 Cara Penggunaan

1. Buka file `.ino` menggunakan **Arduino IDE**.
2. Sambungkan board Arduino (Uno/Nano/Mega) ke komputer.
3. Pilih **Board** dan **Port** yang sesuai di Arduino IDE.
4. Upload kode ke board.
5. Tekan tombol navigasi untuk menguji fungsi lampu sein dan hazard.
