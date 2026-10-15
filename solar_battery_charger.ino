
#include <Servo.h>  

Servo sg90;

// Define the analog pins connected to the two LDR sensors
const int LDR1 = A0;  // Left-side LDR sensor
const int LDR2 = A1;  // Right-side LDR sensor

// Define the digital pin connected to the servo motor
const int servoPin = 4;

// Initialize the servo position and sensitivity
int servoPosition = 90;  // Set the initial servo position to 90 degrees
const int error = 5;     // Minimum light difference required to move the servo

void setup()
{
  // Start serial communication to display sensor values
  Serial.begin(9600);

  // Configure both LDR pins as input pins
  pinMode(LDR1, INPUT);
  pinMode(LDR2, INPUT);

  // Connect the servo motor to pin 4
  sg90.attach(servoPin);

  // Move the servo to its initial position
  sg90.write(servoPosition);

  // Wait for one second for the servo to reach its position
  delay(1000);
}

void loop()
{
  // Read the light intensity values from both LDR sensors
  int sensorLeft = analogRead(LDR1);
  int sensorRight = analogRead(LDR2);

  // Display both LDR readings in the Serial Monitor
  Serial.print("LDR1: ");
  Serial.print(sensorLeft);
  Serial.print("    LDR2: ");
  Serial.println(sensorRight);

  // Calculate the absolute difference between the two sensor readings
  int diff = abs(sensorLeft - sensorRight);

  // Move the servo only when the difference exceeds the threshold
  if (diff > error)
  {
    // If the left LDR receives a higher reading, rotate the servo left
    if (sensorLeft > sensorRight && servoPosition > 0)
    {
      servoPosition--;  // Decrease the servo angle by one degree
    }

    // If the right LDR receives a higher reading, rotate the servo right
    else if (sensorRight > sensorLeft && servoPosition < 180)
    {
      servoPosition++;  // Increase the servo angle by one degree
    }

    // Move the servo to the updated position
    sg90.write(servoPosition);
  }

  // Wait 20 milliseconds before taking the next readings
  delay(20);
}
