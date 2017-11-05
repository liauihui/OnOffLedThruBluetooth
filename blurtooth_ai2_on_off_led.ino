/*
 Bluetooth AT Command 傳送 kah 接收。 
序列視窗下腳 e (沒有行結尾) 選項，愛考慮,試用 zitlex!
配對密碼:1234

...
 */

//HC-06 AT COMMAND:
//AT               // OK
//AT+NAMEJOY2      // Name=JOY2
//AT+VERSION       // panfpunr
//AT+BAUD4         // Baud=9600
//AT+ROLE          // not support
//AT+ADDR          // not support 
//AT+PSWD          // not support
//AT+UART          // not support

#ifndef SS_SOFTWARE_SERIAL
#define SS_SOFTWARE_SERIAL
#include <SoftwareSerial.h>
#endif

static const String sOnLed="OnLed";
static const String sOffLed="OffLed";
static const String sA="A";
static const String sB="B";

enum { UnoBoard_Rx=10, UnoBoard_Tx=11, Baud=9600, AdditionalLedPin=2 };
SoftwareSerial BT(UnoBoard_Rx, UnoBoard_Tx);  // Bluetooth_Tx===UnoBoard_Rx
void setup() {

  Serial.begin(Baud);
  BT.begin(Baud);

  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(AdditionalLedPin, OUTPUT);

  Serial.println(
     String("Serial begin Baud=")+
     String(Baud)+
     String(" OnBoard Rx=")+
     String(UnoBoard_Rx)+
     String(" OnBoard Tx=")+
     String(UnoBoard_Tx)
     );
}

//-----------------------------
void loop() {

  String s="";
  char c=0x00; 
  
  while( BT.available() ){ 
    c=BT.read();
    Serial.write( c );
    s=s+String(c);
  }
  
  if( 0 != s.length() ){ 
    if( s.equalsIgnoreCase(sOnLed) || s.equalsIgnoreCase(sA)) {
      digitalWrite(LED_BUILTIN, HIGH);  
      digitalWrite(AdditionalLedPin,HIGH);
    }
    else if( s.equalsIgnoreCase(sOffLed) || s.equalsIgnoreCase(sB)) {
      digitalWrite(LED_BUILTIN, LOW);  
      digitalWrite(AdditionalLedPin, LOW);  
    }  
    else { 
      Serial.print( String("BtMsg:[")+s+String("]") );
    }
  }

  s="";
  c=0x00;  
  while( Serial.available() ){
    c=Serial.read();
    BT.write( c );
    s=s+String(c);
  }
  
  //if( 0 != s.length() ){ 
  //}

}
