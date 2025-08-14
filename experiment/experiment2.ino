#include <Servo.h>

// Declaración de motores
Servo motor1, motor2, motor3, motor4, motor5, motor7, motor8;

// Pines de cada motor
int pinMotor1 = 9;
int pinMotor2 = 3;
int pinMotor3 = 4;
int pinMotor4 = 5;
int pinMotor5 = 6;
int pinMotor7 = 8;
int pinMotor8 = 2;

void setup() {
  motor1.attach(pinMotor1);
  motor2.attach(pinMotor2);
  motor3.attach(pinMotor3);
  motor4.attach(pinMotor4);
  motor5.attach(pinMotor5);
  motor7.attach(pinMotor7);
  motor8.attach(pinMotor8);

  Serial.begin(9600);

  // Inicializamos todos en stop
  motor1.writeMicroseconds(1500);
  motor2.writeMicroseconds(1500);
  motor3.writeMicroseconds(1500);
  motor4.writeMicroseconds(1500);
  motor5.writeMicroseconds(1500);
  motor7.writeMicroseconds(1500);
  motor8.writeMicroseconds(1500);

  Serial.println("Todos los motores inicializados en stop");
  delay(2000);
}

void loop() {
  if (Serial.available() > 0) {
    String command = Serial.readStringUntil('\n');
    command.trim();

    int firstSpace = command.indexOf(' ');
    int secondSpace = command.indexOf(' ', firstSpace + 1);

    if (command.startsWith("forward") && firstSpace > 0 && secondSpace > firstSpace) {
      int motorNum = command.substring(firstSpace + 1, secondSpace).toInt();
      int duration = command.substring(secondSpace + 1).toInt();

      if (duration > 0) {
        Serial.println("Motor " + String(motorNum) + " forward por " + String(duration) + " segundos");

        if (motorNum == 1) motor1.writeMicroseconds(1600);
        else if (motorNum == 2) motor2.writeMicroseconds(1600);
        else if (motorNum == 3) motor3.writeMicroseconds(1600);
        else if (motorNum == 4) motor4.writeMicroseconds(1600);
        else if (motorNum == 5) motor5.writeMicroseconds(1600);
        else if (motorNum == 7) motor7.writeMicroseconds(1600);
        else if (motorNum == 8) motor8.writeMicroseconds(1600);

        delay(duration * 1000);

        if (motorNum == 1) motor1.writeMicroseconds(1500);
        else if (motorNum == 2) motor2.writeMicroseconds(1500);
        else if (motorNum == 3) motor3.writeMicroseconds(1500);
        else if (motorNum == 4) motor4.writeMicroseconds(1500);
        else if (motorNum == 5) motor5.writeMicroseconds(1500);
        else if (motorNum == 7) motor7.writeMicroseconds(1500);
        else if (motorNum == 8) motor8.writeMicroseconds(1500);

        Serial.println("Motor " + String(motorNum) + " detenido");
      }
    }

    // Comando: backward <motor> <duración>
    else if (command.startsWith("backward") && firstSpace > 0 && secondSpace > firstSpace) {
      int motorNum = command.substring(firstSpace + 1, secondSpace).toInt();
      int duration = command.substring(secondSpace + 1).toInt();

      if (duration > 0) {
        Serial.println("Motor " + String(motorNum) + " backward por " + String(duration) + " segundos");

        if (motorNum == 1) motor1.writeMicroseconds(1400);
        else if (motorNum == 2) motor2.writeMicroseconds(1400);
        else if (motorNum == 3) motor3.writeMicroseconds(1400);
        else if (motorNum == 4) motor4.writeMicroseconds(1400);
        else if (motorNum == 5) motor5.writeMicroseconds(1400);
        else if (motorNum == 7) motor7.writeMicroseconds(1400);
        else if (motorNum == 8) motor8.writeMicroseconds(1400);

        delay(duration * 1000);

        if (motorNum == 1) motor1.writeMicroseconds(1500);
        else if (motorNum == 2) motor2.writeMicroseconds(1500);
        else if (motorNum == 3) motor3.writeMicroseconds(1500);
        else if (motorNum == 4) motor4.writeMicroseconds(1500);
        else if (motorNum == 5) motor5.writeMicroseconds(1500);
        else if (motorNum == 7) motor7.writeMicroseconds(1500);
        else if (motorNum == 8) motor8.writeMicroseconds(1500);

        Serial.println("Motor " + String(motorNum) + " detenido");
      }
    }

    // Comando: stop <motor>
    else if (command.startsWith("stop")) {
      int motorNum = command.substring(5).toInt();

      if (motorNum == 1) motor1.writeMicroseconds(1500);
      else if (motorNum == 2) motor2.writeMicroseconds(1500);
      else if (motorNum == 3) motor3.writeMicroseconds(1500);
      else if (motorNum == 4) motor4.writeMicroseconds(1500);
      else if (motorNum == 5) motor5.writeMicroseconds(1500);
      else if (motorNum == 7) motor7.writeMicroseconds(1500);
      else if (motorNum == 8) motor8.writeMicroseconds(1500);

      Serial.println("Motor " + String(motorNum) + " detenido manualmente");
    }
  }
}
