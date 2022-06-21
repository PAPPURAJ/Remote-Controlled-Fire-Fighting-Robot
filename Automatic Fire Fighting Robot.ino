#include <IRremote.h>

#define echoPin 12
#define trigPin 10

int frontIR = A5, backIR = A2, leftIR = A3, rightIR = A4;

int fV = 0, bV = 0, lV = 0, rV = 0;

float distance = 0, minDis = 200;

int RECV_PIN = A0;
IRrecv irrecv(RECV_PIN);

decode_results results;

int leftFront = 7;
int leftBack = 6;
int rightFront = 5;
int rightBack = 4;
int pump = 3;

int result = 0;

void setup()

{
  Serial.begin(9600);
  irrecv.enableIRIn();

  pinMode(frontIR, INPUT);
  pinMode(backIR, INPUT);
  pinMode(leftIR, INPUT);
  pinMode(rightIR, INPUT);


  pinMode(13, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(leftFront, OUTPUT);
  pinMode(leftBack, OUTPUT);
  pinMode(rightFront, OUTPUT);
  pinMode(rightBack, OUTPUT);
  pinMode(pump, OUTPUT);


}

bool autoMode = false;

void loop() {

  if (irrecv.decode(&results)) {

    result = results.value;

    if (result == 8925) {
      autoMode = !autoMode;
      Serial.println(autoMode ? "Auto driving enabled!" : "Manual driving enabled!");
      digitalWrite(13, autoMode);
      delay(300);
    }


    irrecv.resume(); // Receive the next value }

  }   autoMode ? autoDrive() : manualDrive(result);




}



void autoDrive() {
  Serial.println("Auto");
  delay(300);

  getSensor();

  Serial.print("Front: " + String(fV) + " | Back: " + String(bV) + " | Left: " + String(lV) + " | Right: " + String(rV) + "   |   ");
  getDistance();


  if (lV || bV)
  {
    left();
    delay(1700);
    off();
  }
  else if (rV) {
    right();
    delay(1700);
    off();
  }

  else if (fV) {

    while (fV) {
      Serial.println("Distance: " + String(distance));
      getSensor();
      getDistance();
      if (distance > minDis) {
        front();
      } else {
        off();
        if (fV) {
          pumpOn();
        } else {
          pumpOff();
          break;
        }
      }
    }


  } else {
    off();
    pumpOff();
  }


}

void manualDrive(int val) {
  switch (val) {
    case 6375:
      front();
      break;

    case 19125:
      back();
      break;

    case 4335:
      left();
      break;

    case 23205:
      right();
      break;

    case -23971:
      pumpOn();

      break;

    case 25245:
      pumpOff();
      break;


    case 14535:
      off();
      break;

  }
}


void getSensor() {
  fV = !digitalRead(frontIR);
  bV = !digitalRead(backIR);
  lV = !digitalRead(leftIR);
  rV = !digitalRead(rightIR);
}

void front() {
  digitalWrite(leftFront, 1);
  digitalWrite(leftBack, 0);
  digitalWrite(rightFront, 1);
  digitalWrite(rightBack, 0);
  Serial.println("Front");
}

void back() {
  digitalWrite(leftFront, 0);
  digitalWrite(leftBack, 1);
  digitalWrite(rightFront, 0);
  digitalWrite(rightBack, 1);
  Serial.println("Back");
}

void left() {
  digitalWrite(leftFront, 0);
  digitalWrite(leftBack, 0);
  digitalWrite(rightFront, 1);
  digitalWrite(rightBack, 0);
  Serial.println("Left");
}

void right() {
  digitalWrite(leftFront, 1);
  digitalWrite(leftBack, 0);
  digitalWrite(rightFront, 0);
  digitalWrite(rightBack, 0);
  Serial.println("Right");
}

void off() {
  digitalWrite(leftFront, 0);
  digitalWrite(leftBack, 0);
  digitalWrite(rightFront, 0);
  digitalWrite(rightBack, 0);
  Serial.println("All Of");
}

void pumpOn() {
  digitalWrite(pump, 1);
  Serial.println("Pump On");
}

void pumpOff() {
  digitalWrite(pump, 0);
  Serial.println("Pump Off");
}


void getDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  distance =  pulseIn(echoPin, HIGH) * (0.034 / 2) * 10;
  Serial.println(String(distance))
