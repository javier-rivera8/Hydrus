#include <Servo.h>

Servo motor1, motor2, motor3, motor4, motor5, motor7, motor8;

int pinMotor1 = 9;
int pinMotor2 = 3;
int pinMotor3 = 4;
int pinMotor4 = 5;
int pinMotor5 = 6;
int pinMotor7 = 8;
int pinMotor8 = 2;

Servo* getMotor(int motorNum) {
  switch (motorNum) {
    case 1: return &motor1;
    case 2: return &motor2;
    case 3: return &motor3;
    case 4: return &motor4;
    case 5: return &motor5;
    case 7: return &motor7;
    case 8: return &motor8;
    default: return nullptr;
  }
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

  // Inicializamos todos en stop
  motor1.writeMicroseconds(1500);
  motor2.writeMicroseconds(1500);
  motor3.writeMicroseconds(1500);
  motor4.writeMicroseconds(1500);
  motor5.writeMicroseconds(1500);
  motor7.writeMicroseconds(1500);
  motor8.writeMicroseconds(1500);

  Serial.println("Todos los thrusters inicializados");
  delay(2000);
}

void loop() {
  if (Serial.available() > 0) {
    String command = Serial.readStringUntil('\n');
    command.trim();

    if (command.startsWith("forward")) {
      // Eliminamos "forward " y dividimos el resto
      command = command.substring(7);
      int spaceIndex = 0;
      int motorNum, duration;
      
      while (command.length() > 0) {
        spaceIndex = command.indexOf(' ');
        if (spaceIndex == -1) break;

        motorNum = command.substring(0, spaceIndex).toInt();
        command = command.substring(spaceIndex + 1);

        spaceIndex = command.indexOf(' ');
        if (spaceIndex == -1) {
          duration = command.toInt();
          command = "";
        } else {
          duration = command.substring(0, spaceIndex).toInt();
          command = command.substring(spaceIndex + 1);
        }

        Servo* selectedMotor = getMotor(motorNum);
        if (selectedMotor != nullptr && duration > 0) {
          Serial.println("Motor " + String(motorNum) + " forward por " + String(duration) + " segundos");
          selectedMotor->writeMicroseconds(1600);
          delay(duration * 1000);
          selectedMotor->writeMicroseconds(1500);
          Serial.println("Motor " + String(motorNum) + " detenido");
        }
      }
    }

    // Comando: stop <motor>
    else if (command.startsWith("stop")) {
      int motorNum = command.substring(5).toInt();
      Servo* selectedMotor = getMotor(motorNum);
      if (selectedMotor != nullptr) {
        selectedMotor->writeMicroseconds(1500);
        Serial.println("Motor " + String(motorNum) + " detenido manualmente");
      }
    }
  }
}

