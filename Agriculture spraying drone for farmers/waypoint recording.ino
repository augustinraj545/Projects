#include <EEPROM.h>
#include <PPM.h>

// Create an instance of the PPM library
PPM ppm;

// Define the Arduino pin connected to the PPM signal
int ppmPin = 2;  // Use any available digital pin

// Define the EEPROM address where the waypoints will be stored
int eepromAddress = 0;  // Start at address 0

// Define the interval at which waypoints will be recorded (in milliseconds)
unsigned long recordingInterval = 1000;  // Record every 1 second

// Define variables for storing GPS coordinates
float latitude;
float longitude;

// Define a variable to keep track of the recording time
unsigned long lastRecordTime = 0;

void setup() {
  // Initialize the PPM library
  ppm.begin(ppmPin);

  // Initialize Serial communication for debugging
  Serial.begin(9600);
}

void loop() {
  // Read the PPM signal from the remote controller
  if (ppm.read()) {
    // Get the channel values
    int channel1 = ppm.channel(1);
    int channel2 = ppm.channel(2);
    // ... Add more channels as needed

    // Record waypoints based on the recording interval
    if (millis() - lastRecordTime >= recordingInterval) {
      // Record the GPS coordinates at the current location
      latitude = /* code to get latitude from GPS module */;
      longitude = /* code to get longitude from GPS module */;

      // Store the GPS coordinates in the EEPROM
      EEPROM.put(eepromAddress, latitude);
      EEPROM.put(eepromAddress + sizeof(float), longitude);

      // Move the EEPROM address pointer to the next waypoint
      eepromAddress += sizeof(float) * 2;

      // Update the last recording time
      lastRecordTime = millis();

      // Print the recorded waypoint for debugging
      Serial.print("Waypoint recorded - Latitude: ");
      Serial.print(latitude, 6);
      Serial.print(" Longitude: ");
      Serial.println(longitude, 6);
    }
  }
}
