#include <SPI.h>
#include "MFRC522.h"
#include <Wire.h>
#include "DS3231.h"

#define RST_PIN   9     
#define SS_PIN    10
#define NEW_UID {0xDE, 0xAD, 0xBE, 0xEF}    

MFRC522 mfrc522(SS_PIN, RST_PIN); // Create MFRC522 instance
MFRC522::MIFARE_Key key;

DS3231 clock;
RTCDateTime dt;


void setup() {
  // put your setup code here, to run once:

  //RFID Setup
  Serial.begin(9600);  // Initialize serial communications with the PC
  while (!Serial);     // Do nothing if no serial port is opened (added for Arduinos based on ATMEGA32U4)
  SPI.begin();         // Init SPI bus
  mfrc522.PCD_Init();  // Init MFRC522 card

  //RTC Setup
  clock.begin();
  clock.setDateTime(__DATE__, __TIME__); 

}

void loop() {
  // put your main code here, to run repeatedly:

  // Look for new cards, and select one if present
  if ( ! mfrc522.PICC_IsNewCardPresent() || ! mfrc522.PICC_ReadCardSerial() ) {
    delay(50);
    return;
  }

  dt = clock.getDateTime();

  // For leading zero look to DS3231_dateformat example
  
  Serial.print("Hello user! You've signed in at: ");
  Serial.print(dt.year);   Serial.print("-");
  Serial.print(dt.month);  Serial.print("-");
  Serial.print(dt.day);    Serial.print(" ");
  Serial.print(dt.hour);   Serial.print(":");
  Serial.print(dt.minute); Serial.print(":");
  Serial.print(dt.second); Serial.println("");
  delay(1000);

}
