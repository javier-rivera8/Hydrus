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

    // Separar todos los "tokens" del comando
    int lastSpace = command.lastIndexOf(' ');
    if (lastSpace < 0) return;

    int duration = command.substring(lastSpace + 1).toInt(); 
    String motorsPWM = command.substring(0, lastSpace);      

    Serial.println("Comando recibido, duración: " + String(duration));

    // Procesar pares motor-pwm
    int start = 0;
    while (start < motorsPWM.length()) {
      int spaceIdx = motorsPWM.indexOf(' ', start);
      String motorStr, pwmStr;
      if (spaceIdx >= 0) {
        motorStr = motorsPWM.substring(start, spaceIdx);
        start = spaceIdx + 1;
      } else {
        motorStr = motorsPWM.substring(start);
        start = motorsPWM.length();
      }

      spaceIdx = motorsPWM.indexOf(' ', start);
      if (spaceIdx >= 0) {
        pwmStr = motorsPWM.substring(start, spaceIdx);
        start = spaceIdx + 1;
      } else {
        pwmStr = motorsPWM.substring(start);
        start = motorsPWM.length();
      }

      int motorNum = motorStr.toInt();
      int pwm = pwmStr.toInt();

      moverMotor(motorNum, pwm);
      Serial.println("Motor " + String(motorNum) + " -> PWM " + String(pwm));
    }

    delay(duration * 1000);

    // Detener todos los motores enviados
    start = 0;
    while (start < motorsPWM.length()) {
      int spaceIdx = motorsPWM.indexOf(' ', start);
      String motorStr;
      if (spaceIdx >= 0) {
        motorStr = motorsPWM.substring(start, spaceIdx);
        start = spaceIdx + 1;
      } else {
        motorStr = motorsPWM.substring(start);
        start = motorsPWM.length();
      }

      int motorNum = motorStr.toInt();
      moverMotor(motorNum, 1500);
    }

    Serial.println("Motores detenidos");
  }
}
