#include <Servo.h>

// Number of thrusters (adjust as needed)
const int NUM_THRUSTERS = 8;

// Create servo objects for each thruster
Servo thrusters[NUM_THRUSTERS];

// Pin assignments for thrusters (adjust to your wiring)
const int THRUSTER_PINS[NUM_THRUSTERS] = {
  2,   // Thruster 1
  3,   // Thruster 2  
  4,   // Thruster 3
  5,   // Thruster 4
  6,   // Thruster 5
  7,   // Thruster 6
  8,   // Thruster 7
  9   // Thruster 8
};

// PWM limits for safety
const int PWM_MIN = 1100;
const int PWM_MAX = 1700;
const int PWM_NEUTRAL = 1500;

// Serial communication variables
String inputString = "";
boolean stringComplete = false;

void setup() {
  // Initialize serial communication
  Serial.begin(9600);
  
  // Attach all thrusters to their pins
  for (int i = 0; i < NUM_THRUSTERS; i++) {
    thrusters[i].attach(THRUSTER_PINS[i]);
    thrusters[i].writeMicroseconds(PWM_NEUTRAL); // Start at neutral
  }
  
  // Reserve memory for input string
  inputString.reserve(200);
  
  // Initialize all thrusters to neutral position
  delay(2000);
  Serial.println("Hydrus Thruster Controller Ready");
  Serial.println("Format: T<thruster_number>:<pwm_value>");
  Serial.println("Example: T1:1600");
}

void loop() {
  // Check for complete serial command
  if (stringComplete) {
    processCommand(inputString);
    // Clear the string for next command
    inputString = "";
    stringComplete = false;
  }
}

void processCommand(String command) {
  command.trim(); // Remove whitespace
  
  // Check if command starts with 'T'
  if (command.charAt(0) != 'T') {
    Serial.println("ERROR: Command must start with 'T'");
    return;
  }
  
  // Find the colon separator
  int colonIndex = command.indexOf(':');
  if (colonIndex == -1) {
    Serial.println("ERROR: Missing ':' separator");
    return;
  }
  
  // Extract thruster number and PWM value
  String thrusterStr = command.substring(1, colonIndex);
  String pwmStr = command.substring(colonIndex + 1);
  
  int thrusterNum = thrusterStr.toInt();
  int pwmValue = pwmStr.toInt();
  
  // Validate thruster number (1-based from Python, 0-based internally)
  if (thrusterNum < 1 || thrusterNum > NUM_THRUSTERS) {
    Serial.print("ERROR: Invalid thruster number. Must be 1-");
    Serial.println(NUM_THRUSTERS);
    return;
  }
  
  // Validate PWM value
  if (pwmValue < PWM_MIN || pwmValue > PWM_MAX) {
    Serial.print("ERROR: PWM value out of range. Must be ");
    Serial.print(PWM_MIN);
    Serial.print("-");
    Serial.println(PWM_MAX);
    return;
  }
  
  // Convert to 0-based index
  int thrusterIndex = thrusterNum - 1;
  
  // Set thruster PWM
  thrusters[thrusterIndex].writeMicroseconds(pwmValue);
  
  // Send confirmation
  Serial.print("OK: T");
  Serial.print(thrusterNum);
  Serial.print(":");
  Serial.println(pwmValue);
}

// Serial event handler - called when data is available
void serialEvent() {
  while (Serial.available()) {
    char inChar = (char)Serial.read();
    
    if (inChar == '\n') {
      stringComplete = true;
    } else {
      inputString += inChar;
    }
  }
}

// Emergency stop function
void emergencyStop() {
  for (int i = 0; i < NUM_THRUSTERS; i++) {
    thrusters[i].writeMicroseconds(PWM_NEUTRAL);
  }
  Serial.println("EMERGENCY STOP: All thrusters set to neutral");
}