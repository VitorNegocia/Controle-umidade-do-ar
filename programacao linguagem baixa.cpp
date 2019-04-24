#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include "minhaCom.h"
#include "minhasMacros.h"
#include <LiquidCrystal.h>
#include <String.h>
#include "DHT.h"
#define DHTPIN DDC1 
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
const int rs = DDB4, en = DDB3, d4 = DDD4, d5 = DDD5, d6 = DDB1, d7 = DDB0;
LiquidCrystal  lcd(rs, en, d4, d5, d6, d7);
int BOT1 = DDD2;
int BOT2 = DDD3;
volatile float UMID_DES = 0;
int CLIMA = DDB5;

ISR(INT0_vect)
{
UMID_DES = UMID_DES + 1;
}
ISR(INT1_vect)
{
UMID_DES = UMID_DES - 1;
}
void initInterrupt1(void){
  EIMSK |=(1 << INT0);
  EICRA |=(1 << ISC00);
  sei();}
void initInterrupt2(void){
  EIMSK |=(1 << INT1);
  EICRA |=(1 << ISC00);
  sei();
}
void setup()
{
  initUSART();
  //configura pb2 como entrada e liga seu pullup
  clearBit(DDRD, DDD2);
  setBit(DDRD, DDD2);
  clearBit(DDRD, DDD3);
  setBit(DDRD, DDD3);
  setBit(DDRB, DDB5); 
    dht.begin();
      initInterrupt1();  
     initInterrupt2();  
}
void loop()
{
  char x[10];
  char y[10];
    float UMID = dht.readHumidity(); 
    printString("Umidade: \n");
    sprintf(x, "%f", UMID);
    printString(x);
    printString("Desejada ");
    sprintf(y,"%f",UMID_DES);
    printString(y);
    printString("%\n");
    delay(1000);
    if (UMID < UMID_DES) 
    {
      clearBit(PORTB, PB5);
    }
    else
    {
      setBit(PORTB, PB5);
    }
  }