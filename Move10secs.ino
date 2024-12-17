#include <LiquidCrystal.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
#include <math.h>

Adafruit_MPU6050 mpu;

const int rs = 8, en = 9, d4 = 4, d5 = 5, d6 = 6, d7 = 7;
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
const int sPin1 = A0, sPin2 = A1;
//MOTOR B
int enB = 11;
int in3 = 12;
int in4 = 13;
//motor A
int enA = 3;
int in1 = 2;
int in2 = 10;
//rotary encoders
int RE1 = A0;
int RE2 = A1;
//IR sensors
int IR1 = A3;
int IR2 = A2;
//sensitivity IR1
int sens1 = 300;
//sensitivity IR2
int sens2 = 320;

int Dstate1 = 0;
int lastDstate1 = 0;
int Dstate2 = 0;
int lastDstate2 = 0;
double D1 = 0;
double D2 = 0;
double tD = 0;

unsigned long prevTime = 0;
float A = 0;
int bump = 0;
int spin = 0;
int stop = 0;
void setup() {

  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while (1) {
      delay(10);
    }
  }

  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);

  mpu.setGyroRange(MPU6050_RANGE_500_DEG);

  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);

  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);

  pinMode(IR1, INPUT);
  pinMode(IR2, INPUT);
  pinMode(sPin1, INPUT);
  pinMode(sPin2, INPUT);

  lcd.begin(16, 2);
  lcd.clear();

  digitalWrite(enA, LOW);
  digitalWrite(enB, LOW);
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}

