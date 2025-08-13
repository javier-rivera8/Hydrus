#include <Servo.h>

Servo thruster;
Servo thruster2;
int pinThruster =4;
int pinThruster2 =9;

void setup() {
  thruster.attach(pinThruster);
  thruster2.attach(pinThruster2);
  Serial.begin(9600);
  
  // Inicializamos en stop
  thruster.writeMicroseconds(1500);
  thruster2.writeMicroseconds(1500);
  Serial.println("Thruster en stop (1500 µs)");
  delay(3000);  // Tiempo para que el ESC se estabilice


  thruster.writeMicroseconds(1600);
  thruster2.writeMicroseconds(1600);
  Serial.println("Thruster a velocidad máxima (1600 µs)");
  delay(1000);  // Mantener 3 segundos
  thruster.writeMicroseconds(1500);
  thruster2.writeMicroseconds(1500);
}

void loop() {
  // Encender al máximo

  
  // Volver a stop
}
