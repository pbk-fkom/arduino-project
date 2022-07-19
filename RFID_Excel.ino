//Belajar Robotik
#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 10 
#define RST_PIN 9

MFRC522 mfrc522(SS_PIN, RST_PIN);

byte card_ID[7]; 
byte Name1[7] = {0x04, 0x16, 0x62, 0x9A, 0xEF, 0x2C, 0x80};
byte Name2[7] = {0x04, 0x16, 0x62, 0x9A, 0xEF, 0x2C, 0x80};

int NumbCard[2];
int j = 0;
int statu[2];
int s = 0;

int const RedLed = 6;
int const GreenLed = 5;
int const Buzzer = 8;

String Log;
String Nama;
long Identitas;
int n ;

void setup() {

  Serial.begin(9600);
  SPI.begin();  
  mfrc522.PCD_Init(); 

  Serial.println("CLEARSHEET");               
  Serial.println("LABEL,Date,Nama,Identitas,Waktu Masuk,Waktu Keluar");

  pinMode(RedLed, OUTPUT);
  pinMode(GreenLed, OUTPUT);
  pinMode(Buzzer, OUTPUT);

  delay(200);
}

void loop() {
  //look for new card
  if ( ! mfrc522.PICC_IsNewCardPresent()) {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) {
    return;
  }

  for (byte i = 0; i < mfrc522.uid.size; i++) {
    card_ID[i] = mfrc522.uid.uidByte[i];

    if (card_ID[i] == Name1[i]) {
      Nama = "ADE BUDIONO"; 
      Identitas = 123456;
      j = 0;
      s = 0;
    }
    else if (card_ID[i] == Name2[i]) {
      Nama = "ADE BUDIONO"; 
      Identitas = 789101; 
      j = 1;
      s = 1;
    }
    else {
      digitalWrite(GreenLed, LOW);
      digitalWrite(RedLed, HIGH);
      goto cont;
    }
  }
  if (NumbCard[j] == 1 && statu[s] == 0) {
    statu[s] = 1;
    Serial.print("DATA,DATE," + Nama);
    Serial.print(",");
    Serial.print(Identitas); 
    Serial.print(",");
    Serial.print("");
    Serial.print(",");
    Serial.println("TIME");

  }
  else if (NumbCard[j] == 0) {
    NumbCard[j] = 1;
    n++;
    Serial.print("DATA,DATE," + Nama);
    Serial.print(",");
    Serial.print(Identitas);
    Serial.print(",");
    Serial.print("TIME");
    Serial.print(",");
    Serial.println("");
    digitalWrite(GreenLed, HIGH);
    digitalWrite(RedLed, LOW);
    digitalWrite(Buzzer, HIGH);
    delay(30);
    digitalWrite(Buzzer, LOW);
  }
  else if (statu[s] == 1) {
    
    digitalWrite(RedLed, HIGH);
  }
  delay(1000);
cont:
  delay(2000);
  digitalWrite(GreenLed, LOW);
  digitalWrite(RedLed, LOW);
}

