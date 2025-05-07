// === DEFINIÇÃO DOS PINOS ===
#define S1 8 // Esquerda
#define S2 9 // CentroEsquerda
#define S3 10 // SensorCentro
#define S4 11 //CentroDireita
#define S5 12 //Direita

// Ponte H - Motor esquerdo (OUT1 e OUT2)
#define ENA 6
#define IN1 5
#define IN2 4

// Ponte H - Motor direito (OUT3 e OUT4)
#define ENB 7
#define IN3 2
#define IN4 3

void setup() {
  pinMode(S1, INPUT_PULLUP);
  pinMode(S2, INPUT_PULLUP);
  pinMode(S3, INPUT_PULLUP);
  pinMode(S4, INPUT_PULLUP);
  pinMode(S5, INPUT_PULLUP);

  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  // Inicialmente, desligar os motores
  digitalWrite(ENA, LOW);
  digitalWrite(ENB, LOW);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

void loop() {
  analogWrite(ENA, 200);
  analogWrite(ENB, 200);

  int s1 = digitalRead(S1);
  int s2 = digitalRead(S2);
  int s3 = digitalRead(S3);
  int s4 = digitalRead(S4);
  int s5 = digitalRead(S5);

  if (s3 == LOW && s2 == LOW && s4 == LOW && s1 == LOW && s5 == LOW) {
    frente();
  } else if (s3 == HIGH && s2 == LOW && s4 == LOW && s1 == LOW && s5 == LOW) {
    frente();
  } else if (s3 == HIGH && (s1 == HIGH || s5 == HIGH)) {
    parar();
  } else if (s4 == HIGH || s5 == HIGH) {
    curvaEsquerda();
  } else if (s2 == HIGH || s1 == HIGH) {
    curvaDireita();
  }  else {
    parar();
  }
}

void frente() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void curvaEsquerda() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void curvaDireita() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void parar() {
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}
