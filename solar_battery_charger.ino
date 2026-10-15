#include <Servo.h>  // Include the Servo library to control the servo motor

Servo sg90;  // Create a Servo object named sg90

// Define the analog pins connected to the two LDR sensors
const int LDR1 = A0;  // Left-side LDR sensor input pin
const int LDR2 = A1;  // Right-side LDR sensor input pin

// Define the digital pin connected to the servo motor
const int servoPin = 4;  // Servo signal wire is connected to pin 4

// Initialize the servo position and sensitivity
int servoPosition = 90;  // Set the initial servo angle to 90 degrees
const int error = 5;     // Minimum difference between LDR readings required to move the servo

void setup()
{
  // Initialize serial communication at 9600 baud rate
  Serial.begin(9600);

  // Configure both LDR pins as input pins
  pinMode(LDR1, INPUT);
  pinMode(LDR2, INPUT);

  // Attach the servo motor to digital pin 4
  sg90.attach(servoPin);

  // Move the servo to its initial position of 90 degrees
  sg90.write(servoPosition);

  // Wait for one second to allow the servo to reach its initial position
  delay(1000);
}

void loop()
{
  // Read the analog light intensity value from the left LDR sensor
  int sensorLeft = analogRead(LDR1);

  // Read the analog light intensity value from the right LDR sensor
  int sensorRight = analogRead(LDR2);

  // Display the left LDR sensor reading in the Serial Monitor
  Serial.print("LDR1: ");
  Serial.print(sensorLeft);

  // Display the right LDR sensor reading in the Serial Monitor
  Serial.print("    LDR2: ");
  Serial.println(sensorRight);

  // Calculate the absolute difference between the two sensor readings
  int diff = abs(sensorLeft - sensorRight);

  // Check whether the difference exceeds the specified sensitivity threshold
  if (diff > error)
  {
    // If the left LDR reading is higher, decrease the servo angle
    if (sensorLeft > sensorRight && servoPosition > 0)
    {
      servoPosition--;  // Decrease the servo position by one degree
    }

    // If the right LDR reading is higher, increase the servo angle
    else if (sensorRight > sensorLeft && servoPosition < 180)
    {
      servoPosition++;  // Increase the servo position by one degree
    }

    // Move the servo motor to the newly calculated position
    sg90.write(servoPosition);
  }

  // Wait 20 milliseconds before reading the sensors again
  delay(20);
}
