//===================================================================================
//      ARDUINO UNO BLUETOOTH RC RICKSHAW CODE WITH L298N & HC-05
//===================================================================================

//PIN CONNECTIONS:

//  [HC-05 Bluetooth Module]
//  - VCC  -> Arduino 5V
//  - GND  -> Arduino GND
//  - TXD  -> Arduino D2 (Software Serial RX)
//  - RXD  -> Arduino D3 (Software Serial TX)

//  [L298N Motor Driver]
//  - ENA  -> Arduino D8  (PWM Speed Left)
//  - IN1  -> Arduino D4  (Direction Left)
//  - IN2  -> Arduino D5  (Direction Left)
//  - IN3  -> Arduino D6  (Direction Right)
//  - IN4  -> Arduino D7  (Direction Right)
//  - ENB  -> Arduino D9 (PWM Speed Right)
  
//  [Power - 2S 18650 Battery Pack (~7.4V - 8.4V)]
//  - Positive (+) -> L298N 12V Terminal & Arduino VIN Pin
//  - Negative (-) -> L298N GND Terminal & Arduino GND Pin (Common Ground)

//===================================================================================


#include <SoftwareSerial.h>

// Define Bluetooth Pins
const int BT_RX = 2; 
const int BT_TX = 3; 
SoftwareSerial Bluetooth(BT_RX, BT_TX); // RX, TX

// Define L298N Motor Control Pins
const int ENA = 8;  
const int IN1 = 4;  
const int IN2 = 5;  
const int IN3 = 6;  
const int IN4 = 7;  
const int ENB = 9; 

// Initial speed variable (0 to 255)
int motorSpeed = 200; 

// Variable to store incoming Bluetooth commands
char command;

void setup() {
  // Initialize pin modes for L298N
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  
  // Stop all motors initially
  stopMotors();

  // Initialize Bluetooth Serial communication at 9600 baud rate
  Bluetooth.begin(9600);
}

void loop() {
  // Check if data is available from the Bluetooth module
  if (Bluetooth.available() > 0) {
    command = Bluetooth.read();
    
    // Execute movement based on the received command character
    switch (command) {
      case 'F':
        moveForward();
        break;
      case 'B':
        moveBackward();
        break;
      case 'L':
        turnLeft();
        break;
      case 'R':
        turnRight();
        break;
      case 'S':
        stopMotors();
        break;
    }
  }
}

// --- Movement Functions ---

void moveForward() {
  // Set speeds
  analogWrite(ENA, motorSpeed);
  analogWrite(ENB, motorSpeed);
  
  // Motor A Forward
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  // Motor B Forward
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void moveBackward() {
  // Set speeds
  analogWrite(ENA, motorSpeed);
  analogWrite(ENB, motorSpeed);
  
  // Motor A Backward
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  // Motor B Backward
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void turnLeft() {
  // Set speeds
  analogWrite(ENA, motorSpeed);
  analogWrite(ENB, motorSpeed);
  
  // Motor A Backward / Spin Left
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  // Motor B Forward
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void turnRight() {
  // Set speeds
  analogWrite(ENA, motorSpeed);
  analogWrite(ENB, motorSpeed);
  
  // Motor A Forward
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  // Motor B Backward / Spin Right
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void stopMotors() {
  // Cut off speed generation
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
  
  // Turn off all direction controls
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}