// (C) 2021 FAZ MAKERSPACE
// CAIXA DE CONTROLE BH ESCAPE
// SALA STRANGER THINGS
//

/****************************************************************************

FUNCIONAMENTO

Armadilha
---------

CHAVE_LIGA_ARMADILHA: Chave que liga o circuito de alimentação da Armadilha
(controle das bombas). Envia 127 VDC para a caixa das bombas, que tem 
alimentação própria com fonte de 12 VDC embutida.

  Observações:
  - não oferece riscos de segurança tão grandes, pois a caixa é fechada e 
    fica na parede (não tem cabo debaixo do tapete).

LED_BASES_LIGADAS: Led alimentado diretamente pela CHAVE_LIGA_RPG (chave 
dupla com circuito secundário de 12 VDC). 

  - Resistor de 470 ohms (12 VDC).

INPUT_BOMBAS_OK: Pino de entrada com pullup, serve para receber o sinal das 
bombas. Quando o pino fica LOW indica que as bombas estão todas armadas.

  Observações:
  - Configuração do pino: INPUT_PULLUP
  - Ver observação sobre pino de controle da mesa de RPG (mesmo esquema).

INPUT_PORTA_ARMADILHA: Pino de entrada com pullup, serve para receber o 
sinal da porta da armadilha, indicando que está fechada. Quando o pino fica
LOW indica que a porta está fechada; HIGH indica porta aberta.

  Observações:
  - Configuração do pino: INPUT_PULLUP
  - Mesmo esquema do quadro da Árvore Genealógica (reed switch direto).

BOTAO_BYPASS_ARMADILHA: Botão de pulso, montado em paralelo com o sinal de 
entrada da INPUT_BOMBAS_OK e INPUT_PORTA_ARMADILHA. Quando pressionado, 
libera a armadilha como se estivesse solucionada (aterra os dois sinais).

--> importante: todos os sinais de controle precisam de um resistor de 
proteção que fica nos módulos remotos (RPG ou Armadilha), dimensionado entre
270 ohms e 470 ohms. Isso evita que um sinal de saída em HIGH (que não 
deveria acontecer, mas pode por conta de algum bug) não gere um curto com os
botões de bypass que jogam o sinal para o terra diretamente.

LED_BOMBAS_ATIVAS: Led que fica aceso quando todas as bombas forem ativadas.
Por segurança, será alimentado pelo microcontrolador.

  - Configuração do pino: OUTPUT
  - Resistor de 150 ohms (5 VDC).

LED_PORTA_FECHADA: Led que fica aceso quando a porta estiver fechada. O 
sensor reed fecha e permite o acendimento direto do LED (não passa pelo 
microcontrolador).

  - Resistor de 150 ohms (5 VDC).

OUTPUT_ARMADILHA_OK: Sinal de controle que indica explosão da bomba. Efeito
temporizado, alimenta um relé. Temporizado (tempo de efeito a decidir).

  - Configuração do pino: OUTPUT
  - Conectado ao relé 03 do banco de relés
  - Sinal de controle de 12 VDC.

LED_EXPLOSÃO_BOMBA: Led acionado pelo relé 03 (ativado pelo sinal 
OUTPUT_ARMADILHA_OK).

****************************************************************************/

// pins

#define INPUT_BOMBA_01_ON (2)
#define INPUT_BOMBA_02_ON (3)
#define INPUT_BOMBA_03_ON (4)

#define INPUT_BOMBA_01_SET (5)
#define INPUT_BOMBA_02_SET (6)
#define INPUT_BOMBA_03_SET (7)

#define INPUT_SENSOR_PORTA_ARMADILHA (8)

#define OUTPUT_BOMBAS_LIGADAS (9)
#define OUTPUT_BOMBAS_OK (10)  
#define OUTPUT_SENSOR_PORTA_ARMADILHA (11)

// OUTPUT_BOMBAS_OK --> vermelho
// GROUND --> marrom
// OUTPUT_SENSOR_PORTA_ARMADILHA --> laranja
// OUTPUT_BOMBAS_LIGADAS --> amarelo

boolean porta_armadilha = true;
boolean bombas_ok = false;

void reset_game() {

  // configura pinos
  pinMode(INPUT_BOMBA_01_ON, INPUT_PULLUP);
  pinMode(INPUT_BOMBA_02_ON, INPUT_PULLUP);
  pinMode(INPUT_BOMBA_03_ON, INPUT_PULLUP);
  pinMode(INPUT_BOMBA_01_SET, INPUT_PULLUP);
  pinMode(INPUT_BOMBA_02_SET, INPUT_PULLUP);
  pinMode(INPUT_BOMBA_03_SET, INPUT_PULLUP);
  pinMode(INPUT_SENSOR_PORTA_ARMADILHA, INPUT);
  pinMode(OUTPUT_BOMBAS_LIGADAS, OUTPUT);
  pinMode(OUTPUT_BOMBAS_OK, OUTPUT);
  pinMode(OUTPUT_SENSOR_PORTA_ARMADILHA, OUTPUT);
  pinMode(INPUT_SENSOR_PORTA_ARMADILHA, INPUT);

  // limpa sinais enviados para a caixa  
  digitalWrite(OUTPUT_BOMBAS_LIGADAS, HIGH);
  digitalWrite(OUTPUT_BOMBAS_OK, HIGH);
  digitalWrite(OUTPUT_SENSOR_PORTA_ARMADILHA, HIGH);
}

void setup() {
  Serial.begin(115200);
  Serial.println("START - CONTROLE DA ARMADILHA");
  reset_game();
}

void loop() {

  Serial.print(" ON-01:"); Serial.print(digitalRead(INPUT_BOMBA_01_ON)); Serial.print(" "); 
  Serial.print(" ON-02:"); Serial.print(digitalRead(INPUT_BOMBA_02_ON)); Serial.print(" "); 
  Serial.print(" ON-03:"); Serial.print(digitalRead(INPUT_BOMBA_03_ON)); Serial.print(" "); 
  Serial.println();
  Serial.print("SET-01:"); Serial.print(digitalRead(INPUT_BOMBA_01_SET)); Serial.print(" "); 
  Serial.print("SET-02:"); Serial.print(digitalRead(INPUT_BOMBA_02_SET)); Serial.print(" "); 
  Serial.print("SET-03:"); Serial.print(digitalRead(INPUT_BOMBA_03_SET)); Serial.print(" "); 
  Serial.println();
  boolean bombas_ligadas = 
    !digitalRead(INPUT_BOMBA_01_ON) && 
    !digitalRead(INPUT_BOMBA_02_ON) && 
    !digitalRead(INPUT_BOMBA_03_ON);
  boolean bombas_armadas = 
    !digitalRead(INPUT_BOMBA_01_SET) && 
    !digitalRead(INPUT_BOMBA_02_SET) && 
    !digitalRead(INPUT_BOMBA_03_SET);

  if (bombas_ligadas) {
    digitalWrite(OUTPUT_BOMBAS_LIGADAS, LOW);
  }
  if (bombas_armadas) {
    digitalWrite(OUTPUT_BOMBAS_OK, LOW);
  }
  delay(500);

}
