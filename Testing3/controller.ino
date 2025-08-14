#include <Servo.h>

Servo motor1;
Servo motor2;
Servo motor3;
Servo motor4;
Servo motor5;
Servo motor6;
Servo motor7;
Servo motor8;

const int MIN_US = 1000;
const int MAX_US = 2000;
const int NEUTRAL_US = 1500;

const int pin1 = 2;
const int pin2 = 3;
const int pin3 = 4;
const int pin4 = 5;
const int pin5 = 6;
const int pin6 = 7;
const int pin7 = 8;
const int pin8 = 9;

void setMotorUS(int motor, int us) {
  us = constrain(us, MIN_US, MAX_US);

  switch (motor) {
    case 1: motor1.writeMicroseconds(us); break;
    case 2: motor2.writeMicroseconds(us); break;
    case 3: motor3.writeMicroseconds(us); break;
    case 4: motor4.writeMicroseconds(us); break;
    case 5: motor5.writeMicroseconds(us); break;
    case 6: motor6.writeMicroseconds(us); break;
    case 7: motor7.writeMicroseconds(us); break;
    case 8: motor8.writeMicroseconds(us); break;
    default:
      Serial.println("ERR motor fuera de rango");
      return;
  }

  Serial.print("Motor ");
  Serial.print(motor);
  Serial.print(" set to ");
  Serial.println(us);
}

void procesarLinea(const String &input) {
  String line = input;
  line.trim();
  if (line.length() == 0) return;

  char buf[160];
  if (line.length() >= (int)sizeof(buf)) {
    Serial.println("ERR linea demasiado larga");
    return;
  }
  line.toCharArray(buf, sizeof(buf));

  char *tok = strtok(buf, " \t");
  if (!tok) return;

  // --------- Nuevo comando "forward" ----------
  if (strcmp(tok, "forward") == 0) {
    // Leer primer motor
    tok = strtok(NULL, " \t");
    if (!tok) { Serial.println("ERR falta motor 1"); return; }
    int motor1_id = atoi(tok);

    tok = strtok(NULL, " \t");
    if (!tok) { Serial.println("ERR falta PWM motor 1"); return; }
    int pwm1 = atoi(tok);

    // Leer segundo motor
    tok = strtok(NULL, " \t");
    if (!tok) { Serial.println("ERR falta motor 2"); return; }
    int motor2_id = atoi(tok);

    tok = strtok(NULL, " \t");
    if (!tok) { Serial.println("ERR falta PWM motor 2"); return; }
    int pwm2 = atoi(tok);

    // Leer tiempo
    tok = strtok(NULL, " \t");
    if (!tok) { Serial.println("ERR falta tiempo"); return; }
    int tiempo = atoi(tok);

    // Validaciones
    if (motor1_id < 1 || motor1_id > 8 || motor2_id < 1 || motor2_id > 8) {
      Serial.println("ERR motor fuera de rango");
      return;
    }
    if (pwm1 < MIN_US || pwm1 > MAX_US || pwm2 < MIN_US || pwm2 > MAX_US) {
      Serial.println("ERR us fuera de rango");
      return;
    }
    if (tiempo <= 0) {
      Serial.println("ERR tiempo inválido");
      return;
    }

    // Ejecutar
    setMotorUS(motor1_id, pwm1);
    setMotorUS(motor2_id, pwm2);
    delay(tiempo);
    setMotorUS(motor1_id, NEUTRAL_US);
    setMotorUS(motor2_id, NEUTRAL_US);

    Serial.println("OK");
    return;
  }

  // --------- Comando original "motor" ----------
  if (strcmp(tok, "motor") == 0) {
    tok = strtok(NULL, " \t");
    if (!tok) { Serial.println("ERR falta ID de motor"); return; }
    int motor = atoi(tok);

    tok = strtok(NULL, " \t");
    if (!tok) { Serial.println("ERR falta valor PWM"); return; }
    int us = atoi(tok);

    if (motor < 1 || motor > 8) {
      Serial.println("ERR motor fuera de rango");
      return;
    }
    if (us < MIN_US || us > MAX_US) {
      Serial.println("ERR us fuera de rango");
      return;
    }

    setMotorUS(motor, us);
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

  for (int i = 1; i <= 8; i++) {
    setMotorUS(i, NEUTRAL_US);
  }

  Serial.println("READY");
}

void loop() {
  if (Serial.available()) {
    String line = Serial.readStringUntil('\n');
    if (line.length() > 0) {
      procesarLinea(line);
    }
  }
}
