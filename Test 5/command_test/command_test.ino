#include <Servo.h>

Servo thruster;
Servo thruster2;

int pinThruster = 6;
int pinThruster2 = 5;

void setup() {
  Serial.begin(9600);

  thruster.attach(pinThruster);
  thruster2.attach(pinThruster2);

  thruster.writeMicroseconds(1500);
  thruster2.writeMicroseconds(1500);
  Serial.println("Thrusters en stop (1500 µs)");
  delay(3000);
}

void loop() {

  if (Serial.available() > 0) {
    char command = Serial.read();

    switch (command) {
      case 'F': 
      
        thruster.writeMicroseconds(1600);
        thruster2.writeMicroseconds(1600);
        break;

      case 'B': 
        thruster.writeMicroseconds(1400);
        thruster2.writeMicroseconds(1400);
        break;
    }

    delay(3000);

    thruster.writeMicroseconds(1500);
    thruster2.writeMicroseconds(1500);
  }
}
