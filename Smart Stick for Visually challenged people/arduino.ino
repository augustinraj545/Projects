#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Ultrasonic.h>
#include <SD.h>
#include <TMRpcm.h>
#include <SPI.h>

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

Ultrasonic ultrasonic(12, 13); // Trigger pin, Echo pin

TMRpcm audio;

const int chipSelect = 5; // Pin connected to the SD card module

void setup() {
  Serial.begin(9600);

  // Initialize OLED display
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(2);
  display.setCursor(0, 0);
  display.println("Smart Stick");
  display.display();
  delay(2000);
  display.clearDisplay();
// Initialize SD card
  if (!SD.begin(chipSelect)) {
    Serial.println("SD card initialization failed!");
    while (1);
  }
// Initialize audio
  audio.speakerPin = 25; // Pin connected to the headset
  audio.setVolume(5); // Set audio volume (0-7)

  audio.play("welcome.wav"); // Play welcome audio file
  delay(2000);
}

void loop() {
// Measure distance using ultrasonic sensor
  float dist = ultrasonic.read();
// Convert distance to centimeters
  dist = dist / 29 / 2;
// Display distance on OLED display
  display.clearDisplay();
  display.setCursor(0, 0);
  display.setTextSize(2);
  display.print("Distance:");
  display.setTextSize(3);
  display.setCursor(0, 25);
  display.print(dist);
  display.setTextSize(2);
  display.print(" cm");
  display.display();
// Output distance to serial monitor
  Serial.print("Distance: ");
  Serial.print(dist);
  Serial.println(" cm");
// Check if an obstacle is detected within a specific range
  if (dist < 30) {
// Play obstacle audio file
    audio.play("obstacle.wav");
    delay(2000);
  }

  delay(500); // Adjust delay as needed for the desired update rate
}
