#include <stdint.h>
#include "TouchScreen.h"
#include <MCUFRIEND_kbv.h>

#define YP 14 
#define XM 15
#define YM 16
#define XP 17

MCUFRIEND_kbv tft;

TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);

#define BUTTON_X     160
#define BUTTON_Y     200
#define BUTTON_WIDTH 120
#define BUTTON_HEIGHT 60
#define MINPRESSURE 10
#define MAXPRESSURE 1000
#define TEXT_X   (BUTTON_X + BUTTON_WIDTH / 4)
#define TEXT_Y   (BUTTON_Y + BUTTON_HEIGHT / 4)
int number = 0;


void setup(void) {
  
  Serial.begin(9600);
  int identifier = tft.readID();
  tft.begin(identifier);
  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(TFT_WHITE);
  tft.setTextSize(2);

  drawButton();
  Serial.println("Started");
  updateNumber();
}

void loop(void) {
  TSPoint p = ts.getPoint();

 
    Serial.print("X = "); Serial.print(p.x);
     Serial.print("\tY = "); Serial.print(p.y);
     Serial.print("\tPressure = "); Serial.println(p.z);
  

  // Adjust the pressure threshold for touch detection
  if (p.z > MINPRESSURE && p.z < MAXPRESSURE) {
    number++;
    updateNumber();
    delay(200); // Debounce delay
  }
}
void drawButton() {
  // Ensure coordinates and dimensions are correct
  tft.fillRect(BUTTON_X, BUTTON_Y, BUTTON_WIDTH, BUTTON_HEIGHT, TFT_BLUE);
  tft.drawRect(BUTTON_X, BUTTON_Y, BUTTON_WIDTH, BUTTON_HEIGHT, TFT_WHITE);
  tft.setCursor(TEXT_X, TEXT_Y);
  tft.setTextColor(TFT_WHITE);
  tft.setTextSize(2);
  tft.print("Press Me");
}



void updateNumber() {
  tft.fillRect(TEXT_X, TEXT_Y + 30, BUTTON_WIDTH / 2, BUTTON_HEIGHT / 2, TFT_BLACK);
  tft.setCursor(TEXT_X, TEXT_Y + 30);
  tft.setTextColor(TFT_WHITE);
  tft.setTextSize(2);
  tft.print(number);
}
