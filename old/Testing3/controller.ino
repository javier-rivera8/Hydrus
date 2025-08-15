#include <Servo.h>

// Objetos Servo para cada motor
Servo motor1;
Servo motor2;
Servo motor3;
Servo motor4;
Servo motor5;
Servo motor6;
Servo motor7;
Servo motor8;

// Límites
const int MIN_US = 1000;
const int MAX_US = 2000;
const int NEUTRAL_US = 1500;

// Pines
const int pin1 = 2;
const int pin2 = 3;
const int pin3 = 4;
const int pin4 = 5;
const int pin5 = 6;
const int pin6 = 7;
const int pin7 = 8;
const int pin8 = 9;

// Función para mover un motor específico
void setMotor(int motor, int us) {
  if (us < MIN_US || us > MAX_US) {
    Serial.println("ERR us fuera de rango");
    return;
  }

  if (motor == 1) motor1.writeMicroseconds(us);
  else if (motor == 2) motor2.writeMicroseconds(us);
  else if (motor == 3) motor3.writeMicroseconds(us);
  else if (motor == 4) motor4.writeMicroseconds(us);
  else if (motor == 5) motor5.writeMicroseconds(us);
  else if (motor == 6) motor6.writeMicroseconds(us);
  else if (motor == 7) motor7.writeMicroseconds(us);
  else if (motor == 8) motor8.writeMicroseconds(us);
  else {
    Serial.println("ERR motor fuera de rango");
    return;
  }

  Serial.print("Motor ");
  Serial.print(motor);
  Serial.print(" -> ");
  Serial.println(us);
}

// Procesar comando recibido
void procesarLinea(const String &input) {
  String line = input;
  line.trim();
  if (line.length() == 0) return;

  char buf[80];
  line.toCharArray(buf, sizeof(buf));

  char *tok = strtok(buf, " \t");
  if (!tok) return;

  // -------- Comando forward --------
  if (strcmp(tok, "forward") == 0) {
    int m1 = atoi(strtok(NULL, " \t"));
    int p1 = atoi(strtok(NULL, " \t"));
    int m2 = atoi(strtok(NULL, " \t"));
    int p2 = atoi(strtok(NULL, " \t"));
    int tiempo = atoi(strtok(NULL, " \t"));

    if (m1 < 1 || m1 > 8 || m2 < 1 || m2 > 8) {
      Serial.println("ERR motor fuera de rango");
      return;
    }
    if (p1 < MIN_US || p1 > MAX_US || p2 < MIN_US || p2 > MAX_US) {
      Serial.println("ERR us fuera de rango");
      return;
    }
    if (tiempo <= 0) {
      Serial.println("ERR tiempo invalido");
      return;
    }

    setMotor(m1, p1);
    setMotor(m2, p2);
    delay(tiempo);
    setMotor(m1, NEUTRAL_US);
    setMotor(m2, NEUTRAL_US);

    Serial.println("OK");
    return;
  }

  // -------- Comando motor --------
  if (strcmp(tok, "motor") == 0) {
    int m = atoi(strtok(NULL, " \t"));
    int p = atoi(strtok(NULL, " \t"));

    if (m < 1 || m > 8) {
      Serial.println("ERR motor fuera de rango");
      return;
    }
    if (p < MIN_US || p > MAX_US) {
      Serial.println("ERR us fuera de rango");
      return;
    }

    setMotor(m, p);
    Serial.println("OK");
    return;
  }

  Serial.println("ERR comando desconocido");
}

void setup() {
  Serial.begin(115200);
  Serial.setTimeout(5);

  motor1.attach(pin1);
  motor2.attach(pin2);
  motor3.attach(pin3);
  motor4.attach(pin4);
  motor5.attach(pin5);
  motor6.attach(pin6);
  motor7.attach(pin7);
  motor8.attach(pin8);

  setMotor(1, NEUTRAL_US);
  setMotor(2, NEUTRAL_US);
  setMotor(3, NEUTRAL_US);
  setMotor(4, NEUTRAL_US);
  setMotor(5, NEUTRAL_US);
  setMotor(6, NEUTRAL_US);
  setMotor(7, NEUTRAL_US);
  setMotor(8, NEUTRAL_US);

  Serial.println("READY");
}

void loop() {
  if (Serial.available()) {
    String line = Serial.readStringUntil('\n');
    procesarLinea(line);
  }
}
