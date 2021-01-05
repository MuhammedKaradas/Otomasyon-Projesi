#include <LiquidCrystal.h>
#include <Seeed_BME280.h>
#include <Wire.h>

LiquidCrystal lcd(12,11,5,4,3,2);

BME280 bme280;
int delaySure = 3000;
int sicaklikPwmPin = 9;
int nemPwmPin = 10;
int sicaklikFanHiz = 0;
int nemFanHiz = 0;
float sicaklikDeger;
float nemDeger;

void setup() {
  pinMode(sicaklikPwmPin,OUTPUT);
  pinMode(nemPwmPin,OUTPUT);
  analogWrite(6,100);
  /*
   * burada lcd ekranın contrast değerini ayarlamış olduk.
  */
  lcd.begin(16,2);
  
  if(!bme280.init()){
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Sensor Hata!");
  }
  
}

void loop() {
  lcd.setCursor(0, 0);
  lcd.print("Sicaklik:");
  
  sicaklikDeger = bme280.getTemperature();
  lcd.print(sicaklikDeger,1);
  lcd.print(" C");
  lcd.setCursor(0, 1);
  lcd.print("Hiz:");
  
  if (sicaklikDeger > 30) {
    analogWrite(sicaklikPwmPin, 255);
    sicaklikFanHiz = 255;
  }
  else if (sicaklikDeger > 20 && sicaklikDeger < 30) {
    analogWrite(sicaklikPwmPin, 225);
    sicaklikFanHiz = 225;
  }
  else if (sicaklikDeger > 15 && sicaklikDeger < 20) {
    analogWrite(sicaklikPwmPin, 175);
    sicaklikFanHiz = 175;
  }
  else {
    analogWrite(sicaklikPwmPin, 150);
    sicaklikFanHiz = 150;
  }
  
  lcd.print(sicaklikFanHiz);
  delay(delaySure);
  lcd.clear();
  delay(500);

  /*Nem Değeri*/
  nemDeger = bme280.getHumidity();
  lcd.setCursor(0, 0);
  lcd.print("Nem:");
  //lcd.setCursor(6, 1);
  lcd.print(" % ");
  lcd.print(nemDeger);
  lcd.setCursor(0, 1);
  lcd.print("Hiz:");
  
  if (nemDeger > 60) {
    analogWrite(nemPwmPin, 255);
    nemFanHiz = 255;
  }
  else if (nemDeger>45 && nemDeger<55) {
    analogWrite(nemPwmPin, 225);
    nemFanHiz = 225;
  }
  else if (nemDeger<45) {
    analogWrite(nemPwmPin, 175);
    nemFanHiz = 175;
  }
  
  lcd.print(nemFanHiz);
  delay(delaySure);
  lcd.clear();
}
