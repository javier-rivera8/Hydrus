#include <Servo.h>

Servo thruster; 
int thrusterPin = 9; 

void setup() {
  thruster.attach(thrusterPin);
  Serial.begin(9600);
  Serial.println("Prueba de thruster iniciada");
  
  thruster.writeMicroseconds(1500); 
  delay(2000);
}

void loop() {
  // Adelante
  Serial.println("Adelante");
  thruster.writeMicroseconds(1600);
  delay(2000);

  // Neutro
  Serial.println("Neutro");
  thruster.writeMicroseconds(1500);
  delay(2000);

  // Atrás
  Serial.println("Atras");
  thruster.writeMicroseconds(1400);
  delay(2000);

  // Neutro
  Serial.println("Neutro");
  thruster.writeMicroseconds(1500);
  delay(2000);
}
