#include <Servo.h>

Servo thruster1;
Servo thruster2;
Servo thruster3;
Servo thruster4;
Servo thruster5;
Servo thruster6;
Servo thruster7;
Servo thruster8;

int pinThruster1 = 9;
int pinThruster2 = 3;
int pinThruster3 = 4;
int pinThruster4 = 5;
int pinThruster5 = 6;
int pinThruster6 = 7;
int pinThruster7 = 8;
int pinThruster8 = 2;

void setup() {
  Serial.begin(9600);
  
  // Initialize all thrusters
  thruster1.attach(pinThruster1);
  thruster2.attach(pinThruster2);
  thruster3.attach(pinThruster3);
  thruster4.attach(pinThruster4);
  thruster5.attach(pinThruster5);
  thruster6.attach(pinThruster6);
  thruster7.attach(pinThruster7);
  thruster8.attach(pinThruster8);
  
  // Set all to neutral position
  thruster1.writeMicroseconds(1500);
  thruster2.writeMicroseconds(1500);
  thruster3.writeMicroseconds(1500);
  thruster4.writeMicroseconds(1500);
  thruster5.writeMicroseconds(1500);
  thruster6.writeMicroseconds(1500);
  thruster7.writeMicroseconds(1500);
  thruster8.writeMicroseconds(1500);
  
  delay(2000); // Wait for ESCs to initialize
  Serial.println("Thruster controller ready");
}

void loop() {
  if (Serial.available() > 0) {
    String command = Serial.readStringUntil('\n');
    command.trim();
    
    if (command.length() > 0) {
      processCommand(command);
    }
  }
}

void setThrusterSpeed(int motorNum, int speed) {
  switch(motorNum) {
    case 1: thruster1.writeMicroseconds(speed); break;
    case 2: thruster2.writeMicroseconds(speed); break;
    case 3: thruster3.writeMicroseconds(speed); break;
    case 4: thruster4.writeMicroseconds(speed); break;
    case 5: thruster5.writeMicroseconds(speed); break;
    case 6: thruster6.writeMicroseconds(speed); break;
    case 7: thruster7.writeMicroseconds(speed); break;
    case 8: thruster8.writeMicroseconds(speed); break;
  }
}

void processCommand(String command) {
  // Expected format: "motorNumber,speed" or "motorNumber,speed,duration"
  int firstComma = command.indexOf(',');
  
  if (firstComma > 0) {
    int motorNum = command.substring(0, firstComma).toInt();
    
    int secondComma = command.indexOf(',', firstComma + 1);
    int speed;
    unsigned long duration = 0;
    
    if (secondComma > 0) {
      // Format: motorNumber,speed,duration
      speed = command.substring(firstComma + 1, secondComma).toInt();
      duration = command.substring(secondComma + 1).toInt() * 1000; // Convert to milliseconds
    } else {
      // Format: motorNumber,speed
      speed = command.substring(firstComma + 1).toInt();
    }
    
    if (motorNum >= 1 && motorNum <= 8) {
      if (speed >= 1000 && speed <= 2000) {
        setThrusterSpeed(motorNum, speed);
        Serial.print("Motor ");
        Serial.print(motorNum);
        Serial.print(" set to ");
        Serial.print(speed);
        
        if (duration > 0) {
          Serial.print(" for ");
          Serial.print(duration / 1000);
          Serial.println(" seconds");
          
          delay(duration);
          
          setThrusterSpeed(motorNum, 1500); // Return to neutral
          Serial.print("Motor ");
          Serial.print(motorNum);
          Serial.println(" returned to neutral");
        } else {
          Serial.println();
        }
      } else {
        Serial.println("Speed must be between 1000-2000");
      }
    } else {
      Serial.println("Motor number must be 1-8");
    }
  } else {
    Serial.println("Invalid command format");
  }
}