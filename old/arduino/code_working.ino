#include <Servo.h>

Servo thruster;
Servo thruster2;
int pinThruster =3;
int pinThruster2 =4;

void setup() {
  thruster.attach(pinThruster);
  thruster2.attach(pinThruster2);
  Serial.begin(9600);
  
  // Inicializamos en stop
  thruster.writeMicroseconds(1500);
  thruster2.writeMicroseconds(1500);
  Serial.println("Thruster en stop (1500 µs)");
  delay(3000);  // Tiempo para que el ESC se estabilice


}

void loop() {
  // Encender al máximo


  thruster.writeMicroseconds(1600);
  delay(3000);  // Esperar 1 segundo para estabilizar
  thruster.writeMicroseconds(1500);

  thruster2.writeMicroseconds(1600);
  delay(3000);  // Esperar 1 segundo para estabilizar

  thruster.writeMicroseconds(1500);
  thruster2.writeMicroseconds(1500);
  
  // Volver a stop
}
