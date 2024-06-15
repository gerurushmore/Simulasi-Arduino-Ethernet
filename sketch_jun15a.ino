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