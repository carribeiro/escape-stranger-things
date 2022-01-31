// (C) 2021 FAZ MAKERSPACE
// CAIXA DE CONTROLE BH ESCAPE
// SALA STRANGER THINGS
//

/****************************************************************************

FUNCIONAMENTO

1) Conexão com a CAIXA DE CONTROLE

Cabo manga 4 vias.

- Vermelho: VCC
- Marrom: GND
- Amarelo: RESET (não implementado)
- Laranja: OK (bombas armadas)

2) Conexão BOMBA_01 a BOMBA_03

- Vermelho: VCC
- Marrom: GND
- Amarelo: BOMBA PRESENTE
- Laranja: BOMBA ARMADA

3) Sensor da porta da armadilha

- Sensor Hall
- GND

****************************************************************************/


#define DEBUG_OPTO (true)

// pins

#define INPUT_BOMBA_01_ON (5)
#define INPUT_BOMBA_02_ON (6)
#define INPUT_BOMBA_03_ON (7)

#define INPUT_BOMBA_01_SET (2)
#define INPUT_BOMBA_02_SET (3)
#define INPUT_BOMBA_03_SET (4)

#define INPUT_PORTA_ARMADILHA (8)

#define OUTPUT_BOMBAS_LIGADAS (9)
#define OUTPUT_BOMBAS_OK (10)  
#define OUTPUT_PORTA_ARMADILHA (11)

// OUTPUT_BOMBAS_OK --> vermelho
// GROUND --> marrom
// OUTPUT_PORTA_ARMADILHA --> laranja
// OUTPUT_BOMBAS_LIGADAS --> amarelo

void reset_game() {

  // configura pinos
  pinMode(INPUT_BOMBA_01_ON, INPUT_PULLUP);
  pinMode(INPUT_BOMBA_02_ON, INPUT_PULLUP);
  pinMode(INPUT_BOMBA_03_ON, INPUT_PULLUP);
  pinMode(INPUT_BOMBA_01_SET, INPUT);
  pinMode(INPUT_BOMBA_02_SET, INPUT);
  pinMode(INPUT_BOMBA_03_SET, INPUT);
  pinMode(INPUT_PORTA_ARMADILHA, INPUT_PULLUP);
  pinMode(OUTPUT_BOMBAS_LIGADAS, OUTPUT);
  pinMode(OUTPUT_BOMBAS_OK, OUTPUT);
  pinMode(OUTPUT_PORTA_ARMADILHA, OUTPUT);

  // limpa sinais enviados para a caixa central
  digitalWrite(OUTPUT_BOMBAS_LIGADAS, HIGH);
  digitalWrite(OUTPUT_BOMBAS_OK, HIGH);
  digitalWrite(OUTPUT_PORTA_ARMADILHA, HIGH);
}

void setup() {
  Serial.begin(115200);
  Serial.println("START - CONTROLE DA ARMADILHA");
  reset_game();
}

boolean readBomba(int bomba) {
  // referência: https://www.pololu.com/product/2455
  
  // Set the I/O line to an output and drive it high.
  pinMode(bomba, OUTPUT);
  digitalWrite(bomba, HIGH);
  
  // Allow at least 10 us for the sensor output to rise.
  delayMicroseconds(20);
  
  // Make the I/O line an input (high impedance).
  pinMode(bomba, INPUT);
  
  // Measure the time for the voltage to decay by waiting for the I/O line to go low.
  if (DEBUG_OPTO) {
    Serial.print("Bomba ");
    Serial.print(bomba);
    Serial.print(": ");
  }
  for (int i = 0; i < 50; i++) {
    boolean b = digitalRead(bomba);
    if (DEBUG_OPTO) {
      //Serial.print(b);
    }
    delay(20);
    if (b == 0) {
      if (DEBUG_OPTO) {
        Serial.println(i);
      }
      return (i < 5);
    }
  }
  if (DEBUG_OPTO) {
    Serial.println("");
  }
  return false;
}

boolean bomba_01_on = false;
boolean bomba_02_on = false;
boolean bomba_03_on = false;
boolean bomba_01_set = false;
boolean bomba_02_set = false;
boolean bomba_03_set = false;

boolean old_bomba_01_on = false;
boolean old_bomba_02_on = false;
boolean old_bomba_03_on = false;
boolean old_bomba_01_set = false;
boolean old_bomba_02_set = false;
boolean old_bomba_03_set = false;

boolean porta_armadilha = false;
boolean old_porta_armadilha = false;

boolean status_changed = false;

void loop() {

  // salva status antigo das bombas
  old_bomba_01_on = bomba_01_on;
  old_bomba_02_on = bomba_02_on;
  old_bomba_03_on = bomba_03_on;
  
  old_bomba_01_set = bomba_01_set;
  old_bomba_02_set = bomba_02_set;
  old_bomba_03_set = bomba_03_set;

  old_porta_armadilha = porta_armadilha;

  // carrega status atual das bombas
  bomba_01_on = !digitalRead(INPUT_BOMBA_01_ON);
  bomba_02_on = !digitalRead(INPUT_BOMBA_02_ON);
  bomba_03_on = !digitalRead(INPUT_BOMBA_03_ON);

  bomba_01_set = readBomba(INPUT_BOMBA_01_SET);
  bomba_02_set = readBomba(INPUT_BOMBA_02_SET);
  bomba_03_set = readBomba(INPUT_BOMBA_03_SET);

  porta_armadilha = !digitalRead(INPUT_PORTA_ARMADILHA);
  
  status_changed = (
    (old_bomba_01_on != bomba_01_on) ||
    (old_bomba_02_on != bomba_02_on) ||
    (old_bomba_03_on != bomba_03_on) ||    
    (old_bomba_01_set != bomba_01_set) ||
    (old_bomba_02_set != bomba_02_set) ||
    (old_bomba_03_set != bomba_03_set) ||
    (old_porta_armadilha != porta_armadilha)
    );

  if (status_changed) {
    Serial.print("BOMBA 01:"); Serial.print(bomba_01_on ? "ON " : "OFF"); Serial.print(","); Serial.print(bomba_01_set ? "ARMADA   " : "DESARMADA"); Serial.print("  ");
    Serial.print("BOMBA 02:"); Serial.print(bomba_02_on ? "ON " : "OFF"); Serial.print(","); Serial.print(bomba_02_set ? "ARMADA   " : "DESARMADA"); Serial.print("  ");
    Serial.print("BOMBA 03:"); Serial.print(bomba_03_on ? "ON " : "OFF"); Serial.print(","); Serial.print(bomba_03_set ? "ARMADA   " : "DESARMADA"); Serial.print("  ");
    Serial.print(porta_armadilha ? "PORTA FECHADA" : "PORTA ABERTA");
    Serial.println();
    
    boolean bombas_ligadas = bomba_01_on && bomba_02_on && bomba_03_on;
    boolean bombas_armadas = bomba_01_set && bomba_02_set && bomba_03_set;
  
    if (bombas_ligadas) {
      digitalWrite(OUTPUT_BOMBAS_LIGADAS, LOW);
    }
    if (bombas_armadas) {
      digitalWrite(OUTPUT_BOMBAS_OK, LOW);
    }
  }
  delay(150);

}
