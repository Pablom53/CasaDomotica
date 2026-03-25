#include <ESP32Servo.h>
#include <DHdddddddT.h>// libreria Adafruit
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// ---------- OLED ----------
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// ---------- DHT11 ----------
#define DHTPIN 26
#define DHTTYPE DHT11
#define TEMP_UMBRAL 22
DHT dht(DHTPIN, DHTTYPE);

// ---------- MOTOR (VENTILADOR) ----------
#define INA 14
#define INB 16

// ---------- LDR + SERVO ----------
const int pinLDR = 35;
const int pinServo = 13;
const int umbralLuz = 2000;

Servo miServo;
int posicionArriba = 90;
int posicionRecto = 0;

void setup() {
  Serial.begin(115200);

  pinMode(INA, OUTPUT);
  pinMode(INB, OUTPUT);

  dht.begin();

  miServo.attach(pinServo);
  miServo.write(posicionRecto);

  // OLED
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("No se encontró la pantalla OLED");
    while (true);
  }

  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
}

void loop() {
  // ---------- DHT ----------
  float temperatura = dht.readTemperature();
  float humedad = dht.readHumidity();

  if (!isnan(temperatura) && !isnan(humedad)) {

    // Ventilador
    if (temperatura > TEMP_UMBRAL) {
      digitalWrite(INA, Higth);
      digitalWrite(INB, LOW);
    } else {
      digitalWrite(INA, Low);
      digitalWrite(INB, LOW);
    }

    // ---------- OLED ----------
    display.clearDisplay();
    display.setTextSize(1);
    display.setCursor(0, 0);
    display.println("CASA DOMOTICA");

    display.setCursor(0, 20);
    display.print("Temp: ");
    display.print(temperatura);
    display.println(" C");

    display.setCursor(0, 35);
    display.print("Humedad: ");
    display.print(humedad);
    display.println(" %");

    
  }else{
    digitalWrite(INA, HIGH);
      digitalWrite(INB, LOW);
    }

  // ---------- LDR + SERVO ----------
  int valorLDR = analogRead(pinLDR);
  display.setCursor(0, 50);
    display.print("Luz: ");
    display.println(valorLDR);
    display.display();

  if (valorLDR > umbralLuz) {
    miServo.write(posicionArriba);
    delay(1000);
  } else {
    miServo.write(posicionRecto);
    delay(1000);
  }
Serial.println(humedad);
Serial.println(temperatura);
Serial.println("CASA DOMOTICA");
  delay(2000);
}
