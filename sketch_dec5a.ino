// Define pins for HC-SR04
const int trigPin = 5; // Trigger pin
const int echoPin = 6; // Echo pin

// Define pins for motor control
int enB = 11;
int in3 = 12;
int in4 = 13;
//motor A 
int enA = 3;
int in1 = 2;
int in2 = 10;

// Set the threshold distance in cm
const int thresholdDistance = 20; // Stop when object is closer than 20 cm

void setup() {
  // Initialize serial communication for debugging
  Serial.begin(9600);

  // Set up ultrasonic sensor pins
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // Set up motor pins
 pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);


  // Stop motors initially
  stopMotors();
}

void loop() {
  // Measure the distance
  long distance = measureDistance();

  // Print the distance for debugging
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  // Control the robot based on distance
  if (distance > thresholdDistance) {
    moveForward();
  } else {
    stopMotors();
    delay(500); // Pause for a moment
    moveBackward();
    delay(1000); // Move backward for 1 second
    spin180();
    stopMotors();
  }

  delay(100); // Short delay before next measurement
}

void moveForward() {
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    digitalWrite(in4, LOW);
    digitalWrite(in3, HIGH);
    analogWrite(enA, 110);
    analogWrite(enB, 110);   // Motor 2 forward
}

void moveBackward() {
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    digitalWrite(in4, HIGH);
    digitalWrite(in3, LOW);
    analogWrite(enA, 110);
    analogWrite(enB, 110); 
}

void stopMotors() {
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    digitalWrite(in4, LOW);
    digitalWrite(in3, LOW);
    analogWrite(enA, 0);
    analogWrite(enB, 0);
}

void spin180() {
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    digitalWrite(in4, HIGH);
    digitalWrite(in3, LOW);
    analogWrite(enA, 255);
    analogWrite(enB, 255);
    delay(1000);
}

long measureDistance() {
  // Send a 10-microsecond pulse to the trigger pin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Measure the duration of the echo pin signal
  long duration = pulseIn(echoPin, HIGH);

  // Calculate the distance in cm
  long distance = duration * 0.034 / 2; // Speed of sound = 343 m/s

  return distance;
}