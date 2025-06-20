#define DHTPIN 13       // D5
#define DHTTYPE DHT11

#define buzzer 2        // D4
#define gas_sensor 12   // D6
#define sound_sensor 14 // D5

#define red_light 16    // D0
#define yellow_light 5  // D1
#define green_light 4   // D2

// WiFi Credentials
const char* ssid = "yourWifiName";        // Enter SSID
const char* password = "yourPassword";   // Enter Password

// Blynk Credentials
#define BLYNK_TEMPLATE_ID "TMPL3jtxHKL"
#define BLYNK_TEMPLATE_NAME "traffic monitoring"
#define BLYNK_AUTH_TOKEN "t4GEo578KJq-ICcV6NF1W4Sc_yCdI_A3"

#include <DHT.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

DHT dht(DHTPIN, DHTTYPE);

float temperature, humidity;
int sound, harmfulgas;
BlynkTimer timer;

void setup() {
  Serial.begin(115200);         // Start serial communication
  dht.begin();

  pinMode(buzzer, OUTPUT);
  pinMode(gas_sensor, INPUT);
  pinMode(sound_sensor, INPUT);

  pinMode(red_light, OUTPUT);
  pinMode(yellow_light, OUTPUT);
  pinMode(green_light, OUTPUT);

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, password);

  // Run myTimer every 1 second
  timer.setInterval(1000L, myTimer);

  // Wait for WiFi connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print("*");
  }

  Serial.println("\nWiFi connection Successful");
  Serial.print("ESP8266 IP Address: ");
  Serial.println(WiFi.localIP());
}

void myTimer() {
  Blynk.virtualWrite(V0, temperature);
  Blynk.virtualWrite(V1, humidity);
  Blynk.virtualWrite(V2, !sound);
  Blynk.virtualWrite(V3, !harmfulgas);
}

void loop() {
  sound = digitalRead(sound_sensor);
  harmfulgas = digitalRead(gas_sensor);
  humidity = dht.readHumidity();
  temperature = dht.readTemperature();

  if (isnan(humidity) || isnan(temperature)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.print(" °C | Humidity: ");
  Serial.print(humidity);
  Serial.print(" % | Harmful Gas: ");
  Serial.print(harmfulgas);
  Serial.print(" | Sound: ");
  Serial.println(sound);

  // If ambulance or gas detected → GREEN light
  if (harmfulgas == 0 || sound == 0) {
    traffic_light(0, 0, 1); // GREEN
    delay(3000);
  } else {
    traffic_light(1, 0, 0); // RED
    delay(3000);
    traffic_light(0, 1, 0); // YELLOW
    delay(1000);
    traffic_light(0, 0, 1); // GREEN
    delay(3000);
  }

  Blynk.run();   // Blynk connection handler
  timer.run();   // BlynkTimer handler
}

void traffic_light(int r, int y, int g) {
  digitalWrite(red_light, r);
  digitalWrite(yellow_light, y);
  digitalWrite(green_light, g);
}
