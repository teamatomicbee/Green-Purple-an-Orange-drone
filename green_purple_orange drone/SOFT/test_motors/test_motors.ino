// TEST SIMPLE DE MOTORES - SIN SENSORES NI LEDs

// Motores L293D
#define IN1 2    // Motor izquierdo Adelante
#define IN2 3    // Motor izquierdo Atrás  
#define IN3 5    // Motor derecho Adelante
#define IN4 4    // Motor derecho Atrás

void setup() {
  // Configurar pines de motores
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
}

void loop() {
  // TEST 1: MOTOR DERECHO ADELANTE 5 segundos
  motorDerechoAdelante();
  delay(5000);
  motorStop();
  delay(1000);

  // TEST 2: MOTOR IZQUIERDO ADELANTE 5 segundos
  motorIzquierdoAdelante();
  delay(5000);
  motorStop();
  delay(1000);

  // TEST 3: GIRO DERECHA 3 segundos
  motorGiroDerecha();
  delay(3000);
  motorStop();
  delay(1000);

  // TEST 4: GIRO IZQUIERDA 3 segundos
  motorGiroIzquierda();
  delay(3000);
  motorStop();
  delay(1000);
}

void motorDerechoAdelante() {
  analogWrite(IN1, 0);
  analogWrite(IN2, 0);
  analogWrite(IN3, 200);  // Derecho adelante
  analogWrite(IN4, 0);
}

void motorIzquierdoAdelante() {
  analogWrite(IN1, 200);  // Izquierdo adelante
  analogWrite(IN2, 0);
  analogWrite(IN3, 0);
  analogWrite(IN4, 0);
}

void motorGiroDerecha() {
  analogWrite(IN1, 200);  // Izquierdo adelante
  analogWrite(IN2, 0);
  analogWrite(IN3, 0);
  analogWrite(IN4, 200);  // Derecho atrás
}

void motorGiroIzquierda() {
  analogWrite(IN1, 0);
  analogWrite(IN2, 200);  // Izquierdo atrás
  analogWrite(IN3, 200);  // Derecho adelante
  analogWrite(IN4, 0);
}

void motorStop() {
  analogWrite(IN1, 0);
  analogWrite(IN2, 0);
  analogWrite(IN3, 0);
  analogWrite(IN4, 0);
}