#include <LiquidCrystal.h>

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

//motor a
int enA = 3;
int in1 = 2;
int in2 = 1;
//motor B
int enB = 11;
int in3 = 12;
int in4 = 13;
//IR sensors
int IR1 = A3;
int IR2 = A2;
//rotary encoders
int RE1 = A4;
int RE2 = A5;
//figuring out distance
float time = 0;
float L_distance = 0;
float R_distance = 0;
//sensitivity IR1
int sens1 = 750;
//sensitivity IR2
int sens2 = 750;


//int StartTime;
//int interval = 10000;


void setup() {
  lcd.begin(16, 2);

  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(IR1, INPUT);
  pinMode(IR2, INPUT);
  pinMode(RE1, INPUT);
  pinMode(RE2, INPUT);


  digitalWrite(enA, LOW);
  digitalWrite(enB, LOW);
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);

  lcd.setCursor(0, 0);

  digitalWrite(enA, HIGH);
  digitalWrite(enB, HIGH);
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);

  //lcd.print("Moving for 10s");
  //delay(1000);
  //lcd.clear();
  //StartTime = millis();
}

void loop() {
  int elapsedtime = millis();// - StartTime;
  //int timeleft = (interval - elapsedtime) / 1000;
  lcd.setCursor(0, 0);
  lcd.print("Time Elapsed:");
  lcd.setCursor(0, 1);
  lcd.print(elapsedtime/1000);

  int Right = 10*analogRead(IR1); // Reads the Analog Value on Pin A0 and store it in "Right".
  int Left = 10*analogRead(IR2); // Reads the Analog Value on Pin A1 and store it in "Left".
  if((Right < sens1) && (Left < sens2)){ // Both Sensors detect White Surface
    digitalWrite(in1,HIGH);
    digitalWrite(in2,LOW);
    digitalWrite(in4,HIGH);
    digitalWrite(in3,LOW);
    analogWrite(enA, 110);
    analogWrite(enB, 110);
  }
  if((Right > sens1) && (Left > sens2)){ // Both Sensors detect Black Line
    delay(50);
    digitalWrite(in1,LOW);
    digitalWrite(in2,LOW);
    digitalWrite(in4,LOW);
    digitalWrite(in3,LOW);
    analogWrite(enA,0);
    analogWrite(enB,0);
  }

  if((Right > sens1) && (Left < sens2)){ // Right Sensors detects Black Line and Left sensor detects White Surface.
    digitalWrite(in1,LOW);
    digitalWrite(in2,HIGH);
    digitalWrite(in4,HIGH);
    digitalWrite(in3,LOW);
    analogWrite(enA,255);
    analogWrite(enB,100);
    delay(50);
    
  }

  if((Right < sens1) && (Left > sens2)){ // Right Sensor detects White Surface and Left sensor detects Black Line.
    digitalWrite(in1,HIGH);
    digitalWrite(in2,LOW);
    digitalWrite(in4,LOW);
    digitalWrite(in3,HIGH);
    analogWrite(enA,100);
    analogWrite(enB,255);
    delay(50);
    
  }
  }
  //delay(1000);