// ROBOT MINI SUMO - ARDUINO MINI PRO CON PULL-UPS
// CONFIGURACIÓN DE PINES - VERSIÓN CORREGIDA

// Motores L293D
#define IN1 2    // Motor izquierdo
#define IN2 3    // Motor izquierdo  
#define IN3 5    // Motor derecho
#define IN4 4    // Motor derecho

// Sensores E3Z-T61 DIGITALES (oponente) - CON PULL-UPS
#define SENSOR_C 8   // Sensor central 
#define SENSOR_I 9   // Sensor izquierdo  
#define SENSOR_D 10  // Sensor derecho

// Sensores Pololu QTR-1C (línea) - CON PULL-UPS
#define LINEA_I 6     // Sensor línea izquierdo
#define LINEA_D 7     // Sensor línea derecho

// LEDs de cuenta regresiva
#define LED_ROJO 11
#define LED_AMARILLO 12
#define LED_VERDE 13

// Variables de estrategia
unsigned long tiempoInicio;
bool enCombate = false;

void setup() {
  // Configurar pines de motores
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  
  // 🔥 CONFIGURAR SENSORES CON PULL-UPS INTERNOS
  pinMode(SENSOR_C, INPUT_PULLUP);
  pinMode(SENSOR_I, INPUT_PULLUP);
  pinMode(SENSOR_D, INPUT_PULLUP);
  pinMode(LINEA_I, INPUT_PULLUP);
  pinMode(LINEA_D, INPUT_PULLUP);
  
  // Configurar LEDs
  pinMode(LED_ROJO, OUTPUT);
  pinMode(LED_AMARILLO, OUTPUT);
  pinMode(LED_VERDE, OUTPUT);
  
  // DEBUG INICIAL - Verificar lecturas de sensores
  debugSensores();
  
  // Secuencia de inicio reglamentaria
  secuenciaInicio();
  
  tiempoInicio = millis();
}

void debugSensores() {
  // Función para verificar que los sensores funcionan
  digitalWrite(LED_VERDE, HIGH);
  delay(1000);
  
  // Leer y mostrar estado inicial de sensores
  bool centro = digitalRead(SENSOR_C);
  bool izq = digitalRead(SENSOR_I);
  bool der = digitalRead(SENSOR_D);
  bool lineaizq = digitalRead(LINEA_I);
  bool lineader = digitalRead(LINEA_D);
  
  // Indicar con LEDs si hay detección
  if (!centro || !izq || !der) {
    digitalWrite(LED_ROJO, HIGH); // Opuesto detectado
  }
  if (!lineaizq || !lineader) {
    digitalWrite(LED_AMARILLO, HIGH); // Línea detectada
  }
  
  delay(2000);
  digitalWrite(LED_ROJO, LOW);
  digitalWrite(LED_AMARILLO, LOW);
  digitalWrite(LED_VERDE, LOW);
}

void loop() {
  // 🔥 LECTURA CORREGIDA CON PULL-UPS:
  // INPUT_PULLUP invierte la lógica:
  // - HIGH = No detecta (4V se convierte en 5V con pull-up)
  // - LOW = Detecta (0V se mantiene en 0V)
  
  bool oponenteCentro = !digitalRead(SENSOR_C);  // LOW = detecta
  bool oponenteIzq = !digitalRead(SENSOR_I);     // LOW = detecta  
  bool oponenteDer = !digitalRead(SENSOR_D);     // LOW = detecta
  
  bool lineaIzq = !digitalRead(LINEA_I);         // LOW = línea blanca
  bool lineaDer = !digitalRead(LINEA_D);         // LOW = línea blanca
  
  // DEBUG OPcional: Monitorizar sensores con LEDs
  monitorizarSensores(oponenteCentro, oponenteIzq, oponenteDer, lineaIzq, lineaDer);
  
  // PRIORIDAD 1: Detectar línea blanca (EVITAR)
  if (lineaIzq || lineaDer) {
    digitalWrite(LED_AMARILLO, HIGH); // Indicar detección línea
    evitarLinea(lineaIzq, lineaDer);
    digitalWrite(LED_AMARILLO, LOW);
  }
  // PRIORIDAD 2: Detectar oponente (ATACAR)
  else if (oponenteCentro || oponenteIzq || oponenteDer) {
    digitalWrite(LED_ROJO, HIGH); // Indicar detección oponente
    atacarOponente(oponenteCentro, oponenteIzq, oponenteDer);
    digitalWrite(LED_ROJO, LOW);
  }
  // PRIORIDAD 3: Búsqueda de oponente
  else {
    buscarOponente();
  }
}

