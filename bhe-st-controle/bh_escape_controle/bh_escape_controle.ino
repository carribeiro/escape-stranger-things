// (C) 2021 FAZ MAKERSPACE
// CAIXA DE CONTROLE BH ESCAPE
// SALA STRANGER THINGS
//

/****************************************************************************

FUNCIONAMENTO

Árvore Genealógica
------------------

CHAVE_LIGA_ARVORE: Chave que liga o circuito de alimentação do quadro. 
Comando elétrico direto (não é acionado pelo microcontrolador).

LED_QUADRO_LIGADO: Led que fica aceso quando o quadro está alimentado. 
Alimentação direta pelo circuito, não passa pelo microcontrolador.

  - Resistor de 150 ohms (5 VDC).

INPUT_ARVORE_GENEALOGICA_OK: Pino de entrada com pullup, serve para receber
o sinal dos reed switches. Quando o pino fica LOW indica que o quadro está
solucionado.

  - Configuração do pino: INPUT_PULLUP

BOTAO_BYPASS_ARVORE: Botão de pulso, montado em paralelo com o sinal 
INPUT_ARVORE_GENEALOGICA_OK. Quando pressionado, libera o jogo como se
estivesse solucionado.

LED_QUADROS_OK: Led que fica aceso quando o quadro for solucionado. 
Alimentação direta pelo circuito, não passa pelo microcontrolador.

  - Resistor de 150 ohms (5 VDC).

OUTPUT_QUADRO_OK: Sinal de controle que arma o relé da TV. 

  - Configuração do pino: OUTPUT
  - Conectado ao relé 01 do banco de relés
  - Sinal de controle a definir (12 VDC ou 127 VAC)

CHAVE_LIGA_TV: Chave que liga a TV. Fica em paralelo com o relé de controle
da TV. Quando ligada, força a tomada da TV a ficar ligada. Quando DESLIGADA
permite que o relé faça o controle da TV.

LED_TV_LIGADA. LED que fica aceso enquanto o relé estiver ligado.

--> Ainda tenho dúvida de como ligar isso; se a TV fosse alimentada com
12VDC seria mais fácil, bastava pegar a saída de 12VDC com um resistor 
adequado (470 ohms).

--> Se a TV utilizar uma tomada de 127 VDC o circuito precisa de diodos de 
proteção e um resistor com capacidade de dissipação suficiente; ou ainda, de
um circuito onde um capacitor de 1 uF faz o papel de um "falso resistor".

Ref.:
https://ensinandoeletrica.blogspot.com/2017/11/como-ligar-leds-em-127v-ou-220v.html


RPG
---

CHAVE_LIGA_RPG: Chave que liga o circuito de alimentação do RPG. Envia 127 
VDC para a mesa, que tem alimentação própria com carregador embutido.

  Observações:
  - poderia ter sido feito com alimentação de 12 VDC entrando direto por 
    regulador de tensão, para dar mais segurança.
  - chave dupla, que liga um circuito de 12 VDC que alimenta a tranca 
    e também o LED_RPG_LIGADO com um resistor apropriado.

LED_RPG_LIGADO: Led alimentado diretamente pela CHAVE_LIGA_RPG (chave 
dupla com circuito secundário de 12 VDC). 

  - Resistor de 470 ohms (12 VDC).

--> verificar interação do circuito; acho que o controle da porta da 
armadilha precisa, por segurança, ficar dependente de o RPG estar sempre
ligado. se estiver desligado, a porta fica destrancada. isso dá segurança 
de não deixar ninguém trancado.

INPUT_RPG_OK: Pino de entrada com pullup, serve para receber o sinal do 
RPG. Quando o pino fica LOW indica que o RPG está solucionado.

  Observações:
  - Configuração do pino: INPUT_PULLUP
  - O pino de controle na mesa de RPG fica configurado como INPUT (estado de
    alta impedância), fazendo com que o PULLUP da entrada da mesa de controle
    garanta a leitura do nivel HIGH. Quando o jogo é resolvido a mesa de RPG
    comuta o pino para OUTPUT com sinal LOW, aterrando a saída.

BOTAO_BYPASS_RPG: Botão de pulso, montado em paralelo com o sinal de entrada
da INPUT_RPG_OK. Quando pressionado, libera o RPG como se estivesse
solucionado.

LED_RPG_OK: Led que fica aceso quando o RPG for solucionado. Por segurança,
será alimentado pelo microcontrolador.

  - Configuração do pino: OUTPUT
  - Resistor de 150 ohms (5 VDC).

BOTAO_RESET_RPG: Botão de pulso, quando acionado envia sinal LOW para o 
microcontrolador da mesa de RPG. Necessário para reiniciar o jogo depois de
resolvido.

  Observação:
  - Quando o jogo RPG é ligado, se as cartas já estiverem no lugar, ele NÃO
    ENVIA O SINAL; precisa zerar a mesa primeiro.

OUTPUT_RESET_RPG: saída ligada diretamente ao BOTAO_RESET_RPG, não passa 
pelo microcontrolador.

OUTPUT_RPG_OK: Sinal de controle que arma o relé da porta da armadilha. 

  - Configuração do pino: OUTPUT
  - Conectado ao relé 02 do banco de relés
  - Sinal de controle de 12 VDC.

CHAVE_TRANCA_PORTA_ARMADILHA: Chave que controla diretamente a porta da 
armadilha. Fica em paralelo com o relé de controle da porta. Quando ligada,
força a porta ficar TRANCADA. Quando DESLIGADA, permite que o relé faça o
controle da porta.

LED_TRANCA_PORTA_ARMADILHA: LED que fica aceso enquanto o relé da tranca 
estiver ligado. 

  Observação:
  - Resistor de 470 ohms (12 VDC).


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


Carta Will
----------

CHAVE_LIGA_CARTA_WILL: Chave que liga o circuito de alimentação da Carta
Will (quebra cabeças do armário). Chave dupla; a chave (A) libera 12 VDC
para acionar o relé da tranca do armário, a chave (B) conecta o sinal de 
terra de referência para acendimento dos LEDs, etc.

LED_WILL_LIGADO: Led alimentado diretamente pela CHAVE_LIGA_CARTA_WILL
(chave dupla).

  - Resistor de 470 ohms (12 VDC).

INPUT_SENSOR_WILL_OK: Pino de entrada com pullup, serve para receber o sinal
da reed switch do sensor Will. Quando o pino fica LOW indica que o objeto
está corretamente posicionado.

  Observações:
  - Configuração do pino: INPUT_PULLUP
  - Mesmo esquema do quadro da Árvore Genealógica (reed switch direto).

LED_SENSOR_WILL_ATIVADO: Led alimentado diretamente pelo reed switch do 
SENSOR WILL.

  - Resistor de 150 ohms (5 VDC).

INPUT_PORTA_ARMARIO: Pino de entrada com pullup, serve para receber o 
sinal da porta do armário, indicando que está fechada. Quando o pino fica
LOW indica que a porta está fechada; HIGH indica porta aberta.

  Observações:
  - Configuração do pino: INPUT_PULLUP
  - Mesmo esquema do quadro da Árvore Genealógica (reed switch direto).

LED_ARMARIO_ABERTO: Led alimentado diretamente pelo reed switch do 
INPUT_PORTA_ARMARIO.

  - Resistor de 150 ohms (5 VDC).

OUTPUT_WILL_OK: Sinal de controle que arma o relé da porta do armário. 

  - Configuração do pino: OUTPUT
  - Conectado ao relé 04 do banco de relés
  - Sinal de controle de 12 VDC

BOTAO_BYPASS_WILL: Botão de pulso, montado em paralelo com o sinal de 
entrada de INPUT_SENSOR_WILL_OK. Quando pressionado, libera a porta do 
armário como se estivesse solucionada.

CHAVE_TRANCA_PORTA_ARMARIO: Chave que controla diretamente a porta da 
armadilha. Fica em paralelo com o relé de controle da porta. Quando ligada,
força a porta ficar TRANCADA. Quando DESLIGADA, permite que o relé faça o
controle da porta.

LED_TRANCA_PORTA_ARMARIO: LED que fica aceso enquanto o relé da tranca 
estiver ligado. 

  Observação:
  - Resistor de 470 ohms (12 VDC).

****************************************************************************/



