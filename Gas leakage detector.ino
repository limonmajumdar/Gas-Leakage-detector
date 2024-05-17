#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <SoftwareSerial.h>

LiquidCrystal_I2C lcd(0x27, 20, 4); 
SoftwareSerial mySerial(3, 2); 

int gasValue = A0;
int data = 0;
int redPin = 4;
int greenPin = 5;

void setup() {
  randomSeed(analogRead(0));
  mySerial.begin(9600);
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  pinMode(gasValue, INPUT);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);

  
  lcd.print("     WELCOME TO ");
  lcd.setCursor(0, 1);
  lcd.print("   LIMON MAJUMDAR");
  lcd.setCursor(0, 2);
  lcd.print("    NAYAN PANDAY");
  lcd.setCursor(0, 3);
  lcd.print("      PROJECT");
  delay(4000);
  lcd.clear();
  lcd.print("Gas Leakage Detector");
  lcd.setCursor(0, 1);
  lcd.print("     Supervisor");
  lcd.setCursor(0, 2);
  lcd.print("     M. RAIHAN");
  lcd.setCursor(0, 3);
  lcd.print("NORTH WESTERN KHULNA");
  delay(6000);
  lcd.clear();
}

void loop() {
  data = analogRead(gasValue);
  Serial.print("  Gas Level: ");
  Serial.println(data);

  lcd.clear();

  if (data > 400) {
    lcd.print("GAS LEAK DETECTED!"); 
  } else {
    lcd.print("  Gas Scan: Active   "); 
  }
  delay(500); 

  lcd.setCursor(0, 1);
  lcd.print("   Gas Level: ");
  lcd.print(data); 
  delay(500);

  if (data > 400) { 
    lcd.setCursor(0, 2);
    lcd.print("SMS Alert Sent      "); 
  } else {
    lcd.setCursor(0, 2); 
    lcd.print("                    "); 
  }
  delay(500);

  lcd.setCursor(0, 3);
  if (data > 400) {
    lcd.print("LED: RED            ");  
  } else {
    lcd.print("     LED: GREEN     "); 
  }
  delay(500);

 
  if (data > 400) {
    SendMessage();
    analogWrite(redPin, 255); 
    digitalWrite(greenPin, LOW); 
  } else {
    analogWrite(greenPin, 255); 
    digitalWrite(redPin, LOW); 
  }

  delay(2000);
}

void SendMessage() {
  Serial.println("I am in send");
  mySerial.println("AT+CMGF=1"); 
  delay(1000);
  mySerial.println("AT+CMGS=\"+8801987080310\"\r"); 
  mySerial.println("Gas Leakage Detected !!Open Windows And Check Your Gas Cylinder!!"); 
  delay(100);
  mySerial.println((char)26); 
  delay(1000);
}
