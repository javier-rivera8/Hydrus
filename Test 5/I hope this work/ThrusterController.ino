#include <Servo.h>

Servo motor1;
Servo motor2;
Servo motor3;
Servo motor4;
Servo motor5;
Servo motor7;
Servo motor8;

int pinMotor1 = 9;
int pinMotor2 = 3;
int pinMotor3 = 4;
int pinMotor4 = 5;
int pinMotor5 = 6;
int pinMotor7 = 8;
int pinMotor8 = 2;

void setup() {
  Serial.begin(9600);

  motor1.attach(pinMotor1);
  motor2.attach(pinMotor2);
  motor3.attach(pinMotor3);
  motor4.attach(pinMotor4);
  motor5.attach(pinMotor5);
  motor7.attach(pinMotor7);
  motor8.attach(pinMotor8);

  // Initialize all motors at stop
  stopAll();

  delay(3000); // Time for ESC 
  Serial.println("Arduino listo para recibir comandos");
}

void stopAll() {
  motor1.writeMicroseconds(1500);
  motor2.writeMicroseconds(1500);
  motor3.writeMicroseconds(1500);
  motor4.writeMicroseconds(1500);
  motor5.writeMicroseconds(1500);
  motor7.writeMicroseconds(1500);
  motor8.writeMicroseconds(1500);
}

void forward() {
  motor7.writeMicroseconds(1600);
  motor8.writeMicroseconds(1600);
}

void back() {
  motor7.writeMicroseconds(1400);
  motor8.writeMicroseconds(1400);
}

void left() {
  motor1.writeMicroseconds(1400);
  motor2.writeMicroseconds(1600);
}

void right() {
  motor1.writeMicroseconds(1600);
  motor2.writeMicroseconds(1400);
}

void up() {
  motor5.writeMicroseconds(1600);
  motor6.writeMicroseconds(1600);

}

void down() {
  motor5.writeMicroseconds(1400);
  motor6.writeMicroseconds(1400);
}

void loop() {
  if (Serial.available() > 0) {
    char command = Serial.read();

    switch (command) {
      case 'F': forward(); break;
      case 'B': back(); break;
      case 'L': left(); break;
      case 'R': right(); break;
      case 'U': up(); break;
      case 'D': down(); break;
      case 'S': stopAll(); break;
    }

    delay(2000);
    stopAll();
  }
}
