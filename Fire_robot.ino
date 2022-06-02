#include <IRremote.h>

int RECV_PIN = A0;

IRrecv irrecv(RECV_PIN);

decode_results results;

int leftFront = 7;
int leftBack = 6;
int rightFront = 5;
int rightBack = 4;
int pump = 3;
;
void setup()

{

  Serial.begin(9600);
  irrecv.enableIRIn();
  pinMode(leftFront, OUTPUT);
  pinMode(leftBack, OUTPUT);
  pinMode(rightFront, OUTPUT);
  pinMode(rightBack, OUTPUT);
  pinMode(pump, OUTPUT);


}

void loop() {

  if (irrecv.decode(&results)) {

    int result = results.value;

    //    Serial.print(result);
    //    Serial.print(" ");
    //    Serial.print(results.value);
    //    Serial.print(" ");
    //    Serial.println(results.value, HEX);


    switch (result) {
      case 6375:

        digitalWrite(leftFront, 1);
        digitalWrite(leftBack, 0);
        digitalWrite(rightFront, 1);
        digitalWrite(rightBack, 0);
        Serial.println("Front");

        break;
      case 19125:


        digitalWrite(leftFront, 0);
        digitalWrite(leftBack, 1);
        digitalWrite(rightFront, 0);
        digitalWrite(rightBack, 1);
        Serial.println("Back");

        break;

      case 4335:

        digitalWrite(leftFront, 0);
        digitalWrite(leftBack, 0);
        digitalWrite(rightFront, 1);
        digitalWrite(rightBack, 0);
        Serial.println("Left");
        break;

      case 23205:

        digitalWrite(leftFront, 1);
        digitalWrite(leftBack, 0);
        digitalWrite(rightFront, 0);
        digitalWrite(rightBack, 0);
        Serial.println("Right");

        break;

      case -23971:
        digitalWrite(pump, 1);
        Serial.println("Pump On");

        break;

      case 25245:
        digitalWrite(pump, 0);
        Serial.println("Pump Off");
        break;


      case 14535:
        digitalWrite(leftFront, 0);
        digitalWrite(leftBack, 0);
        digitalWrite(rightFront, 0);
        digitalWrite(rightBack, 0);
        Serial.println("All Of");
        break;




    }

    irrecv.resume(); // Receive the next value }



  }
}
