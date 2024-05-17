#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <SoftwareSerial.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);
SoftwareSerial mySerial(2, 3);
 
int gasValue = A0;
int data = 0;
int Red = 6;
int Green = 7;
void setup() {
  randomSeed(analogRead(0));
  mySerial.begin(9600);
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  pinMode(gasValue, INPUT);
  pinMode(Red, OUTPUT);
  pinMode(Green, OUTPUT);
  lcd.print("   WELCOME TO");
  lcd.setCursor(0, 1);
  lcd.print(" Limon Majumdar ");
  delay(3000);
  lcd.clear();
  lcd.print(" Gas Leakage ");
  lcd.setCursor(0, 1);
  lcd.print(" Detector Alarm ");
  delay(3000);
  lcd.clear();
}
 
void loop() {
 
  data = analogRead(gasValue);
 
  Serial.print("Gas Level: ");
  Serial.println(data);
  lcd.print("Gas Scan is ON");
  lcd.setCursor(0, 1);
  lcd.print("Gas Level: ");
  lcd.print(data);
  delay(1000);
 
  if (data > 80) {
    SendMessage();
    Serial.print("Gas detect alarm");
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(" Gas Leakage");
    lcd.setCursor(0, 1);
    lcd.print(" SMS Sent");
    delay(1000);
    digitalWrite(Red, HIGH);
    digitalWrite(Green, LOW);
 
  } else {
    Serial.print("Gas Level Low");
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Gas Level Normal");
    digitalWrite(Red, LOW);
    digitalWrite(Green, HIGH);
    delay(1000);
  }
  lcd.clear();
}
 
void SendMessage() {
  Serial.println("I am in send");
  mySerial.println("AT+CMGF=1");
  delay(1000);
  mySerial.println("AT+CMGS=\"+880187080310\"\r");
  mySerial.println("Hi Limon Gas Detected plz Open Windows And Check Your Gas Cylinder");
  delay(100);
  mySerial.println((char)26);
  delay(1000);
}
