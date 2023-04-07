#include <LiquidCrystal.h>
#include <DHT.h>

#define DHTPIN 2
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

const int buttonStartPin = 6;
const int buttonScrollPin = A3;
const int ledBlue = 7;
const int ledRed = 8;
const int ledGreen = 9;
const int ledYellow = 10;
const int buzzer = 13;
const int trigPin = A0;
const int echoPin = A1;
const int photoResistor = A2;

bool isRunning = false;
int buttonStateStart = 0;
int buttonStateScroll = 0;
int displayState = 0;

void setup() {
  pinMode(buttonStartPin, INPUT);
  pinMode(buttonScrollPin, INPUT);
  pinMode(ledBlue, OUTPUT);
  pinMode(ledRed, OUTPUT);
  pinMode(ledGreen, OUTPUT);
  pinMode(ledYellow, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(photoResistor, INPUT);

  dht.begin();
  lcd.begin(16, 2);
  lcd.print("Appuyez pr demarrer");
}

void loop() {
  buttonStateStart = digitalRead(buttonStartPin);

  if (buttonStateStart == HIGH) {
    isRunning = !isRunning;
    delay(500);
  }

  if (isRunning) {
    int temperature = dht.readTemperature();
    int humidity = dht.readHumidity();
    int lightLevel = analogRead(photoResistor);
    long distance = measureDistance();

    manageTemperature(temperature);
    manageHumidity(humidity);
    manageDistance(distance);

    buttonStateScroll = digitalRead(buttonScrollPin);

    if (buttonStateScroll == HIGH) {
      displayState++;
      if (displayState > 2) {
        displayState = 0;
      }
      delay(500);
    }

    switch (displayState) {
      case 0:
        lcd.setCursor(0, 0);
        lcd.print("Temp: ");
        lcd.print(temperature);
        lcd.print("C");

        lcd.setCursor(0, 1);
        lcd.print("Humid: ");
        lcd.print(humidity);
        lcd.print("%");
        break;

      case 1:
        lcd.setCursor(0, 0);
        lcd.print("Lum: ");
        lcd.print(lightLevel);
        lcd.setCursor(0, 1);
        lcd.print("                  ");
        break;

      case 2:
        lcd.setCursor(0, 0);
        lcd.print("Distance: ");
        lcd.print(distance);
        lcd.print("cm");
        lcd.setCursor(0, 1);
        lcd.print("                  ");
        break;
    }
    delay(200);
  }
}

// Les fonctions manageTemperature, manageHumidity, measureDistance et manageDistance restent inchangées.
