#include <SoftwareSerial.h>
#include "VoiceRecognitionV3.h"

VR myVR(2,3);    // 2:RX 3:TX

uint8_t records[7]; // save record
uint8_t buf[64];

#define TRIGGER_PIN_1 12 
#define TRIGGER_PIN_2 11

#define onRecord  (0)
#define offRecord (1)
#define inRecord  (2)
#define outRecord (3)

void printSignature(uint8_t *buf, int len)
{
  int i;
  for(i=0; i<len; i++)
  {
    if(buf[i]>0x19 && buf[i]<0x7F)
    {
      Serial.write(buf[i]);
    }
    else
    {
      Serial.print("[");
      Serial.print(buf[i], HEX);
      Serial.print("]");
    }
  }
}

void printVR(uint8_t *buf)
{
  Serial.println("VR Index\tGroup\tRecordNum\tSignature");

  Serial.print(buf[2], DEC); Serial.print("\t\t");
  if(buf[0] == 0xFF)
  {
    Serial.println("NONE");
  }
  else if(buf[0]&0x80)
  {
    Serial.print("UG");
    Serial.println(buf[0]&(~0x80), DEC);
  }
  else
  {
    Serial.print("SG");
    Serial.println(buf[0], DEC);
  }

  Serial.print(buf[1], DEC); Serial.print("\t\t");
  if(buf[3]>0)
  {
    printSignature(buf+4, buf[3]);
  }
  else
  {
    Serial.println("NONE");
  }
  Serial.println("\r\n");
}

void setup()
{
  myVR.begin(9600);

  Serial.begin(115200);
  Serial.println("Elechouse Voice Recognition V3 Module\r\n");
  
  pinMode(TRIGGER_PIN_1, OUTPUT);
  pinMode(TRIGGER_PIN_2, OUTPUT);

  if(myVR.clear() == 0)
  {
    Serial.println("Recognizer cleared.");
  }
  else
  {
    Serial.println("Not find VoiceRecognitionModule. Please check connection");
    while(1);
  }

  if(myVR.load((uint8_t)onRecord) >= 0)
  {
    Serial.println("onRecord loaded");
  }
  if(myVR.load((uint8_t)offRecord) >= 0)
  {
    Serial.println("offRecord loaded");
  }
  if(myVR.load((uint8_t)inRecord) >= 0)
  {
    Serial.println("inRecord loaded");
  }
  if(myVR.load((uint8_t)outRecord) >= 0)
  {
    Serial.println("outRecord loaded");
  }
}

void loop()
{
  int ret;
  ret = myVR.recognize(buf, 50);
  if(ret>0)
  {
    switch(buf[1])
    {
      case onRecord:
        digitalWrite(TRIGGER_PIN_1, HIGH);
        digitalWrite(TRIGGER_PIN_2, HIGH);
        break;
      case offRecord:
        digitalWrite(TRIGGER_PIN_1, HIGH);
        digitalWrite(TRIGGER_PIN_2, LOW);
        break;
      case inRecord:
        digitalWrite(TRIGGER_PIN_1, LOW);
        digitalWrite(TRIGGER_PIN_2, HIGH);
        break;
      case outRecord:
        digitalWrite(TRIGGER_PIN_1, LOW);
        digitalWrite(TRIGGER_PIN_2, LOW);
        break;
      default:
        Serial.println("Record function undefined");
        break;
    }
    printVR(buf);
    delay(100);
    digitalWrite(TRIGGER_PIN_1, LOW);
    digitalWrite(TRIGGER_PIN_2, LOW);
  }
}