void loop() {
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);
  /*if(spin > 0){
    Dstate1 = digitalRead(sPin1);
    if (Dstate1 != lastDstate1 && Dstate1 == 1) {
      D1= D1 + 1.16;
    }
    lastDstate1 = Dstate1;

    Dstate2 = digitalRead(sPin2);
    if (Dstate2 != lastDstate2 && Dstate2 == 1) {
      D2= D2 + 1.16;
    }
    lastDstate2 = Dstate2;
  }*/
  unsigned long currTime = millis();
  if (currTime - prevTime >= 200) {
    prevTime = currTime;
    lcd.clear();
    A = (atan(a.acceleration.x / a.acceleration.z) / 3.1415926 * 180) + 3;
    lcd.setCursor(0, 0);
    lcd.print("Time: ");
    lcd.print(currTime / 1000);
    lcd.print("s ");
    lcd.setCursor(0, 1);
    lcd.print("A: ");
    lcd.print(A, 1);
    lcd.setCursor(8, 1);
    lcd.print("D: ");
    tD = (D1 + D2) / 200;
    lcd.print(tD);
    lcd.print(" m");
    if (A > 24 && bump < 1 && spin < 1) {
      bump = bump + 1;

      analogWrite(enA, 0);
      analogWrite(enB, 0);
      delay(500);
        A = (atan(a.acceleration.x / a.acceleration.z) / 3.1415926 * 180) + 3;
        digitalWrite(in1, LOW);
        digitalWrite(in2, HIGH);
        digitalWrite(in4, LOW);
        digitalWrite(in3, HIGH);
        analogWrite(enA, 255);
        analogWrite(enB, 255);
        delay(2000);
      analogWrite(enA, 0);
      analogWrite(enB, 0);
      tD = -0.4;
    }
    if (A < 10 && bump > 0 && spin < 1) {
      spin = spin + 1;
      A = (atan(a.acceleration.x / a.acceleration.z) / 3.1415926 * 180) + 3;
      lcd.setCursor(0, 0);
      lcd.print("Time: ");
      lcd.print(currTime / 1000);
      lcd.print("s ");
      lcd.setCursor(0, 1);
      lcd.print("A: ");
      lcd.print(A, 1);
      lcd.setCursor(8, 1);
      lcd.print("D: ");
      lcd.print(tD);
      lcd.print("m");
      digitalWrite(in1, LOW);
      digitalWrite(in2, HIGH);
      digitalWrite(in4, LOW);
      digitalWrite(in3, HIGH);
      analogWrite(enA, 200);  // change
      analogWrite(enB, 200);  //change
      delay(50);

      analogWrite(enA, 0);
      analogWrite(enB, 0);
      delay(4000);
      digitalWrite(in1, LOW);
      digitalWrite(in2, HIGH);
      digitalWrite(in4, HIGH);
      digitalWrite(in3, LOW);
      analogWrite(enA, 255);
      analogWrite(enB, 150);
      delay(5000);
      bump = 1;
      analogWrite(enA, 0);
      analogWrite(enB, 0);
      delay(200);
      digitalWrite(in1, LOW);
      digitalWrite(in2, HIGH);
      digitalWrite(in4, LOW);
      digitalWrite(in3, HIGH);
      analogWrite(enA, 255);
      analogWrite(enB, 255);
      delay(1000);
    }
  }

  /*if (A<5 && bump>0 && spin >= 1) {
    int Right = analogRead(IR2);
    int Left = analogRead(IR1);
    int TurnRight = 0;
    if ((Right > sens1) && (Left > sens2) && spin<1) { // Move straight
      digitalWrite(in1, LOW);
      digitalWrite(in2, HIGH);
      digitalWrite(in4, LOW);
      digitalWrite(in3, HIGH);
      analogWrite(enA, 200);
      analogWrite(enB, 200);
          delay(40);
          analogWrite(enA, 0);
          analogWrite(enB, 0);
    }
    if ((Right > sens1) && (Left > sens2) && TurnRight>=1) { // Move straight
      digitalWrite(in1, LOW);
      digitalWrite(in2, HIGH);
      digitalWrite(in4, LOW);
      digitalWrite(in3, HIGH);
      analogWrite(enA, 110);
      analogWrite(enB, 110);
      delay(2000);
      analogWrite(enA, 0);
      analogWrite(enB, 0);
      delay(2000);
      bump++;
    } 
    if ((Right < sens1) && (Left < sens2)) { // Stop
      digitalWrite(in1, LOW);
      digitalWrite(in2, LOW);
      digitalWrite(in4, LOW);
      digitalWrite(in3, LOW);
      analogWrite(enA, 0);
      analogWrite(enB, 0);
          delay(15);
      analogWrite(enA, 0);
      analogWrite(enB, 0);
    } 
    if ((Right < sens1) && (Left > sens2)) { // Turn right
      digitalWrite(in1, LOW);
      digitalWrite(in2, HIGH);
      digitalWrite(in4, HIGH);
      digitalWrite(in3, LOW);
      analogWrite(enA, 150);
      analogWrite(enB, 255);
      delay(45);
          analogWrite(enA, 0);
          analogWrite(enB, 0);
          TurnRight++;
    } 
    if ((Right > sens1) && (Left < sens2)) { // Turn left
      digitalWrite(in1, HIGH);
      digitalWrite(in2, LOW);
      digitalWrite(in4, LOW);
      digitalWrite(in3, HIGH);
      analogWrite(enA, 150);
      analogWrite(enB, 255);
      delay(65);
          analogWrite(enA, 0);
          analogWrite(enB, 0);
    }
  }*/


  int Right = analogRead(IR2);
  int Left = analogRead(IR1);
  if ((Right > sens1) && (Left > sens2) && spin < 1) {  // Move straight
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    digitalWrite(in4, LOW);
    digitalWrite(in3, HIGH);
    analogWrite(enA, 200);
    analogWrite(enB, 200);
    delay(70);
    analogWrite(enA, 0);
    analogWrite(enB, 0);
  }
  if ((Right > sens1) && (Left > sens2) && spin >= 1) {  // Move straight
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    digitalWrite(in4, LOW);
    digitalWrite(in3, HIGH);
    analogWrite(enA, 120);
    analogWrite(enB, 120);
    delay(15);
    analogWrite(enA, 0);
    analogWrite(enB, 0);
  }
  if ((Right < sens1) && (Left < sens2)) {  // Stop
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    digitalWrite(in4, LOW);
    digitalWrite(in3, LOW);
    analogWrite(enA, 0);
    analogWrite(enB, 0);
    delay(15);
    analogWrite(enA, 0);
    analogWrite(enB, 0);
  }
  if ((Right < sens1) && (Left > sens2)) {  // Turn right
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    digitalWrite(in4, HIGH);
    digitalWrite(in3, LOW);
    analogWrite(enA, 150);
    analogWrite(enB, 255);
    delay(45);
    analogWrite(enA, 0);
    analogWrite(enB, 0);
  }
  if ((Right > sens1) && (Left < sens2)) {  // Turn left
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    digitalWrite(in4, LOW);
    digitalWrite(in3, HIGH);
    analogWrite(enA, 150);
    analogWrite(enB, 255);
    delay(65);
    analogWrite(enA, 0);
    analogWrite(enB, 0);
  }
}