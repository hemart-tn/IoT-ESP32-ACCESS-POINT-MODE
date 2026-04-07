# 🚀 ESP32 IoT Dashboard (Access Point Mode)

## 📌 Deskripsi

Project ini merupakan implementasi sistem IoT menggunakan ESP32 dalam mode **Access Point (AP)**.
ESP32 bertindak sebagai server lokal yang dapat diakses langsung melalui smartphone tanpa koneksi internet.

---

## 📱 Fitur Utama

* 📏 Monitoring jarak (Ultrasonic Sensor)
* 📊 Grafik realtime
* 🎨 Kontrol LED RGB (slider)
* 📡 Mode Access Point (tanpa WiFi rumah)

---

## 🌐 Cara Akses

1. Nyalakan ESP32
2. Hubungkan HP ke WiFi:

   ```
   ESP32_AP
   ```
3. Buka browser:

   ```
   http://192.168.4.1
   ```

---

## 🧰 Hardware

* ESP32
* Sensor Ultrasonik (HC-SR04)
* LED RGB
* Breadboard
* Kabel jumper

---

## ⚙️ Cara Kerja

1. ESP32 membuat jaringan WiFi sendiri (AP Mode)
2. Smartphone terhubung ke ESP32
3. ESP32 menjalankan web server
4. Data sensor dikirim ke web secara realtime
5. User bisa kontrol LED dari web

---

## 📸 Hasil Project

1. Koneksi WiFi ESP32 (Access Point)
<p align="center"> <img src="https://github.com/user-attachments/assets/347e2330-a174-46d8-8b07-35d1d33e5657" width="300"> </p>

Keterangan:
Gambar di atas menunjukkan perangkat smartphone yang terhubung langsung ke jaringan WiFi yang dibuat oleh ESP32 (mode Access Point). Pengguna dapat mengakses web dashboard melalui alamat IP 192.168.4.1 tanpa menggunakan koneksi internet.

2. Hasil Pembacaan Sensor Jarak (HC-SR04)
<p align="center"> <img src="https://github.com/user-attachments/assets/9fbf9cef-488c-4c43-ad5e-a23be9a38f71" width="300"> </p>

Keterangan:
Gambar menunjukkan tampilan web dashboard yang menampilkan hasil pembacaan sensor ultrasonik HC-SR04 secara realtime. Nilai jarak yang terbaca akan berubah sesuai dengan objek yang berada di depan sensor.

3. Hasil Kontrol LED RGB
<p align="center"> <img src="https://github.com/user-attachments/assets/0c14e30e-2bce-4e50-83cf-79dd45e34336" width="300"> </p>

Keterangan:
Gambar menunjukkan LED RGB yang dapat dikontrol melalui web dashboard menggunakan slider. Perubahan nilai warna (Red, Green, Blue) akan langsung mempengaruhi warna LED secara realtime.

---

## 🧠 Konsep yang Digunakan

* Access Point Mode (WiFi AP)
* Web Server ESP32
* Realtime Data (AJAX/WebSocket)
* IoT Local Network

---

## 🏁 Kesimpulan

ESP32 dapat digunakan sebagai server lokal tanpa internet dan mampu melakukan monitoring serta kontrol perangkat secara realtime melalui web browser.

---

## 👨‍💻 Author

Hema
