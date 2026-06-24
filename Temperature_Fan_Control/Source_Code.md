#include <DHT.h>
#include <LiquidCrystal_I2C.h>

DHT dht(2 , DHT11);
LiquidCrystal_I2C lcd(0x27 , 16 , 2);

uint8_t INT3 = 8;
uint8_t INT4 = 9;
uint8_t ENB = 3;

float Temp;


void setup() {
  // put your setup code here, to run once:
  dht.begin();
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("Temperature:");
  pinMode(INT3 , OUTPUT);
  pinMode(INT4 , OUTPUT);
  pinMode(ENB , OUTPUT);
  
  digitalWrite(INT3 , HIGH);
  digitalWrite(INT4 , LOW);
  analogWrite(ENB , 255);
  delay(1000);

}

void loop() {
  // put your main code here, to run repeatedly:
  delay(2000);
  Temp = dht.readTemperature();
  lcd.setCursor(0,1);
  lcd.print(Temp);
  lcd.setCursor(6,1);
  lcd.print("*C");

  if(Temp > 30)
  {
    lcd.setCursor(13,0);
    lcd.print("H");
    analogWrite(ENB , 255);
  }

  else if(Temp > 28 && Temp <=30)
  {
    lcd.setCursor(13,0);
    lcd.print("M");
    analogWrite(ENB , 128);
  }

  else
  {
    lcd.setCursor(13,0);
    lcd.print("L");
    analogWrite(ENB , 70);
  }

}