void monitorizarSensores(bool centro, bool izq, bool der, bool lineaI, bool lineaD) {
  // Usar LED VERDE para indicar funcionamiento normal
  static unsigned long ultimoParpadeo = 0;
  
  if (millis() - ultimoParpadeo > 500) {
    digitalWrite(LED_VERDE, !digitalRead(LED_VERDE));
    ultimoParpadeo = millis();
  }
}

// ... (el resto de las funciones se mantienen igual que antes)
// secuenciaInicio(), atacarOponente(), evitarLinea(), buscarOponente(), etc.

void secuenciaInicio() {
  // LED ROJO (0-2 segundos)
  digitalWrite(LED_ROJO, HIGH);
  delay(2000);
  digitalWrite(LED_ROJO, LOW);
  
  // LED AMARILLO (2-4 segundos)
  digitalWrite(LED_AMARILLO, HIGH);
  delay(2000);
  digitalWrite(LED_AMARILLO, LOW);
  
  // LED VERDE (4-5 segundos) - ¡COMIENZA!
  digitalWrite(LED_VERDE, HIGH);
  delay(1000);
  digitalWrite(LED_VERDE, LOW);
  
  enCombate = true;
}

void atacarOponente(bool centro, bool izq, bool der) {
  // OPONENTE CENTRAL - ATAQUE FRONTAL AGRESIVO
  if (centro) {
    motorAdelante(255, 255);
    delay(30);
  }
  // OPONENTE IZQUIERDO - GIRO IZQUIERDO AGRESIVO
  else if (izq) {
    motorGiroIzquierdo(255, 220);
    delay(25);
  }
  // OPONENTE DERECHO - GIRO DERECHO AGRESIVO
  else if (der) {
    motorGiroDerecho(220, 255);
    delay(25);
  }
}

void evitarLinea(bool lineaizq, bool lineader) {
  // RETROCESO RÁPIDO
  motorAtras(220, 220);
  delay(350);
  
  if (lineaizq && lineader) {
    motorGiroDerecho(200, 200);
    delay(600);
  }
  else if (lineaizq) {
    motorGiroDerecho(180, 180);
    delay(450);
  }
  else if (lineader) {
    motorGiroIzquierdo(180, 180);
    delay(450);
  }
  
  motorStop();
  delay(100);
}

void buscarOponente() {
  // (Mantener la misma lógica de búsqueda)
  motorGiroDerecho(180, 180);
  delay(400);
}

// Funciones de motores (igual que antes)
void motorAdelante(int velIzq, int velDer) {
  analogWrite(IN1, velIzq);
  analogWrite(IN2, 0);
  analogWrite(IN3, velDer);
  analogWrite(IN4, 0);
}

void motorAtras(int velIzq, int velDer) {
  analogWrite(IN1, 0);
  analogWrite(IN2, velIzq);
  analogWrite(IN3, 0);
  analogWrite(IN4, velDer);
}

void motorGiroIzquierdo(int velIzq, int velDer) {
  analogWrite(IN1, 0);
  analogWrite(IN2, velIzq);
  analogWrite(IN3, velDer);
  analogWrite(IN4, 0);
}

void motorGiroDerecho(int velIzq, int velDer) {
  analogWrite(IN1, velIzq);
  analogWrite(IN2, 0);
  analogWrite(IN3, 0);
  analogWrite(IN4, velDer);
}

void motorStop() {
  analogWrite(IN1, 0);
  analogWrite(IN2, 0);
  analogWrite(IN3, 0);
  analogWrite(IN4, 0);
}