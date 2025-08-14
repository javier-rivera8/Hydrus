#include <Servo.h>

Servo thruster;
Servo thruster2;
int pinThruster = 4;
int pinThruster2 = 9;

void setup() {
  thruster.attach(pinThruster);
  thruster2.attach(pinThruster2);
  Serial.begin(9600);
  
  // Inicializamos en stop
  thruster.writeMicroseconds(1500);
  thruster2.writeMicroseconds(1500);
  Serial.println("Thruster en stop (1500 µs)");
  Serial.println("Comandos disponibles:");
  Serial.println("F - Encender thrusters al máximo");
  Serial.println("S - Parar thrusters");
  delay(3000);  // Tiempo para que el ESC se estabilize
}

void loop() {
  // Verificar si hay datos disponibles en el puerto serie
  if (Serial.available() > 0) {
    char command = Serial.read();
    
    // Convertir a mayúscula para mayor flexibilidad
    command = toupper(command);
    
    switch (command) {
      case 'F':
        // Encender al máximo
        thruster.writeMicroseconds(1600);
        thruster2.writeMicroseconds(1600);
        Serial.println("Thrusters encendidos al máximo (1600 µs)");
        break;
        
      case 'S':
        // Parar thrusters
        thruster.writeMicroseconds(1500);
        thruster2.writeMicroseconds(1500);
        Serial.println("Thrusters parados (1500 µs)");
        break;
        
      default:
        Serial.println("Comando no reconocido. Use 'F' para encender o 'S' para parar.");
        break;
    }
  }
}