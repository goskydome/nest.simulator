#include <RF22ReliableDatagram.h>
#include <RF22.h>
#include <SPI.h>
 

#define SERVER_ADDRESS 0

// Class to manage message delivery and receipt, using the driver declared above
RF22ReliableDatagram manager(SERVER_ADDRESS);


void setup() { 
  Serial.begin(9600);
  /// RF initialization must be before network initialization, otherwise RF will not initialize!
  if (manager.init())
    Serial.println(F("init success"));
  else
    Serial.println(F("init failed"));
}


void loop() { 
  uint8_t buf[2] PROGMEM;
  if (manager.available()) {
    uint8_t len = 2;
    uint8_t from;
    if (manager.recvfromAck(buf, &len, &from)) {
      Serial.print(buf[0]); 
      Serial.print(":"); 
      Serial.println(buf[1]); 
      // Send a reply back to the originator client
      if (!manager.sendtoWait(buf, 2, from)) {
        Serial.println("SendToWait Failed!");
        //// alarm to a red led !!!
      }
    }
  }
}
