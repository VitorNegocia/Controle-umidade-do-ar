#include <LiquidCrystal.h>
#include "DHT.h"
#define DHTPIN A1 
#define DHTTYPE DHT11 
DHT dht(DHTPIN, DHTTYPE);
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 9, d7 = 8;
LiquidCrystal  lcd(rs, en, d4, d5, d6, d7);
int BOT1 = 2;
int BOT2 = 3;
volatile float UMID_DES = 0;
int CLIMA = 13;
void setup()
{
  pinMode(BOT1, INPUT);
  pinMode(BOT2, INPUT);
  pinMode(CLIMA, OUTPUT);
  lcd.begin(16, 2);
  dht.begin();
  attachInterrupt(digitalPinToInterrupt(BOT1),aumenta_umidade, FALLING);
  attachInterrupt(digitalPinToInterrupt(BOT2),diminui_umidade, FALLING);
}

void loop()
{
  float h = dht.readHumidity();

    lcd.setCursor(0, 0);
    lcd.print("Umidade: ");
    lcd.print(h);
    lcd.setCursor(0, 1);
    lcd.print("Desejada ");
    lcd.print(UMID_DES);
    lcd.print("%");
  
  float UMID = dht.readHumidity(); {
    if (h < UMID_DES)
    {
      digitalWrite(CLIMA, HIGH);
    }
    else
    {
      digitalWrite(CLIMA, LOW);
    }
  }
}
void aumenta_umidade()
{
  UMID_DES = UMID_DES + 1;
}

void diminui_umidade()
{
  UMID_DES = UMID_DES - 1;
}