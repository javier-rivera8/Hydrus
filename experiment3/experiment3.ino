#include <Servo.h>

Servo thruster1;
Servo thruster2;
Servo thruster3;
Servo thruster4;
Servo thruster5;
Servo thruster6;
Servo thruster7;
Servo thruster8;

int pinThruster1 =9;
int pinThruster2 =3;
int pinThruster3 =4;
int pinThruster4 =5;
int pinThruster5 =6;
int pinThruster6 =7;
int pinThruster7 =8;
int pinThruster8 =2;



void setup() {
  thruster1.attach(pinThruster1);
  thruster2.attach(pinThruster2);
  thruster3.attach(pinThruster3);
  thruster4.attach(pinThruster4);
  thruster5.attach(pinThruster5);
  thruster6.attach(pinThruster6);
  thruster7.attach(pinThruster7);
  thruster8.attach(pinThruster8);

  Serial.begin(9600);

  delay(2000); // Esperamos 2 segundos para estabilizar
  
  // Inicializamos en stop
  thruster1.writeMicroseconds(1500);
  thruster2.writeMicroseconds(1500);
  thruster3.writeMicroseconds(1500);
  thruster4.writeMicroseconds(1500);
  thruster5.writeMicroseconds(1500);
  thruster6.writeMicroseconds(1500);
  thruster7.writeMicroseconds(1500);
  thruster8.writeMicroseconds(1500);

  delay(3000); // Esperamos un segundo para estabilizar

  thruster7.writeMicroseconds(1600);
  thruster8.writeMicroseconds(1600);
  delay(3000); // Esperamos 5 para estabilizar
  thruster7.writeMicroseconds(1500);
  thruster8.writeMicroseconds(1500);

  thruster6.writeMicroseconds(1600);
  thruster5.writeMicroseconds(1600);
  delay(3000); // Esperamos 5 para estabilizar
  thruster6.writeMicroseconds(1500);
  thruster5.writeMicroseconds(1500);


}

void loop() {
  // Encender al máximo

  
  // Volver a stop
}
