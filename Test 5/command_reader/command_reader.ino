#include <Servo.h>

Servo thruster;
Servo thruster2;

int pinThruster = 8;
int pinThruster2 = 2;

void setup() {
  Serial.begin(9600);

  thruster.attach(pinThruster);
  thruster2.attach(pinThruster2);

  thruster.writeMicroseconds(1500);
  thruster2.writeMicroseconds(1500);
  delay(3000); // Tiempo para armar ESC

  Serial.println("Arduino listo para recibir comandos");
}

void loop() {
  if (Serial.available() > 0) {
    char command = Serial.read();

    switch (command) {
      case 'F': // Adelante
        thruster.writeMicroseconds(1600);
        thruster2.writeMicroseconds(1600);
        break;

      case 'B': // Atrás
        thruster.writeMicroseconds(1400);
        thruster2.writeMicroseconds(1400);
        break;

      case 'S': // Stop
        thruster.writeMicroseconds(1500);
        thruster2.writeMicroseconds(1500);
        break;

      case 'L': // Solo izquierda
        thruster.writeMicroseconds(1600);
        thruster2.writeMicroseconds(1500);
        break;

      case 'R': // Solo derecha
        thruster.writeMicroseconds(1500);
        thruster2.writeMicroseconds(1600);
        break;
    }

	delay(2000);
	thruster.writeMicroseconds(1500);
	thruster2.writeMicroseconds(1500); 

 }
}
