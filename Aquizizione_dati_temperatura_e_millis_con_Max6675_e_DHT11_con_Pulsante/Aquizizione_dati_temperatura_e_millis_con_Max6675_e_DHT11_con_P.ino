/*Obbiettivo progetto: acquisire Temp da DHT11 e Temp termocoppia una volta ogni volta che il pulsante è premuto.
scrivere su seriale i valori di tempo trascorso, Temp termocoopia, Temp DHT11 in formato csv.*/
#include "max6675.h"                                    
#include "DHT.h"                                       
#define DHTPIN 9
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

int counter=0;
int last_state=0;

int buttonPin= 3;
int ledPin = 12;
int thermoDO = 6;
int thermoCS = 5;
int thermoCLK = 4;

MAX6675 thermocouple(thermoCLK, thermoCS, thermoDO);

void setup() {
  Serial.begin(9600);
  Serial.println(" millis, Max6675 e DHT11 ");
  dht.begin();

  // use Arduino pins
  pinMode(buttonPin, INPUT);
  pinMode(ledPin, OUTPUT);

  // wait for MAX chip to stabilize
  delay(1000);
}

void loop() {
  
  // Read temperature as Celsius (the default)
  float temp_DHT11 = 0;
  float temp_Termocoppia = 0;
  unsigned long now = millis();
  int button_state = digitalRead(buttonPin);
  
  if(button_state == HIGH && button_state != last_state)
  {
    digitalWrite(ledPin, HIGH);
    temp_DHT11 = dht.readTemperature();
    temp_Termocoppia = thermocouple.readCelsius();
    Serial.print(now/1000);
    Serial.print(" , ");
    Serial.print(temp_Termocoppia);
    Serial.print(" , ");
    Serial.println(temp_DHT11);
    digitalWrite(ledPin, LOW);
  }
  
  last_state = button_state;
  delay(1);
}
