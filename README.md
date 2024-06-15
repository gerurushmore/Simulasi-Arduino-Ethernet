# Simulasi-Arduino-Ethernet
Proyek ini adalah aplikasi sederhana yang menggunakan Arduino dan sensor suhu LM35 untuk memonitor suhu dan mengirim data melalui server Ethernet. Data suhu, bersama dengan beberapa informasi pribadi, ditampilkan di Serial Monitor dan dapat diakses melalui server web yang berjalan di Arduino.
# Perangkat yang dibutuhkan
1. Perangkat Keras yang Dibutuhkan
2. Arduino UNO (atau model lain yang kompatibel)
3. Ethernet Shield (seperti W5100)
4. Sensor Suhu LM35
5. Kabel Jumper
7. Komputer dengan Arduino IDE
8. Proteus (untuk simulasi, jika diperlukan)
   ![image](https://github.com/gerurushmore/Simulasi-Arduino-Ethernet/assets/129182758/96eefd30-95cd-4da2-b46c-101d8d6501fe)

# Perangkat yang diinstal
1. Arduino IDE
2. UIPEthernet libraly

#Cara Kerja
1. Install Arduino
2. Unduh dan extract Libraly di Arduino IDE
3. Setelah install dan menambahkan libraly di Arduino, lalu inputkan source code
   ![image](https://github.com/gerurushmore/Simulasi-Arduino-Ethernet/assets/129182758/4aada53c-a0b1-47e3-a942-36e34f447a20)
4. lalu pilih board Arduino Uno
![image](https://github.com/gerurushmore/Simulasi-Arduino-Ethernet/assets/129182758/09e2334c-9fbe-4d0e-8211-b95bd05bd2e8)
5. klik untuk verify
![image](https://github.com/gerurushmore/Simulasi-Arduino-Ethernet/assets/129182758/10225ff8-90c0-4723-9d71-6dcb26010b2d)
6. copy hasil yang sudah dicompile untuk dirun di Arduino
![image](https://github.com/gerurushmore/Simulasi-Arduino-Ethernet/assets/129182758/85dc51bf-4f3e-4f8e-a398-cf0ceba156c0)
7. jika sudah masuk Proteus
![image](https://github.com/gerurushmore/Simulasi-Arduino-Ethernet/assets/129182758/641b06b9-0ffa-4929-9831-b240b980f0e5)
8. klik 2x diboard Arduino UNO, lalu copykan di Program File
![image](https://github.com/gerurushmore/Simulasi-Arduino-Ethernet/assets/129182758/bcac687b-9ee2-4747-9651-442a1f3e662d)
9. jika sudah maka ke run, buka terminal
![image](https://github.com/gerurushmore/Simulasi-Arduino-Ethernet/assets/129182758/087e967d-85bc-4394-a5b3-d24d69bfab01)
10. tampilan Virtual Terminal
![image](https://github.com/gerurushmore/Simulasi-Arduino-Ethernet/assets/129182758/1f20555d-2236-4793-a4b6-a0179dbba424)

#Kontribusi untuk pembelajaran yang lebih mendalam

  #include <UIPEthernet.h>

// Pengaturan IP Address
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
IPAddress ip(192, 168, 67, 164);

EthernetServer server(80);

// Pin untuk sensor suhu LM35
const int sensorPin = A0;

// Data diri
String nama = "Istana Islam";
String nim = "1462100051";
String tanggalLahir = "8 September 2001";
String email = "gerurushmore@gmail.com";

void setup() {
  // Memulai komunikasi serial
  Serial.begin(9600);

  // Memulai UIPEthernet
  Ethernet.begin(mac, ip);
  server.begin();
  Serial.print("Server IP: ");
  Serial.println(Ethernet.localIP());
}

void loop() {
  // Membaca nilai dari sensor suhu
  int sensorValue = analogRead(sensorPin);
  float temperature = (sensorValue / 1024.0) * 5.0 * 100;

  // Menampilkan data suhu dan data diri pada terminal serial
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" C");
  Serial.print("Nama: ");
  Serial.println(nama);
  Serial.print("NIM: ");
  Serial.println(nim);
  Serial.print("Tanggal Lahir: ");
  Serial.println(tanggalLahir);
  Serial.print("Email: ");
  Serial.println(email);

  // Menunggu beberapa detik sebelum membaca kembali
  delay(5000);

  // Mendengarkan klien
  EthernetClient client = server.available();
  if (client) {
    Serial.println("New client");
    boolean currentLineIsBlank = true;
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        Serial.write(c);

        // Jika kita sampai pada akhir baris HTTP request
        if (c == '\n' && currentLineIsBlank) {
          // Mengirim respon standar HTTP
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println("Connection: close");
          client.println();

          // Mengirim data suhu
          client.print("Temperature: ");
          client.print(temperature);
          client.println(" C");
          client.println("<br>");
          client.print("Nama: ");
          client.println(nama);
          client.print("NIM: ");
          client.println(nim);
          client.print("Tanggal Lahir: ");
          client.println(tanggalLahir);
          client.print("Email: ");
          client.println(email);
          break;
        }
        if (c == '\n') {
          currentLineIsBlank = true;
        } else if (c != '\r') {
          currentLineIsBlank = false;
        }
      }
    }
    delay(1);
    client.stop();
    Serial.println("Client disconnected");
  }
}









