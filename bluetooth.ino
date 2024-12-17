#include <LiquidCrystal.h>
#include <SoftwareSerial.h>

#define FORWARD 'F'
#define BACKWARD 'B'
#define LEFT 'L'
#define RIGHT 'R'
#define STOP 'S'

//const int rs = 8, en = 9, d4 = 4, d5 = 5, d6 = 6, d7 = 7;
//LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

int ENA = 3;
int ENB = 11;

int motor1pin1 = 10 ;
int motor1pin2 = 2;

int motor2pin1 = 12;
int motor2pin2 = 13;

SoftwareSerial BTSerial (0, 1);

void setup() {
  Serial.begin(9600);  // Set the baud rate for serial communication
  // Initialize any other necessary setup code here
  pinMode(motor1pin1, OUTPUT);
  pinMode(motor1pin2, OUTPUT);
  pinMode(motor2pin1, OUTPUT);
  pinMode(motor2pin2, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
}

void loop() {
  if (Serial.available()) {
    char command = Serial.read();
    executeCommand(command);
  }
  // Continue with other tasks in your main loop
}

void executeCommand(char command) {
  switch (command) {
    case FORWARD:
      // Perform action for moving forward
      digitalWrite(motor1pin1, HIGH);
      digitalWrite(motor1pin2, LOW);   // Motor 1 forward
      analogWrite(ENA, 120);          // Enable Motor 1
      analogWrite(ENB, 120);  
      digitalWrite(motor2pin1, HIGH);
      digitalWrite(motor2pin2, LOW);  // Motor 2 forward
      break;

    case BACKWARD:
      // Perform action for moving backward
      digitalWrite(motor1pin1, LOW);
      digitalWrite(motor1pin2, HIGH);   // Motor 1 forward
      analogWrite(ENA, 120);          // Enable Motor 1
      analogWrite(ENB, 120);  
      digitalWrite(motor2pin1, LOW);
      digitalWrite(motor2pin2, HIGH);  // Motor 2 forward

      break;
    case LEFT:
      // Perform action for turning left
      digitalWrite(motor1pin1, LOW);
      digitalWrite(motor1pin2, HIGH);  // Motor 1 backward
      analogWrite(ENA, 140);
      analogWrite(ENB, 255);
      digitalWrite(motor2pin1, HIGH);
      digitalWrite(motor2pin2, LOW);   // Motor 2 forward
      break;

    case RIGHT:
      // Perform action for turning right
      digitalWrite(motor1pin1, HIGH);
      digitalWrite(motor1pin2, LOW);   // Motor 1 forward
      analogWrite(ENA, 255);
      analogWrite(ENB, 140);
      digitalWrite(motor2pin1, LOW);
      digitalWrite(motor2pin2, HIGH);  // Motor 2 backward
      break;

    case STOP:
      digitalWrite(motor1pin1, LOW);
      digitalWrite(motor1pin2, LOW);   // Motor 1 forward
      analogWrite(ENA, 0);
      analogWrite(ENB, 0);
      digitalWrite(motor2pin1, LOW);
      digitalWrite(motor2pin2, LOW);

    default:
      // Invalid command received
  break;
}
}