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

bool stopFlag = false;

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

void front(){
    thruster7.writeMicroseconds(1600);
    thruster8.writeMicroseconds(1600);
}

void back(){
    thruster7.writeMicroseconds(1400);
    thruster8.writeMicroseconds(1400);
}

void left(){
    thruster1.writeMicroseconds(1600);
    thruster7.writeMicroseconds(1600);
}

void right(){
    thruster2.writeMicroseconds(1600);
    thruster8.writeMicroseconds(1600);
}

void down(){
    thruster3.writeMicroseconds(1400);
    thruster6.writeMicroseconds(1400);
}

void up(){
    thruster3.writeMicroseconds(1600);
    thruster6.writeMicroseconds(1600);
}

void stop(){
    thruster1.writeMicroseconds(1500);
    thruster2.writeMicroseconds(1500);
    thruster3.writeMicroseconds(1500);
    thruster4.writeMicroseconds(1500);
    thruster5.writeMicroseconds(1500);
    thruster6.writeMicroseconds(1500);
    thruster7.writeMicroseconds(1500);
    thruster8.writeMicroseconds(1500);

    Serial.println("Thrusters stopped.");
    delay(2000);  // Wait for 2 seconds
}


void loop() {
    if (stopFlag) {
        while (true) {
            Serial.println("Thrusters are stopped. Press any key to start again.");
        }
    }

    delay(10000);  // Wait for 10 seconds before starting the sequence

    Serial.println("Going down for 5 seconds...");
    down();
    delay(5000);  // Wait for 5 seconds to stabilize

    stop();

    Serial.println("Going left for 10 seconds...");
    left();
    delay(10000);  // Wait for 10 seconds to stabilize

    stop();

    Serial.println("Going front for 20 seconds...");
    front();
    delay(20000);  // Wait for 20 seconds to stabilize

    stop();

    stopFlag = true;  // Set the stop flag to true
    Serial.println("Thrusters stopped.");


}