// pins

#define INPUT_ARVORE_GENEALOGICA_OK (2)
#define OUTPUT_QUADRO_OK (3)
#define OUTPUT_TOMADA_TV (3)

#define INPUT_RPG_OK (4)
#define LED_RPG_OK A1
#define INPUT_RPG_ON A2
#define INPUT_RESET_RPG A3
#define OUTPUT_RESET_RPG (5)
#define OUTPUT_RPG_OK (6)
#define OUTPUT_TRAVA_ARMADILHA (6)

#define INPUT_SENSOR_WILL_OK (10)
#define INPUT_PORTA_ARMARIO (11)
#define OUTPUT_WILL_OK (12)
#define OUTPUT_TRAVA_ARMARIO (12)

#define INPUT_BOMBAS_OK (7)
#define INPUT_PORTA_ARMADILHA (8)
#define OUTPUT_ARMADILHA_OK (9)
#define OUTPUT_PORTA_PRINCIPAL A4
#define OUTPUT_TRAVA_PRINCIPAL A4

boolean porta_armadilha = true;
boolean porta_armario = true;
boolean porta_principal = true;
boolean tomada_tv = false;

//boolean luz_interna_armario = false;  // ver se precisa de um pino pra isso

boolean arvore_genealogica_ok = false;
boolean rpg_ok = false;
boolean sensor_porta_armadilha = false;
boolean sensor_porta_armario = false;
boolean sensor_will_ok = false;
boolean bombas_ok = false;

