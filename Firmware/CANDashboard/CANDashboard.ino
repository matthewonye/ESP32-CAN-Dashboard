 // ESP32 CAN DASHBOARD By Matthew Onye //
 // Date Started 8/5/26//

#include "driver/twai.h"

#define CAN_TX GPIO_NUM_18
#define CAN_RX GPIO_NUM_5


void setup() 
{
  
  //Testing Code:
   Serial.begin(115200);
  delay(1000);

  Serial.println("CAN Transmitter Starting...");

  twai_general_config_t g_config =
      TWAI_GENERAL_CONFIG_DEFAULT(CAN_TX, CAN_RX, TWAI_MODE_NORMAL);

  twai_timing_config_t t_config =
      TWAI_TIMING_CONFIG_500KBITS();

  twai_filter_config_t f_config =
      TWAI_FILTER_CONFIG_ACCEPT_ALL();

  if (twai_driver_install(&g_config, &t_config, &f_config) != ESP_OK) {
    Serial.println("TWAI driver install FAILED!");
    return;
  }

  if (twai_start() != ESP_OK) {
    Serial.println("TWAI start FAILED!");
    return;
  }

  Serial.println("CAN Transmitter Ready!");
//------------------------------------------------------------------------------------

}

void loop() 
{
   twai_message_t message = {};

  message.identifier = 0x100;
  message.data_length_code = 4;

  message.data[0] = 0x01;
  message.data[1] = 0x02;
  message.data[2] = 0x03;
  message.data[3] = 0x04;

  if (twai_transmit(&message, pdMS_TO_TICKS(1000)) == ESP_OK) {
    Serial.println("Message sent!");
  } else {
    Serial.println("Message FAILED!");
  }

  delay(1000);


}
