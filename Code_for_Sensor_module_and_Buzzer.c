#define BLYNK_PRINT Serial
#define BLYNK_TEMPLATE_ID "TMPL3-BrdSFf4"
#define BLYNK_TEMPLATE_NAME "Gas Monitor"
#define BLYNK_AUTH_TOKEN "xZvQKS2yfFqdfkFP4G_qeWl8PrFfpf9B"
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
char ssid[] = "Wifi-names";
char pass[] = "password for wifi";

float co_value, h2s_value, ch4_value;
#define co_pin 34
#define h2s_pin 32
#define ch4_pin 35
#define buzzer 15
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);
BLYNK_WRITE(V3)
{
  int a = param[0].asInt();
  if (a == 1)
  {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Buzzer Activated");
    digitalWrite(buzzer, HIGH);
    delay(500);
  }
  else
  {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Buzzer DeActivated");
    digitalWrite(buzzer, LOW);
    delay(500);
  }
}

void setup()
{
  lcd.begin();
  lcd.setCursor(0, 0);
  lcd.print(" Ore Hazard ");
  lcd.setCursor(0, 1);
  lcd.print("  Explorer  ");
  Serial.begin(9600);
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  pinMode(co_pin, INPUT);
  pinMode(h2s_pin, INPUT);
  pinMode(ch4_pin, INPUT);
  pinMode(buzzer, OUTPUT);
  digitalWrite(buzzer, HIGH);
  delay(250);
  digitalWrite(buzzer, LOW);
  delay(750);
}

void loop()
{
  Blynk.run();
  co_value = analogRead(co_pin);
  Serial.print("co_value: ");
  Serial.println(co_value);
  co_value = map(co_value, 0, 1023, 0, 100);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Carbon Monoxide: ");
  lcd.setCursor(0, 1);
  lcd.print(co_value);
  delay(1000);
  h2s_value = analogRead(h2s_pin);
  Serial.print("h2s_value: ");
  Serial.println(h2s_value);
  h2s_value = map(h2s_value, 0, 1023, 0, 100);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Hydrogen Sulphide: ");
  lcd.setCursor(0, 1);
  lcd.print(h2s_value);
  delay(1000);
  ch4_value = analogRead(ch4_pin);
  Serial.print("ch4_value: ");
  Serial.println(ch4_value);
  ch4_value = map(ch4_value, 0, 1023, 0, 100);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Methane: ");
  lcd.setCursor(0, 1);
  lcd.print(ch4_value);
  delay(1000);
  Blynk.virtualWrite(V0, co_value);
  Blynk.virtualWrite(V1, h2s_value);
  Blynk.virtualWrite(V2, ch4_value);
}
