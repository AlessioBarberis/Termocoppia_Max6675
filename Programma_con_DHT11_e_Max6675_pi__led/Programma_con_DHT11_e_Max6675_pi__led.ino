// this example is public domain. enjoy!
// www.ladyada.net/learn/sensors/thermocouple
int ledPin = 12;

#include "max6675.h"
#include "DHT.h"
#define DHTPIN 9
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

int thermoDO = 6;
int thermoCS = 5;
int thermoCLK = 4;

MAX6675 thermocouple(thermoCLK, thermoCS, thermoDO);
int vccPin = 3;
int gndPin = 2;

unsigned long old_millis = 0;
unsigned long delta = 6000;       //oppure 60000 per ricevere un dato ogni minuto;
int minuti = 1;

void setup() {
  Serial.begin(9600);
  Serial.println(F("DHT11 e Max6675"));
  dht.begin();

  // use Arduino pins
  pinMode(vccPin, OUTPUT); digitalWrite(vccPin, HIGH);
  pinMode(gndPin, OUTPUT); digitalWrite(gndPin, LOW);

  pinMode(ledPin, OUTPUT);

  // wait for MAX chip to stabilize
  delay(500);
}

void loop() {
  // basic readout test, just print the current temp
  delay(2000);  //2 secondi prima che inizi il programma

  unsigned long now = millis();

  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  if (now >= old_millis + delta)
  {
    digitalWrite(ledPin, HIGH);
    Serial.print(minuti);
    Serial.print(", Temp Max6675: ");
    Serial.print(thermocouple.readCelsius());
    Serial.print(F(", Temperature DHT11: "));         //sensore umidità
    Serial.print(t);                                  //sensore umidità
    Serial.println(F("°C "));                         //sensore umidità
    old_millis = now;
    minuti = minuti + 1;

  }

  digitalWrite(ledPin, LOW);
  delay(1);

}
