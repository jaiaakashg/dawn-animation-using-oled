#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1 
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup() {
  Serial.begin(115200);
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }

  display.clearDisplay();
  display.display();
  display.setCursor(0, 10);
  display.display();
  delay(2000); 
}

void loop() {
  simulateDawnAnimation();
  delay(30000); 
}

void simulateDawnAnimation() {
  for (int step = 0; step <= 100; step++) {
    display.clearDisplay();
    drawGradient(step);
    drawRisingSun(step);
    drawClouds(step);
    drawStars(step);
    display.display();
    delay(50); // 
  }
}

void drawGradient(int step) {
  for (int y = SCREEN_HEIGHT - 1; y >= 0; y--) {
    int brightness = map(y, 0, SCREEN_HEIGHT - 1, 0, step * 2.55);
    display.drawFastHLine(0, y, SCREEN_WIDTH, SSD1306_WHITE * (brightness > 127));
  }
}

void drawRisingSun(int step) {
  int radius = 10 + step / 5; 
  int sunY = SCREEN_HEIGHT - (step * 0.5); 
  int sunX = SCREEN_WIDTH / 2;
  
  display.fillCircle(sunX, sunY, radius, SSD1306_WHITE);
}

void drawClouds(int step) {
  int cloud1X = map(step, 0, 100, 0, -60);
  int cloud2X = map(step, 0, 100, 128, 68);
  display.fillRect(cloud1X, 20, 60, 10, SSD1306_WHITE);
  display.fillRect(cloud2X, 30, 60, 10, SSD1306_WHITE);
  int cloud3X = map(step, 0, 100, 0, -30);
  int cloud4X = map(step, 0, 100, 128, 98);
  display.fillRect(cloud3X, 40, 30, 8, SSD1306_WHITE);
  display.fillRect(cloud4X, 50, 30, 8, SSD1306_WHITE);
}

void drawStars(int step) {
  if (step < 50) {
    int numStars = 10;
    for (int i = 0; i < numStars; i++) {
      int starX = random(0, SCREEN_WIDTH);
      int starY = random(0, SCREEN_HEIGHT / 2);
      int brightness = 255 - step * 5; 
      if (brightness > 127) {
        display.drawPixel(starX, starY, SSD1306_WHITE);
      }
    }
  }
}

