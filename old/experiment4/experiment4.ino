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

const int PWM_MIN = 1100;
const int PWM_MAX = 1900;
const int PWM_STOP = 1500;

struct ActiveRun {
  bool running = false;
  unsigned long endMillis = 0;
  int thrA = 0;
  int thrB = 0;
};

ActiveRun runState;

Servo* getThruster(int idx) {
  switch(idx) {
    case 1: return &thruster1;
    case 2: return &thruster2;
    case 3: return &thruster3;
    case 4: return &thruster4;
    case 5: return &thruster5;
    case 6: return &thruster6;
    case 7: return &thruster7;
    case 8: return &thruster8;
    default: return nullptr;
  }
}

void setStopAll() {
  for (int i=1;i<=8;i++) {
    Servo* s = getThruster(i);
    if (s) s->writeMicroseconds(PWM_STOP);
  }
}

bool setThruster(int idx, int pwm) {
  Servo* s = getThruster(idx);
  if (!s) return false;
  if (pwm < PWM_MIN || pwm > PWM_MAX) return false;
  s->writeMicroseconds(pwm);
  return true;
}

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
  setStopAll();
  Serial.println(F("READY"));
}

void processLine(char *line) {
  // Comando STOP
  if (strcasecmp(line, "STOP") == 0) {
    runState.running = false;
    setStopAll();
    Serial.println(F("STOPPED"));
    return;
  }
  if (runState.running) {
    Serial.println(F("BUSY"));
    return;
  }
  // Esperamos: t1 pwm1 t2 pwm2 dur
  int t1, p1, t2, p2, dur;
  int n = sscanf(line, "%d %d %d %d %d", &t1, &p1, &t2, &p2, &dur);
  if (n != 5) {
    Serial.println(F("ERR formato"));
    return;
  }
  if (t1 <1 || t1>8 || t2<1 || t2>8) {
    Serial.println(F("ERR thruster"));
    return;
  }
  if (p1 < PWM_MIN || p1 > PWM_MAX || p2 < PWM_MIN || p2 > PWM_MAX) {
    Serial.println(F("ERR pwm"));
    return;
  }
  if (dur <=0 || dur > 3600) {
    Serial.println(F("ERR tiempo"));
    return;
  }
  if (!setThruster(t1, p1) || !setThruster(t2, p2)) {
    Serial.println(F("ERR set"));
    return;
  }
  runState.running = true;
  runState.thrA = t1;
  runState.thrB = t2;
  runState.endMillis = millis() + (unsigned long)dur * 1000UL;
  Serial.println(F("OK"));
}

void loop() {
  static char buf[64];
  static uint8_t idx = 0;

  // Lectura no bloqueante
  while (Serial.available()) {
    char c = Serial.read();
    if (c == '\r') continue;
    if (c == '\n') {
      buf[idx] = 0;
      if (idx > 0) {
        processLine(buf);
      }
      idx = 0;
    } else if (idx < sizeof(buf)-1) {
      buf[idx++] = c;
    }
  }

  if (runState.running && millis() >= runState.endMillis) {
    // Terminar
    if (runState.thrA) setThruster(runState.thrA, PWM_STOP);
    if (runState.thrB) setThruster(runState.thrB, PWM_STOP);
    runState.running = false;
    Serial.println(F("DONE"));
  }
}