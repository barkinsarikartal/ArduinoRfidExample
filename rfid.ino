#include <SPI.h>
#include <MFRC522.h>
const byte YESIL_LED = 4;
const byte KIRMIZI_LED = 2;
const byte BUZZER = 6;

#include <LiquidCrystal_I2C.h>
#include <Wire.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

MFRC522 rfid(10, 9);
byte Kart[4] = {202,38,92,131};
boolean Yetki;
void setup()
{ 
  Serial.begin(9600);
  pinMode(KIRMIZI_LED, OUTPUT);
  pinMode(YESIL_LED, OUTPUT);
  pinMode(BUZZER, OUTPUT);
  SPI.begin();
  rfid.PCD_Init(); 
  lcd.begin();
  lcd.clear();
}
void loop()
{
  Yetki = true;
  if ( rfid.PICC_IsNewCardPresent())
  {
    if ( rfid.PICC_ReadCardSerial())
    { Serial.print("Okunan Kart ID: ");
     Serial.print(rfid.uid.uidByte[0]);
     Serial.print(",");
     Serial.print(rfid.uid.uidByte[1]);
     Serial.print(",");
     Serial.print(rfid.uid.uidByte[2]);
     Serial.print(",");
     Serial.println(rfid.uid.uidByte[3]);
    }
    for (int i = 0; i < 4; i++)
    {
      if (rfid.uid.uidByte[i] != Kart[i])
      {
        Yetki = false;
      }
    }
    if (Yetki == true)
    {
      Serial.println("Yetki Onaylandi...");
      lcd.print("BarkinSarikartal");
      lcd.setCursor(0,1);
      lcd.print("Welcome");
      digitalWrite(YESIL_LED, HIGH);
      delay(1000);
      lcd.clear();
      digitalWrite(YESIL_LED, LOW);
      digitalWrite(BUZZER, HIGH);
      delay(50);
      digitalWrite(BUZZER, LOW);
      delay(50);
      digitalWrite(BUZZER, HIGH);
      delay(50);
      digitalWrite(BUZZER, LOW);
    }
    else
    {
      Serial.println("Yetki Onaylanmadi...");
      lcd.print("  INVALID CARD");
      digitalWrite(KIRMIZI_LED, HIGH);
      digitalWrite(BUZZER, HIGH);
      delay(500);
      lcd.clear();
      digitalWrite(KIRMIZI_LED, LOW);
      digitalWrite(BUZZER, LOW);
    }
    //rfid.PICC_HaltA();
  }
}
