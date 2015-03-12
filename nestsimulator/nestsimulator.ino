#include <NanodeUNIO.h>
#include <NanodeUIP.h>
#include <NanodeMQTT.h>
#include <RF22ReliableDatagram.h>
#include <RF22.h>
#include <SPI.h>
 

//#define CLIENT_ADDRESS 1
#define SERVER_ADDRESS 0

// Class to manage message delivery and receipt, using the driver declared above
RF22ReliableDatagram manager(SERVER_ADDRESS);
const byte macaddr[] = { 0x74, 0x69, 0x69, 0x2D, 0x30, 0x31 };
const char topic[] = "skydome/7469692d3031";
int a = -1;
int b = -1;
int c = -1;
int d = -1;
const int DOT = 46;
const int EOI = 0;
 

void setup() {
  char buf[20] PROGMEM;
  Serial.begin(9600);
  /// RF initialization must be before network initialization, otherwise RF will not initialize!
  if (manager.init())
    Serial.println(F("init success"));
  else
    Serial.println(F("init failed"));
}


void loop() {
  uip.poll();

  uint8_t buf[2] PROGMEM;
  if (manager.available()) {
    uint8_t len = 2;
    uint8_t from;
    if (manager.recvfromAck(buf, &len, &from)) {
      uint8_t data[10] = { macaddr[0], macaddr[1], macaddr[2], macaddr[3], macaddr[4], macaddr[5], SERVER_ADDRESS, from, buf[0], buf[1]};
      uint8_t len = 10;
      Serial.print(buf[0]); 
      Serial.println(buf[1]); 
      // Send a reply back to the originator client
      if (!manager.sendtoWait(buf, 2, from)) {
        Serial.println("SendToWait Failed!");
        //// alarm to a red led !!!
      }
    }
  }
}
