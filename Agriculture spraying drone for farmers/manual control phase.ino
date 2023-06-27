#include <PPM.h>

// Create an instance of the PPM library
PPM ppm;

// Define the Arduino pin connected to the PPM signal
int ppmPin = 2;  // Use any available digital pin

// Define variables for drone control
int throttle;
int pitch;
int roll;
int yaw;

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
    int channel3 = ppm.channel(3);
    int channel4 = ppm.channel(4);
    // ... Add more channels as needed

    // Print the channel values for debugging
    Serial.print("Channel 1: ");
    Serial.print(channel1);
    Serial.print(" Channel 2: ");
    Serial.print(channel2);
    Serial.print(" Channel 3: ");
    Serial.print(channel3);
    Serial.print(" Channel 4: ");
    Serial.println(channel4);

    // Map the channel values to drone control variables
    throttle = map(channel1, 1000, 2000, -100, 100);
    pitch = map(channel2, 1000, 2000, -100, 100);
    roll = map(channel3, 1000, 2000, -100, 100);
    yaw = map(channel4, 1000, 2000, -100, 100);

    // Use the drone control variables to control the drone's movements
    // Implement appropriate drone control logic based on the channel values

    // Example: Print the control values for debugging
    Serial.print("Throttle: ");
    Serial.print(throttle);
    Serial.print(" Pitch: ");
    Serial.print(pitch);
    Serial.print(" Roll: ");
    Serial.print(roll);
    Serial.print(" Yaw: ");
    Serial.println(yaw);
  }
}