boolean old_arvore_genealogica_ok = false;
boolean old_rpg_ok = false;
boolean old_sensor_porta_armadilha = false;
boolean old_sensor_porta_armario = false;
boolean old_sensor_will_ok = false;
boolean old_bombas_ok = false;

void reset_game() {

  // configura pinos
  pinMode(INPUT_ARVORE_GENEALOGICA_OK, INPUT_PULLUP);
  pinMode(OUTPUT_QUADRO_OK, OUTPUT);
  pinMode(INPUT_RPG_OK, INPUT_PULLUP);
  pinMode(LED_RPG_OK, OUTPUT);
  pinMode(OUTPUT_RESET_RPG, OUTPUT);
  pinMode(OUTPUT_RPG_OK, OUTPUT);
  pinMode(INPUT_BOMBAS_OK, INPUT_PULLUP);
  pinMode(INPUT_PORTA_ARMADILHA, INPUT_PULLUP);
  pinMode(OUTPUT_ARMADILHA_OK , OUTPUT);
  pinMode(INPUT_SENSOR_WILL_OK, INPUT_PULLUP);
  pinMode(INPUT_PORTA_ARMARIO, INPUT_PULLUP);
  pinMode(OUTPUT_WILL_OK, OUTPUT);
  pinMode(OUTPUT_PORTA_PRINCIPAL, OUTPUT);
  
  desliga_tomada_tv();
  reset_rpg();
  trava_porta_armadilha();
  trava_porta_armario();
  trava_porta_principal();

  atualiza_status();
}

void desliga_tomada_tv() {
  Serial.println("Desliga tomada da TV");
  tomada_tv = false;
  digitalWrite(OUTPUT_TOMADA_TV, LOW);
}

void liga_tomada_tv() {
  Serial.println("Liga tomada da TV");
  tomada_tv = true;
  digitalWrite(OUTPUT_TOMADA_TV, HIGH);
}

void reset_rpg() {
  Serial.println("Reseta o RPG");
  digitalWrite(LED_RPG_OK, LOW);
  digitalWrite(OUTPUT_RESET_RPG, HIGH);
}

void trava_porta_armadilha() {
  Serial.println("Trava porta da armadilha");
  porta_armadilha = true;
  digitalWrite(OUTPUT_TRAVA_ARMADILHA, HIGH);
}

void destrava_porta_armadilha() {
  Serial.println("Destrava porta da armadilha");
  porta_armadilha = false;
  digitalWrite(OUTPUT_TRAVA_ARMADILHA, LOW);
}

void trava_porta_armario() {
  Serial.println("Trava porta do armário");
  porta_armario = true;
  digitalWrite(OUTPUT_TRAVA_ARMARIO, HIGH);
}

void destrava_porta_armario() {
  Serial.println("Destrava porta do armário");
  porta_armario = false;
  digitalWrite(OUTPUT_TRAVA_ARMARIO, LOW);
}

void trava_porta_principal() {
  Serial.println("Trava porta principal");
  porta_principal = true;
  digitalWrite(OUTPUT_TRAVA_PRINCIPAL, HIGH);
}

void destrava_porta_principal() {
  Serial.println("Destrava porta principal");
  porta_principal = false;
  digitalWrite(OUTPUT_TRAVA_PRINCIPAL, LOW);
}

boolean atualiza_status() {
  // save old status
  old_arvore_genealogica_ok = arvore_genealogica_ok;
  old_rpg_ok = rpg_ok;
  old_sensor_porta_armadilha = sensor_porta_armadilha;
  old_sensor_porta_armario = sensor_porta_armario;
  old_sensor_will_ok = sensor_will_ok;
  old_bombas_ok = bombas_ok;

  // read new status; signals that are true when LOW are inverted on read to simplify logic
  arvore_genealogica_ok = !digitalRead(INPUT_ARVORE_GENEALOGICA_OK);
  rpg_ok = !digitalRead(INPUT_RPG_OK);
  sensor_porta_armadilha = !digitalRead(INPUT_PORTA_ARMADILHA);
  sensor_porta_armario = !digitalRead(INPUT_PORTA_ARMARIO);
  sensor_will_ok = !digitalRead(INPUT_SENSOR_WILL_OK);
  bombas_ok = !digitalRead(INPUT_BOMBAS_OK);   

  // returns true if anything changed
  return (
    (arvore_genealogica_ok != old_arvore_genealogica_ok) ||
    (rpg_ok != old_rpg_ok) ||
    (sensor_porta_armadilha != old_sensor_porta_armadilha) ||
    (sensor_porta_armario != old_sensor_porta_armario) ||
    (sensor_will_ok != old_sensor_will_ok) ||
    (bombas_ok != old_bombas_ok)
    );
}

