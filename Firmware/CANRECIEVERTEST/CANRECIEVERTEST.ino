#include "driver/twai.h"

#define CAN_TX GPIO_NUM_18
#define CAN_RX GPIO_NUM_5




void setup() {
  //Reciever test
   Serial.begin(115200);
  delay(1000);

  Serial.println("CAN Receiver Starting...");

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

  Serial.println("CAN Receiver Ready!");
}

void loop() {
  twai_message_t message;

  if (twai_receive(&message, pdMS_TO_TICKS(1000)) == ESP_OK) {

    Serial.print("CAN ID: 0x");
    Serial.println(message.identifier, HEX);

    Serial.print("Data: ");

    for (int i = 0; i < message.data_length_code; i++) {

      if (message.data[i] < 0x10) {
        Serial.print("0");
      }

      Serial.print(message.data[i], HEX);
      Serial.print(" ");
    }

    Serial.println();
    Serial.println("----------------");
  }
}
