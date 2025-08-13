//  |Motor| Pin | Type | Direction | Function |
//  |----|-----|------|-----------|----------|
//  | T1 | 1 |  Forward | Movement/Rotation |
//  | T2 | 2 |  Forward | Movement/Rotation |
//  | T3 | 3 |  Forward | Movement/Rotation |
//  | T4 | 4 |  Backward | Movement/Rotation |
//  | T5 | 5 |  Backward | Depth Control |
//  | T6 | 6 |  Backward | Depth Control |
//  | T7 | 7 |  Backward | Torpedo System |
//  | T8 | 8 |  Forward | Torpedo System |
//  | T9 | 9 |  Forward | Camera Pan/Tilt | NOT NEEDED RIGHT NOW


#include <Servo.h>

#define PWM_NEUTRAL 1500
#define PWM_FORWARD 1600
#define PWM_REVERSE 1400

Servo thrusters[9];

void setup() {
  Serial.begin(115200);
  Serial.println("=== TESTING ===");

  thrusters[0].attach(1);
  thrusters[1].attach(2);
  thrusters[2].attach(3);
  thrusters[3].attach(4); //Torpedo
  thrusters[4].attach(5);
  thrusters[5].attach(6);
  thrusters[6].attach(7); //Torpedo
  thrusters[7].attach(8);
  thrusters[8].attach(9); 

  allNeutral();
  Serial.println("Initializing ESCs...");
  delay(3000);
  Serial.println("Initialization completed \n");
}

void loop() {
  forward(5000);
  turnRight(1000);
  stop(2000);
  dive(3000);
  stop(1000);
  rise(3000);
  stop(2000);
  turnLeft(2000);
  stop(2000);
}


// movemet functio
void forward(int duration) {
  announce("FORWARD", duration);
  thrusters[0].writeMicroseconds(PWM_FORWARD);
  thrusters[1].writeMicroseconds(PWM_FORWARD);
  thrusters[2].writeMicroseconds(PWM_FORWARD);
  thrusters[7].writeMicroseconds(PWM_FORWARD);

  thrusters[3].writeMicroseconds(PWM_REVERSE);
  thrusters[4].writeMicroseconds(PWM_REVERSE);
  thrusters[5].writeMicroseconds(PWM_REVERSE);
  thrusters[6].writeMicroseconds(PWM_REVERSE);

  progress(duration);
}

void reverse(int duration) {
  announce("REVERSE", duration);
  thrusters[0].writeMicroseconds(PWM_REVERSE);
  thrusters[1].writeMicroseconds(PWM_REVERSE);
  thrusters[2].writeMicroseconds(PWM_REVERSE);
  thrusters[7].writeMicroseconds(PWM_REVERSE);

  thrusters[3].writeMicroseconds(PWM_FORWARD);
  thrusters[4].writeMicroseconds(PWM_FORWARD);
  thrusters[5].writeMicroseconds(PWM_FORWARD);
  thrusters[6].writeMicroseconds(PWM_FORWARD);

  progress(duration);
}

void dive(int duration) {
  announce("DIVE", duration);
  thrusters[4].writeMicroseconds(PWM_FORWARD); // T5
  thrusters[5].writeMicroseconds(PWM_FORWARD); // T6
  progress(duration);
}

void rise(int duration) {
  announce("RISE", duration);
  thrusters[4].writeMicroseconds(PWM_REVERSE); // T5
  thrusters[5].writeMicroseconds(PWM_REVERSE); // T6
  progress(duration);
}

void turnLeft(int duration) {
  announce("TURN LEFT", duration);
  thrusters[0].writeMicroseconds(PWM_REVERSE); // T1
  thrusters[1].writeMicroseconds(PWM_FORWARD); // T2
  thrusters[2].writeMicroseconds(PWM_REVERSE); // T3
  thrusters[7].writeMicroseconds(PWM_FORWARD); // T8
  progress(duration);
}

void turnRight(int duration) {
  announce("TURN RIGHT", duration);
  thrusters[0].writeMicroseconds(PWM_FORWARD); // T1
  thrusters[1].writeMicroseconds(PWM_REVERSE); // T2
  thrusters[2].writeMicroseconds(PWM_FORWARD); // T3
  thrusters[7].writeMicroseconds(PWM_REVERSE); // T8
  progress(duration);
}

void stop(int duration) {
  announce("STOP", duration);
  allNeutral();
  progress(duration);
}

void allNeutral() {
  for (int i = 0; i < 9; i++) {
    thrusters[i].writeMicroseconds(PWM_NEUTRAL);
  }
}

void announce(const char* action, int ms) {
  Serial.print("[ACTION] ");
  Serial.print(action);
  Serial.print(" for ");
  Serial.print(ms / 1000.0, 1);
  Serial.println(" sec");
}

void progress(int ms) { //just to simulate a progres bar
  int steps = ms / 200; 
  for (int i = 0; i < steps; i++) {
    Serial.print(".");
    delay(200);
  }
  Serial.println();
}

void testThruster(int i) {
  int duration = 5000;

  Serial.print("Testing Thruster ");
  Serial.println(i + 1);  

  thrusters[i].writeMicroseconds(PWM_FORWARD);
  delay(duration);

  thrusters[i].writeMicroseconds(PWM_NEUTRAL);
  delay(duration);

  thrusters[i].writeMicroseconds(PWM_REVERSE);
  delay(duration);

  thrusters[i].writeMicroseconds(PWM_NEUTRAL);
  delay(1000); 
} 