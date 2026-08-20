 // ESP32 CAN DASHBOARD By Matthew Onye //
 // Date Started 8/5/26//

#include <SPI.h>
#include <mcp_can.h>

#define CAN_CS 5

MCP_CAN CAN(CAN_CS);


void setup() 
{
  Serial.begin(115200);
  delay(1000);

  Serial.println("Starting MCP2515 test...");
  if (CAN.begin(MCP_ANY, CAN_500KBPS, MCP_8MHZ) == CAN_OK) {
    Serial.println("MCP2515 initialized successfully!");
  } else {
    Serial.println("MCP2515 initialization FAILED.");
  }

  CAN.setMode(MCP_NORMAL);

}

void loop() 
{
  // put your main code here, to run repeatedly:

}
