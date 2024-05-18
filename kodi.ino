#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

const char* ssid = "SSID_NAME";       // WiFi SSID
const char* password = "PASSWORD";   // WiFi şifresi

const char* kodi_ip = "KODI_INTERNAL_IP";
const int kodi_port = 8080;
const char* kodi_username = "USERNAME_OF_KODI";
const char* kodi_password = "PASSWORD_OF_KODI";  // Kodi şifresi

WiFiClient wifiClient; // WiFiClient nesnesi oluşturuldu

void setup() {
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);  // LED'i başta kapalı yap

  WiFi.begin(ssid, password);
  
  Serial.print("WiFi'a bağlanıyor");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Bağlandı!");
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) { // WiFi'ye bağlıysa
    HTTPClient http;

    String url = String("http://") + kodi_ip + ":" + String(kodi_port) + "/jsonrpc";
    Serial.println("Connecting to Kodi: " + url);

    http.begin(wifiClient, url); // Yeni API kullanımı

    http.setAuthorization(kodi_username, kodi_password);

    int httpCode = http.GET();

    if (httpCode == HTTP_CODE_OK) { // HTTP isteği başarılıysa
      digitalWrite(LED_BUILTIN, LOW);  // LED'i yak
      Serial.println("Kodi'ye bağlı");
    } else {
      digitalWrite(LED_BUILTIN, HIGH); // LED'i kapat
      Serial.println("Kodi bağlı değil");
    }
    http.end();
  } else {
    digitalWrite(LED_BUILTIN, HIGH); // WiFi bağlantısı yoksa LED'i kapat
    Serial.println("WiFi bağlantısı yapılamadı");
  }
  
  delay(5000); // 5 saniye bekle
}