void imprime_status() {
  Serial.println();
  Serial.print("STATUS ("); Serial.print(long(millis()/1000)); Serial.println(")");
  Serial.print("Árvore: "); Serial.println(arvore_genealogica_ok);
  Serial.print("RPG: "); Serial.println(rpg_ok);
  Serial.print("Porta armadilha: "); Serial.println(sensor_porta_armadilha);
  Serial.print("Porta armário: "); Serial.println(sensor_porta_armario);
  Serial.print("Will: "); Serial.println(sensor_will_ok);
  Serial.print("Bombas: "); Serial.println(bombas_ok);  
}

void setup() {
  Serial.begin(115200);
  Serial.println();
  Serial.println();
  Serial.println();
  Serial.println("BHESCAPE STRANGER THINGS");
  Serial.println("NOVO JOGO");
  reset_game();
}

void loop() {
  // Serial.println("LOOP");

  boolean status_changed;

  status_changed = atualiza_status();
  if (status_changed) {
    imprime_status();
  }

  // ARVORE GENEALOGICA
  if (arvore_genealogica_ok != old_arvore_genealogica_ok) {
    if (arvore_genealogica_ok) {
      Serial.println("Árvore OK");
      tomada_tv = false;  
      digitalWrite(OUTPUT_QUADRO_OK, LOW);
    }
    else {
      Serial.println("Árvore NÃO OK");
      /*
       * depois que ligou, não desliga mais
      tomada_tv = false;  
      digitalWrite(OUTPUT_QUADRO_OK, false);
      */
    }
  }

  // RPG
  if (rpg_ok != old_rpg_ok) {
    if (rpg_ok) {
      Serial.println("RPG OK");
      digitalWrite(LED_RPG_OK, HIGH);
      porta_armadilha = false;
      digitalWrite(OUTPUT_RPG_OK, HIGH);
    }
    else {
      Serial.println("RPG NÃO OK");
      digitalWrite(LED_RPG_OK, LOW);
      /*
      porta_armadilha = true;  
      digitalWrite(OUTPUT_RPG_OK, false);
      */
    }
  }

  if (sensor_will_ok != old_sensor_will_ok) {
    if (sensor_will_ok) {
      Serial.println("Will OK");
      // desliga o relé pra abrir a porta do armário
      digitalWrite(OUTPUT_WILL_OK, LOW);
    }
    else {/*
      Serial.println("Will NÃO OK");
      // liga o relé pra trancar a porta do armário
      digitalWrite(OUTPUT_WILL_OK, HIGH);
      */
    }
  }

  if (bombas_ok != old_bombas_ok) {
    bombas_ok = !digitalRead(INPUT_BOMBAS_OK);
    if (bombas_ok) {
      Serial.println("Bombas OK");
      // desliga o relé pra abrir a porta do principal, apaga as luzes
      porta_principal = false;
      digitalWrite(OUTPUT_PORTA_PRINCIPAL, LOW);
    }
  }

  String input;
  if(Serial.available()) {
      input = Serial.readStringUntil('\n');
      input.trim();
      if (input.equalsIgnoreCase("STATUS")) {
        imprime_status();
      }
      else if (input.equalsIgnoreCase("RESTART")) {
        Serial.println("Travando porta principal"); 
        reset_game();
      }
      else if (input.equalsIgnoreCase("ABRIR SALA")) {
        destrava_porta_principal();
      }
      else if (input.equalsIgnoreCase("FECHAR SALA")) {
        trava_porta_principal();
      }
      else if (input.equalsIgnoreCase("ABRIR ARMADILHA")) {
        destrava_porta_armadilha();
      }
      else if (input.equalsIgnoreCase("FECHAR ARMADILHA")) {
        trava_porta_armadilha();
      }
      else if (input.equalsIgnoreCase("ABRIR ARMARIO")) {
        destrava_porta_armario();
      }
      else if (input.equalsIgnoreCase("FECHAR ARMARIO")) {
        trava_porta_armario();
      }
      else if (input.equalsIgnoreCase("RESET RPG")) {
         Serial.println("RPG_OK"); 
         digitalWrite(LED_RPG_OK, HIGH);
      }
      else {
        Serial.print("Comando não reconhecido: <");
        Serial.print(input); Serial.print("> "); Serial.println(input.length());
      }
  }
  
  delay(100);
}
