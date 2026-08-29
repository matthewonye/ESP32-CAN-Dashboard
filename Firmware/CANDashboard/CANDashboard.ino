 // ESP32 CAN DASHBOARD By Matthew Onye //
 // Date Started 8/5/26//

#include "driver/twai.h"

#define CAN_TX GPIO_NUM_18
#define CAN_RX GPIO_NUM_5

int rpm = 900;
int speedMPH = 0;
int coolantTemp = 170;
bool accelerating = true;


void setup() 
{
  
  //Testing Code:
   Serial.begin(115200);
  delay(1000);

  twai_general_config_t g_config =
      TWAI_GENERAL_CONFIG_DEFAULT(CAN_TX, CAN_RX, TWAI_MODE_NORMAL);

  twai_timing_config_t t_config =
      TWAI_TIMING_CONFIG_500KBITS();

  twai_filter_config_t f_config =
      TWAI_FILTER_CONFIG_ACCEPT_ALL();

  if (twai_driver_install(&g_config, &t_config, &f_config) != ESP_OK) {
    Serial.println("TWAI install FAILED!");
    return;
  }

  if (twai_start() != ESP_OK) {
    Serial.println("TWAI start FAILED!");
    return;
  }

  Serial.println("Fake Vehicle Ready!");
}

void updateVehicleData() {

  if (accelerating) {
    rpm += 200;
    speedMPH += 2;

    if (rpm >= 4500) {
      accelerating = false;
    }
  }
  else {
    rpm -= 250;
    speedMPH -= 2;

    if (rpm <= 900) {
      rpm = 900;
      speedMPH = 0;
      accelerating = true;
    }
  }

  if (speedMPH > 0 && coolantTemp < 195) {
    coolantTemp++;
  }
}



void sendVehicleData() {

  twai_message_t message = {};

  message.identifier = 0x100;
  message.data_length_code = 5;

  // RPM needs 2 bytes because it can exceed 255
  message.data[0] = (rpm >> 8) & 0xFF;
  message.data[1] = rpm & 0xFF;

  message.data[2] = speedMPH;
  message.data[3] = coolantTemp;

  // Reserved for future data
  message.data[4] = 0;

  if (twai_transmit(&message, pdMS_TO_TICKS(100)) == ESP_OK) {
    Serial.print("Sent | RPM: ");
    Serial.print(rpm);
    Serial.print(" Speed: ");
    Serial.print(speedMPH);
    Serial.print(" Coolant: ");
    Serial.println(coolantTemp);
  }
  else {
    Serial.println("CAN transmit FAILED!");
  }
}
void loop() 
{
  updateVehicleData();
  sendVehicleData();

  delay(500);


}
