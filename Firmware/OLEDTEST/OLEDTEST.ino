#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
// Simulated vehicle data
int rpm = 800;
int speedMPH = 0;
int coolantTemp = 170;

void updateVehicleData() {
 static bool accelerating = true;

  if (accelerating) {
    rpm += 200;
    speedMPH += 2;

    if (rpm >= 4500) {
      accelerating = false;
    }
  } else {
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

void updateDisplay() {
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);

  display.setTextSize(1);
  display.setCursor(20, 0);
  display.println("CAN DASHBOARD");

  display.setTextSize(1);
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




void setup() {
   Serial.begin(115200);

  Wire.begin(21, 22);

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("OLED initialization FAILED!");
    while (true);
  }

  Serial.println("Dashboard started!");

  display.clearDisplay();
  display.display();
}

void loop() {
  updateVehicleData();
  updateDisplay();

  delay(500);

}
