// TEST SENSORES SIMPLE CON LEDs

// Sensores E3Z-T61 
#define SENSOR_C 8   // Sensor central 
#define SENSOR_I 9   // Sensor izquierdo  
#define SENSOR_D 10  // Sensor derecho

// LEDs
#define LED_ROJO 11    // Sensor izquierdo
#define LED_AMARILLO 12 // Sensor central  
#define LED_VERDE 13   // Sensor derecho

void setup() {
  // Configurar sensores con PULLUP
  pinMode(SENSOR_C, INPUT_PULLUP);
  pinMode(SENSOR_I, INPUT_PULLUP);
  pinMode(SENSOR_D, INPUT_PULLUP);
  
  // Configurar LEDs
  pinMode(LED_ROJO, OUTPUT);
  pinMode(LED_AMARILLO, OUTPUT);
  pinMode(LED_VERDE, OUTPUT);
  
  // Apagar todos los LEDs al inicio
  digitalWrite(LED_ROJO, LOW);
  digitalWrite(LED_AMARILLO, LOW);
  digitalWrite(LED_VERDE, LOW);
}

void loop() {
  // Leer sensores (LOW = detecta)
  bool centro = !digitalRead(SENSOR_C);
  bool izq = !digitalRead(SENSOR_I);  
  bool der = !digitalRead(SENSOR_D);
  
  // Controlar LEDs según sensores
  // LED ROJO = Sensor izquierdo detecta
  digitalWrite(LED_ROJO, izq);
  
  // LED AMARILLO = Sensor central detecta  
  digitalWrite(LED_AMARILLO, centro);
  
  // LED VERDE = Sensor derecho detecta
  digitalWrite(LED_VERDE, der);
  
  delay(50);
}