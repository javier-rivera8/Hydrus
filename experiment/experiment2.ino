#include <Servo.h>

#define NUM_THRUSTERS 8

Servo thrusters[NUM_THRUSTERS];
int thrusterPins[NUM_THRUSTERS] = {2, 3, 4, 5, 6, 7, 8, 9};
int stopValue = 1500;  

void setup() {
  Serial.begin(9600);

  // Inicializar todos los thrusters
  for (int i = 0; i < NUM_THRUSTERS; i++) {
    thrusters[i].attach(thrusterPins[i]);
    thrusters[i].writeMicroseconds(stopValue);
  }

  Serial.println("Todos los thrusters inicializados en stop");
  delay(2000);
}

void loop() {
  if (Serial.available() > 0) {
    String command = Serial.readStringUntil('\n');
    command.trim();

    if (command.startsWith("forward")) {
      // forward <thruster/all> <valor> <segundos>
      int firstSpace = command.indexOf(' ');
      int secondSpace = command.indexOf(' ', firstSpace + 1);
      int thirdSpace = command.indexOf(' ', secondSpace + 1);

      if (firstSpace > 0 && secondSpace > 0 && thirdSpace > 0) {
        String target = command.substring(firstSpace + 1, secondSpace);
        int value = command.substring(secondSpace + 1, thirdSpace).toInt();
        int duration = command.substring(thirdSpace + 1).toInt();

        if (target == "all") {
          for (int i = 0; i < NUM_THRUSTERS; i++) {
            thrusters[i].writeMicroseconds(value);
          }
        } else {
          int thrusterNum = target.toInt() - 1; 
          if (thrusterNum >= 0 && thrusterNum < NUM_THRUSTERS) {
            thrusters[thrusterNum].writeMicroseconds(value);
          } else {
            Serial.println("Thruster inválido");
            return;
          }
        }

        Serial.println("Moviendo " + target + " a " + String(value) + " por " + String(duration) + " segundos");
        delay(duration * 1000);

        // Parar después
        if (target == "all") {
          for (int i = 0; i < NUM_THRUSTERS; i++) {
            thrusters[i].writeMicroseconds(stopValue);
          }
        } else {
          thrusters[target.toInt() - 1].writeMicroseconds(stopValue);
        }

        Serial.println("Movimiento completado, thrusters detenidos");
      }
    }
    else if (command.startsWith("stop")) {
      // stop <thruster/all>
      int spaceIndex = command.indexOf(' ');
      if (spaceIndex > 0) {
        String target = command.substring(spaceIndex + 1);
        if (target == "all") {
          for (int i = 0; i < NUM_THRUSTERS; i++) {
            thrusters[i].writeMicroseconds(stopValue);
          }
        } else {
          int thrusterNum = target.toInt() - 1;
          if (thrusterNum >= 0 && thrusterNum < NUM_THRUSTERS) {
            thrusters[thrusterNum].writeMicroseconds(stopValue);
          } else {
            Serial.println("Thruster inválido");
            return;
          }
        }
        Serial.println("Thruster(s) detenidos");
      }
    }
  }
}


//comando pa mandar comands
//arduino-cli monitor -p /dev/ttyACM0 -c baud=9600

