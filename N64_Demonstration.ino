/**
   Simple demonstration of communication with a Nintendo 64 controller
*/

#include "N64_Interface.h"

//Global variables
N64_Interface interface;
N64_Status status, oldStatus;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  //Start by clearing the status variables
  memset(&status, 0, sizeof(status));
  memset(&oldStatus, 0, sizeof(oldStatus));
}

void loop() {
  // put your main code here, to run repeatedly:

  noInterrupts();
  interface.send(&COMMAND_STATUS, 1); //this is how we send the status query (1 byte)
  interface.receive((char*) &status, 4); //this is how we receive the status response (4 bytes)
  interrupts();

  if (memcmp(&status, &oldStatus, sizeof(status))) { //if the status has changed
    PrintN64Status(status);
    oldStatus = status;
  }

  delay(50);
}
