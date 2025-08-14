#include <Servo.h>

Servo motor1, motor2, motor3, motor4, motor5, motor7, motor8;

int pinMotor1 = 9;
int pinMotor2 = 3;
int pinMotor3 = 4;
int pinMotor4 = 5;
int pinMotor5 = 6;
int pinMotor7 = 8;
int pinMotor8 = 2;

void moverMotor(int motorNum, int señal) {
  if (motorNum == 1) motor1.writeMicroseconds(señal);
  else if (motorNum == 2) motor2.writeMicroseconds(señal);
  else if (motorNum == 3) motor3.writeMicroseconds(señal);
  else if (motorNum == 4) motor4.writeMicroseconds(señal);
  else if (motorNum == 5) motor5.writeMicroseconds(señal);
  else if (motorNum == 7) motor7.writeMicroseconds(señal);
  else if (motorNum == 8) motor8.writeMicroseconds(señal);
}

void setup() {
  motor1.attach(pinMotor1);
  motor2.attach(pinMotor2);
  motor3.attach(pinMotor3);
  motor4.attach(pinMotor4);
  motor5.attach(pinMotor5);
  motor7.attach(pinMotor7);
  motor8.attach(pinMotor8);

  Serial.begin(9600);

  moverMotor(1, 1500);
  moverMotor(2, 1500);
  moverMotor(3, 1500);
  moverMotor(4, 1500);
  moverMotor(5, 1500);
  moverMotor(7, 1500);
  moverMotor(8, 1500);

  Serial.println("Todos los motores inicializados en stop");
  delay(2000);
}

void loop() {
  if (Serial.available() > 0) {
    String command = Serial.readStringUntil('\n');
    command.trim();

    int firstSpace = command.indexOf(' ');
    int secondSpace = command.indexOf(' ', firstSpace + 1);
    int thirdSpace = command.indexOf(' ', secondSpace + 1);

    if ((command.startsWith("forward") || command.startsWith("backward")) &&
        firstSpace > 0 && secondSpace > firstSpace && thirdSpace > secondSpace) {

      int motorA = command.substring(firstSpace + 1, secondSpace).toInt();
      int motorB = command.substring(secondSpace + 1, thirdSpace).toInt();
      int duration = command.substring(thirdSpace + 1).toInt();

      int señal = command.startsWith("forward") ? 1600 : 1400;

      Serial.println("Moviendo motores " + String(motorA) + " y " + String(motorB) +
                     (señal==1600 ? " forward " : " backward ") + String(duration) + " segundos");

      moverMotor(motorA, señal);
      moverMotor(motorB, señal);

      delay(duration * 1000);

      moverMotor(motorA, 1500);
      moverMotor(motorB, 1500);

      Serial.println("Motores detenidos");
    }

    // Comando stop <motor>
    else if (command.startsWith("stop")) {
      int motorNum = command.substring(5).toInt();
      moverMotor(motorNum, 1500);
      Serial.println("Motor " + String(motorNum) + " detenido manualmente");
    }
  }
}
