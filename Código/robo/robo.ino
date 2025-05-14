// === PINOS DOS SENSORES DE LINHA ===
const int sensorEsquerdo       = 8;  // S1
const int sensorCentroEsquerdo = 9;  // S2
const int sensorCentro         = 10; // S3
const int sensorCentroDireito  = 11; // S4
const int sensorDireito        = 12; // S5

// === PINOS DA PONTE H ===
// Motor esquerdo
const int motorEsqPWM  = 6; // ENA
const int motorEsqIN1  = 5; // IN1
const int motorEsqIN2  = 4; // IN2

// Motor direito
const int motorDirPWM  = 7; // ENB
const int motorDirIN3  = 2; // IN3
const int motorDirIN4  = 3; // IN4

// === VARIÁVEIS DE CONTROLE DE FAIXA ===
bool primeiraFaixaDetectada = false;
unsigned long tempoPrimeiraFaixa = 0;
const unsigned long intervaloMinimo = 400; // tempo mínimo entre detecções das faixas (ms)

void setup() {
  // Configura sensores como entrada com pull-up interno
  pinMode(sensorEsquerdo,       INPUT_PULLUP);
  pinMode(sensorCentroEsquerdo, INPUT_PULLUP);
  pinMode(sensorCentro,         INPUT_PULLUP);
  pinMode(sensorCentroDireito,  INPUT_PULLUP);
  pinMode(sensorDireito,        INPUT_PULLUP);

  // Configura pinos dos motores como saída
  pinMode(motorEsqPWM, OUTPUT);
  pinMode(motorEsqIN1, OUTPUT);
  pinMode(motorEsqIN2, OUTPUT);

  pinMode(motorDirPWM, OUTPUT);
  pinMode(motorDirIN3, OUTPUT);
  pinMode(motorDirIN4, OUTPUT);

  // Motores inicialmente desligados
  parar();
}

void loop() {
  // Velocidade dos motores
  analogWrite(motorEsqPWM, 200);
  analogWrite(motorDirPWM, 200);

  // Leitura dos sensores
  int s1 = digitalRead(sensorEsquerdo);
  int s2 = digitalRead(sensorCentroEsquerdo);
  int s3 = digitalRead(sensorCentro);
  int s4 = digitalRead(sensorCentroDireito);
  int s5 = digitalRead(sensorDireito);

  bool paradaDetectada = ((s1 == HIGH && s2 == LOW && s3 == HIGH && s4 == LOW && s5 == LOW) ||
   (s1 == LOW && s2 == LOW && s3 == HIGH && s4 == LOW && s5 == HIGH));

  if (paradaDetectada) {
    if (!primeiraFaixaDetectada) {
      primeiraFaixaDetectada = true;
      tempoPrimeiraFaixa = millis();
    } else if (millis() - tempoPrimeiraFaixa > intervaloMinimo) {
      parar();
      return;
    }
  }

  bool faixaCruzada = (s1 == HIGH && s2 == HIGH && s3 == HIGH && s4 == HIGH) || (s2 == HIGH && s3 == HIGH && s4 == HIGH && s5 == HIGH);

  bool darReDireita = (s1 == HIGH && s2 == LOW && s3 == LOW && s4 == LOW && s5 == LOW);
  bool darReEsquerda = (s1 == LOW && s2 == LOW && s3 == LOW && s4 == LOW && s5 == HIGH);

  // Lógica de linha
  if (s3 == LOW && s2 == LOW && s4 == LOW && s1 == LOW && s5 == LOW || faixaCruzada) {
    frente();
  } else if ((s1 == HIGH && s2 == HIGH) || darReEsquerda) {
    reEsquerda();
    delay(100);
  }
  else if ((s4 == HIGH && s5 == HIGH) || darReDireita) {
    reDireita();
    delay(100);
  } else if (s3 == HIGH && s2 == LOW && s4 == LOW && s1 == LOW && s5 == LOW) {
    frente();
  } else if (s4 == HIGH || s5 == HIGH) {
      curvaEsquerda();
  } else if (s2 == HIGH || s1 == HIGH) {
      curvaDireita();
  }  else {
    frente();
  }
}

// === FUNÇÕES DE MOVIMENTO ===

void frente() {
  digitalWrite(motorEsqIN1, HIGH);
  digitalWrite(motorEsqIN2, LOW);
  digitalWrite(motorDirIN3, HIGH);
  digitalWrite(motorDirIN4, LOW);
}

void curvaEsquerda() {
  digitalWrite(motorEsqIN1, HIGH);
  digitalWrite(motorEsqIN2, LOW);
  digitalWrite(motorDirIN3, LOW);
  digitalWrite(motorDirIN4, HIGH);
}

void curvaDireita() {
  digitalWrite(motorEsqIN1, LOW);
  digitalWrite(motorEsqIN2, HIGH);
  digitalWrite(motorDirIN3, HIGH);
  digitalWrite(motorDirIN4, LOW);
}

void reEsquerda() {
  digitalWrite(motorEsqIN1, LOW);
  digitalWrite(motorEsqIN2, HIGH);
  digitalWrite(motorDirIN3, HIGH);
  digitalWrite(motorDirIN4, LOW);
}

void reDireita() {
  digitalWrite(motorEsqIN1, HIGH);
  digitalWrite(motorEsqIN2, LOW);
  digitalWrite(motorDirIN3, LOW);
  digitalWrite(motorDirIN4, HIGH);
}


void parar() {
  analogWrite(motorEsqPWM, 0);
  analogWrite(motorDirPWM, 0);

  digitalWrite(motorEsqIN1, LOW);
  digitalWrite(motorEsqIN2, LOW);
  digitalWrite(motorDirIN3, LOW);
  digitalWrite(motorDirIN4, LOW);
}
