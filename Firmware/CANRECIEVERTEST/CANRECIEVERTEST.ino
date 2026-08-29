#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "driver/twai.h"

#define CAN_TX GPIO_NUM_18
#define CAN_RX GPIO_NUM_5

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

int rpm = 0;
int speedMPH = 0;
int coolantTemp = 0;



void setup() {
  //Reciever test
   Serial.begin(115200);
  delay(1000);

  // ---------------- OLED ----------------
  Wire.begin(22, 21);

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("OLED initialization FAILED!");
    while (true);
  }

  display.clearDisplay();
  display.display();

  // ---------------- CAN ----------------
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

  Serial.println("CAN Dashboard Ready!");
}
void decodeCAN() {

  twai_message_t message;

  if (twai_receive(&message, pdMS_TO_TICKS(100)) == ESP_OK) {

    if (message.identifier == 0x100 &&
        message.data_length_code >= 4) {

      rpm = (message.data[0] << 8) | message.data[1];

      speedMPH = message.data[2];

      coolantTemp = message.data[3];

      Serial.print("RPM: ");
      Serial.print(rpm);

      Serial.print(" | Speed: ");
      Serial.print(speedMPH);

      Serial.print(" | Coolant: ");
      Serial.println(coolantTemp);
    }
  }
}
void updateDisplay() {

  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);

  display.setTextSize(1);

  display.setCursor(20, 0);
  display.println("CAN DASHBOARD");

  display.setCursor(0, 18);
  display.print("RPM: ");
  display.println(rpm);

  display.setCursor(0, 32);
  display.print("SPEED: ");
  display.print(speedMPH);
  display.println(" MPH");

  display.setCursor(0, 46);
  display.print("COOLANT: ");
  display.print(coolantTemp);
  display.println(" F");

  display.display();
}

void loop() {
  twai_message_t message;

  decodeCAN();
  updateDisplay();
}
