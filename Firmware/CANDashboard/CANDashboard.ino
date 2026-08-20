 // ESP32 CAN DASHBOARD By Matthew Onye //
 // Date Started 8/5/26//

#include <SPI.h>
#include <mcp_can.h>

#define CAN_CS 5

MCP_CAN CAN(CAN_CS);


void setup() 
{
  
  //Testing Code:
  Serial.begin(115200);
  delay(1000);

  Serial.println("CAN Transmitter Starting...");
 
  if (CAN.begin(MCP_ANY, CAN_500KBPS, MCP_8MHZ) == CAN_OK) {
    Serial.println("MCP2515 initialized successfully!");
  } else {
    Serial.println("MCP2515 initialization FAILED!");
    while (1);
  }

  CAN.setMode(MCP_NORMAL);
  Serial.println("CAN Transmitter Ready!");
//------------------------------------------------------------------------------------

}

void loop() 
{
  byte data[4] = {0x01, 0x02, 0x03, 0x04};

  byte result = CAN.sendMsgBuf(0x100, 0, 4, data);

  if (result == CAN_OK) {
    Serial.println("Message sent!");
  } else {
    Serial.println("Send failed!");
  }

  delay(1000);

}
