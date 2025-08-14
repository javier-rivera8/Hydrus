#include <Servo.h>

Servo thruster;
Servo thruster2;
int pinThruster = 3;
int pinThruster2 = 4;

void setup() {
  thruster.attach(pinThruster);
  thruster2.attach(pinThruster2);
  Serial.begin(9600);
  
  // Inicializamos en stop
  thruster.writeMicroseconds(1500);
  thruster2.writeMicroseconds(1500);
  Serial.println("Thrusters inicializados en stop");
  delay(2000);  // Tiempo para que el ESC se estabilice
}

void loop() {
  if (Serial.available() > 0) {
    String command = Serial.readStringUntil('\n');
    command.trim();
    
    if (command.startsWith("forward")) {
      int spaceIndex = command.indexOf(' ');
      if (spaceIndex > 0) {
        int duration = command.substring(spaceIndex + 1).toInt();
        if (duration > 0) {
          Serial.println("Thrusters forward - " + String(duration) + " segundos");
          
          // Encender thrusters
          thruster.writeMicroseconds(1600);
          thruster2.writeMicroseconds(1600);
          
          delay(duration * 1000);  // Esperar la duración especificada
          
          // Parar thrusters
          thruster.writeMicroseconds(1500);
          thruster2.writeMicroseconds(1500);
          
          Serial.println("Thrusters detenidos");
        }
      }
    }
    else if (command == "stop") {
      thruster.writeMicroseconds(1500);
      thruster2.writeMicroseconds(1500);
      Serial.println("Thrusters detenidos manualmente");
    }
  }
}