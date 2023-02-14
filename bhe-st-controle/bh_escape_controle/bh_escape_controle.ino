// (C) 2021 FAZ MAKERSPACE
// CAIXA DE CONTROLE BH ESCAPE
// SALA STRANGER THINGS
//
// pins

#include <FastLED.h>
#define NUM_LEDS 9
#define LEDS_DATA_PIN 12
CRGB leds[NUM_LEDS];

#define COR_VERDE    (CRGB::Green)
#define COR_AZUL     (CRGB::Blue)
#define COR_VERMELHO (CRGB::Red)
#define COR_AMARELO  (CRGB::Yellow)
#define COR_APAGADO  (CRGB::Black)

// os LEDs ficam nessa ordem na fita endereçada. Não são os pinos, é o "index" do vetor de LEDs
#define FL_ARVORE_OK          (0)
#define FL_ARVORE_RESOLVIDO   (1)
#define FL_RPG_OK             (2)
#define FL_RPG_RESOLVIDO      (3)
#define FL_BRASAO_OK          (4)
#define FL_BRASAO_RESOLVIDO   (5)
#define FL_BOMBAS_OK          (6)
#define FL_BOMBAS_RESOLVIDO   (7)
#define FL_JOGO_EM_ANDAMENTO  (8)

#define IN_ARVORE_LIGADA       (2)
#define IN_ARVORE_OK           (3)
#define IN_RPG_LIGADO          (4)
#define IN_RPG_OK              (5)
#define IN_BRASAO_LIGADO       (6)
#define IN_BRASAO_OK           (7)
#define IN_BOMBAS_LIGADA       (8)
#define IN_BOMBAS_OK           (9)
#define IN_BOMBAS_PORTA        (10)

#define RELE_LIGA_TV           (11)
#define RELE_PORTA_BOMBAS      (A4)
#define RELE_PORTA_ARMARIO     (A5)
#define RELE_PORTA_PRINCIPAL   (13)

#define IN_RESTART_ARVORE      (A3)
#define IN_RESTART_RPG         (A2)
#define IN_RESTART_BRASAO      (A1)
#define IN_RESTART_BOMBAS      (A0)

boolean arvore_ligada = false;
boolean rpg_ligado = false;
boolean brasao_ligado = false;
boolean bombas_ligada = false;

boolean arvore_ok = false;
boolean rpg_ok = false;
boolean brasao_ok = false;
boolean bombas_ok = false;
boolean bombas_porta = false;

boolean arvore_resolvida = false;
boolean rpg_resolvido = false;
boolean brasao_resolvido = false;
boolean bombas_resolvida = false;

#define ESTAGIO_INICIAL   (0)
#define ESTAGIO_ARVORE    (1)
#define ESTAGIO_RPG       (2)
#define ESTAGIO_BRASAO    (3)
#define ESTAGIO_BOMBAS    (4)
#define ESTAGIO_FINAL     (5)
#define ESTAGIO_NENHUM    (-1)

int estagio = ESTAGIO_NENHUM;
boolean bombas_blink = false;
boolean inicial_blink = false;
unsigned long hora_restart_bombas = 0;

boolean read_arvore_ok() {
  if (!digitalRead(IN_ARVORE_OK)) {
    delay(30);
    if (!digitalRead(IN_ARVORE_OK)) {
      return true;
    }
  }
  return false;
}

boolean read_rpg_ok() {
  if (!digitalRead(IN_RPG_OK)) {
    delay(30);
    if (!digitalRead(IN_RPG_OK)) {
      return true;
    }
  }
  return false;
}

boolean read_brasao_ok() {
  if (!digitalRead(IN_BRASAO_OK)) {
    delay(30);
    if (!digitalRead(IN_BRASAO_OK)) {
      return true;
    }
  }
  return false;
}

void reset_game() {

  // configura pinos
  pinMode(IN_ARVORE_LIGADA, INPUT); 
  pinMode(IN_ARVORE_OK, INPUT_PULLUP);
  pinMode(IN_RPG_LIGADO, INPUT);
  pinMode(IN_RPG_OK, INPUT_PULLUP);
  pinMode(IN_BRASAO_LIGADO, INPUT);
  pinMode(IN_BRASAO_OK, INPUT_PULLUP);
  pinMode(IN_BOMBAS_LIGADA, INPUT);
  pinMode(IN_BOMBAS_OK, INPUT_PULLUP);
  pinMode(IN_BOMBAS_PORTA, INPUT_PULLUP);
  pinMode(RELE_LIGA_TV, OUTPUT);
  pinMode(RELE_PORTA_BOMBAS, OUTPUT);
  pinMode(RELE_PORTA_ARMARIO, OUTPUT);
  pinMode(RELE_PORTA_PRINCIPAL, OUTPUT);
  pinMode(IN_RESTART_ARVORE, INPUT_PULLUP);
  pinMode(IN_RESTART_RPG, INPUT_PULLUP);
  pinMode(IN_RESTART_BRASAO, INPUT_PULLUP);
  pinMode(IN_RESTART_BOMBAS, INPUT_PULLUP);

  // zera variáveis de controle
  arvore_ligada = digitalRead(IN_ARVORE_LIGADA);  
  rpg_ligado = digitalRead(IN_RPG_LIGADO);  
  brasao_ligado = digitalRead(IN_BRASAO_LIGADO);  
  bombas_ligada = digitalRead(IN_BOMBAS_LIGADA);  

  arvore_ok = read_arvore_ok();
  rpg_ok = read_rpg_ok(); // !digitalRead(IN_RPG_OK);
  brasao_ok = read_brasao_ok();
  bombas_ok = !digitalRead(IN_BOMBAS_OK);
  bombas_porta = !digitalRead(IN_BOMBAS_PORTA);

  estagio_inicial();
}

void estagio_inicial() {
  estagio = ESTAGIO_INICIAL;

  arvore_resolvida = false;  
  rpg_resolvido = false;  
  brasao_resolvido = false;  
  bombas_resolvida = false;  

  desliga_tomada_tv();
  destrava_porta_bombas();
  destrava_porta_armario();
  destrava_porta_principal();

  leds[FL_ARVORE_OK] = COR_AZUL;
  leds[FL_RPG_OK] = COR_AZUL;
  leds[FL_BRASAO_OK] = COR_AZUL;
  leds[FL_BOMBAS_OK] = COR_AZUL;
  leds[FL_ARVORE_RESOLVIDO] = COR_AZUL;
  leds[FL_RPG_RESOLVIDO] = COR_AZUL;
  leds[FL_BRASAO_RESOLVIDO] = COR_AZUL;
  leds[FL_BOMBAS_RESOLVIDO] = COR_AZUL;
  leds[FL_JOGO_EM_ANDAMENTO] = COR_AZUL;

  inicial_blink = true;

}

void desliga_tomada_tv() {
  Serial.println("Desliga tomada da TV");
  arvore_resolvida = false;
  digitalWrite(RELE_LIGA_TV, HIGH); // sinal invertido
}

void liga_tomada_tv() {
  Serial.println("Liga tomada da TV");
  arvore_resolvida = true;
  digitalWrite(RELE_LIGA_TV, LOW); // sinal invertido
}

/*
void reset_rpg() {
  Serial.println("Reseta o RPG");
  digitalWrite(LED_RPG_OK, LOW);
  digitalWrite(OUTPUT_RESET_RPG, HIGH);
}
*/

void trava_porta_bombas() {
  Serial.println("Trava porta da armadilha");
  rpg_resolvido = false;
  digitalWrite(RELE_PORTA_BOMBAS, LOW);  // rele invertido
}

void destrava_porta_bombas() {
  Serial.println("Destrava porta da armadilha");
  rpg_resolvido = true;
  digitalWrite(RELE_PORTA_BOMBAS, HIGH); // rele invertido
}

void trava_porta_armario() {
  Serial.println("Trava porta do armário");
  brasao_resolvido = false;
  digitalWrite(RELE_PORTA_ARMARIO, LOW);
}

void destrava_porta_armario() {
  Serial.println("Destrava porta do armário");
  brasao_resolvido = true;
  digitalWrite(RELE_PORTA_ARMARIO, HIGH);
}

void trava_porta_principal() {
  Serial.println("Trava porta principal");
  bombas_resolvida = false;
  digitalWrite(RELE_PORTA_PRINCIPAL, LOW);
}

void destrava_porta_principal() {
  Serial.println("Destrava porta principal");
  bombas_resolvida = true;
  digitalWrite(RELE_PORTA_PRINCIPAL, HIGH);
}

void estagio_arvore() {
  inicial_blink = false;  

  leds[FL_ARVORE_OK] = arvore_ok ? COR_VERDE : COR_APAGADO;
  leds[FL_RPG_OK] = rpg_ok ? COR_VERDE : COR_APAGADO;
  leds[FL_BRASAO_OK] = brasao_ok ? COR_VERDE : COR_APAGADO;
  leds[FL_BOMBAS_OK] = COR_APAGADO;

  // leds de status dos estágios do jogo
  leds[FL_ARVORE_RESOLVIDO] = COR_AZUL;
  leds[FL_RPG_RESOLVIDO] = COR_APAGADO;
  leds[FL_BRASAO_RESOLVIDO] = COR_APAGADO;
  leds[FL_BOMBAS_RESOLVIDO] = COR_APAGADO;
  leds[FL_JOGO_EM_ANDAMENTO] = COR_VERDE;
  FastLED.show();

  // pisca o LED de resolvido rapidamente
  delay(300);
  leds[FL_ARVORE_RESOLVIDO] = COR_APAGADO;
  FastLED.show();
  delay(300);
  leds[FL_ARVORE_RESOLVIDO] = COR_AZUL;
  FastLED.show();
  delay(300);
  leds[FL_ARVORE_RESOLVIDO] = COR_APAGADO;
  FastLED.show();
  delay(300);
  leds[FL_ARVORE_RESOLVIDO] = COR_AZUL;
  FastLED.show();

  // força status do módulo para ser "falso", assim ele processa corretamente se o sinal já estiver ativo
  arvore_ok = false;

  estagio = ESTAGIO_ARVORE;
  Serial.println("Estágio ARVORE");
  desliga_tomada_tv();
  trava_porta_bombas();
  trava_porta_armario();
  trava_porta_principal();
}

void estagio_rpg() {
  inicial_blink = false;  

  leds[FL_ARVORE_OK] = arvore_ok ? COR_VERDE : COR_APAGADO;
  leds[FL_RPG_OK] = rpg_ok ? COR_VERDE : COR_APAGADO;
  leds[FL_BRASAO_OK] = brasao_ok ? COR_VERDE : COR_APAGADO;
  leds[FL_BOMBAS_OK] = COR_VERDE;

  // leds de status dos estágios do jogo
  leds[FL_ARVORE_RESOLVIDO] = COR_VERDE;
  leds[FL_RPG_RESOLVIDO] = COR_AZUL;
  leds[FL_BRASAO_RESOLVIDO] = COR_APAGADO;
  leds[FL_BOMBAS_RESOLVIDO] = COR_APAGADO;
  leds[FL_JOGO_EM_ANDAMENTO] = COR_VERDE;
  FastLED.show();

  // força status do módulo para ser "falso", assim ele processa corretamente se o sinal já estiver ativo
  rpg_ok = false;

  estagio = ESTAGIO_RPG;
  Serial.println("Estágio RPG");
  liga_tomada_tv();
  trava_porta_bombas();
  trava_porta_armario();
  trava_porta_principal();
}

void estagio_will() {
  inicial_blink = false;  

  leds[FL_ARVORE_OK] = arvore_ok ? COR_VERDE : COR_APAGADO;
  leds[FL_RPG_OK] = rpg_ok ? COR_VERDE : COR_APAGADO;
  leds[FL_BRASAO_OK] = brasao_ok ? COR_VERDE : COR_APAGADO;
  leds[FL_BOMBAS_OK] = COR_APAGADO;

  // leds de status dos estágios do jogo
  leds[FL_ARVORE_RESOLVIDO] = COR_VERDE;
  leds[FL_RPG_RESOLVIDO] = COR_VERDE;
  leds[FL_BRASAO_RESOLVIDO] = COR_AZUL;
  leds[FL_BOMBAS_RESOLVIDO] = COR_APAGADO;
  leds[FL_JOGO_EM_ANDAMENTO] = COR_VERDE;
  FastLED.show();

  // força status do módulo para ser "falso", assim ele processa corretamente se o sinal já estiver ativo
  brasao_ok = false;

  estagio = ESTAGIO_BRASAO;
  Serial.println("Estágio BRASAO");
  liga_tomada_tv();
  destrava_porta_bombas();
  trava_porta_armario();
  trava_porta_principal();
}

void estagio_bombas() {
  inicial_blink = false;  
  /*
  digitalWrite(LED_RPG_OK, rpg_ok);  
  digitalWrite(LED_BRASAO_OK, brasao_ok);  
  digitalWrite(LED_BOMBAS_OK, LOW);  
  */
  leds[FL_ARVORE_OK] = arvore_ok ? COR_VERDE : COR_APAGADO;
  leds[FL_RPG_OK] = rpg_ok ? COR_VERDE : COR_APAGADO;
  leds[FL_BRASAO_OK] = brasao_ok ? COR_VERDE : COR_APAGADO;
  leds[FL_BOMBAS_OK] = COR_APAGADO;

  // leds de status dos estágios do jogo
  leds[FL_ARVORE_RESOLVIDO] = COR_VERDE;
  leds[FL_RPG_RESOLVIDO] = COR_VERDE;
  leds[FL_BRASAO_RESOLVIDO] = COR_VERDE;
  leds[FL_BOMBAS_RESOLVIDO] = COR_AZUL;
  leds[FL_JOGO_EM_ANDAMENTO] = COR_VERDE;
  FastLED.show();

  // força status do módulo para ser "falso", assim ele processa corretamente se o sinal já estiver ativo
  bombas_ok = false;
  bombas_porta = false;

  estagio = ESTAGIO_BOMBAS;
  Serial.println("Estágio BOMBAS");
  liga_tomada_tv();
  destrava_porta_bombas();
  destrava_porta_armario();
  trava_porta_principal();
}

void estagio_final() {  
  estagio = ESTAGIO_FINAL;
  desliga_tomada_tv();
  // quando as bombas armam, a porta deve permanecer travada
  trava_porta_bombas();
  destrava_porta_armario();
  destrava_porta_principal();

  // leds de status dos estágios do jogo
  leds[FL_ARVORE_RESOLVIDO] = COR_AZUL;
  leds[FL_RPG_RESOLVIDO] = COR_AZUL;
  leds[FL_BRASAO_RESOLVIDO] = COR_AZUL;
  leds[FL_BOMBAS_RESOLVIDO] = COR_AZUL;
  leds[FL_JOGO_EM_ANDAMENTO] = COR_AZUL;
  FastLED.show();

  inicial_blink = true;  
}

void test_game() {
  delay(2000);
  liga_tomada_tv(); delay(500);
  trava_porta_bombas(); delay(500);
  trava_porta_armario(); delay(500);
  trava_porta_principal(); delay(500);
  delay(2000);
  desliga_tomada_tv(); delay(500);
  destrava_porta_bombas(); delay(500);
  destrava_porta_armario(); delay(500);
  destrava_porta_principal(); delay(500);
  delay(2000);
  reset_game();
}

boolean old_arvore_ok = false;
boolean old_rpg_ok = false;
boolean old_brasao_ok = false;
boolean old_bombas_ok = false;
boolean old_bombas_porta = false;

boolean old_arvore_ligada = false;
boolean old_rpg_ligado = false;
boolean old_brasao_ligado = false;
boolean old_bombas_ligada = false;

boolean arvore_restart_pressed = false;
boolean rpg_restart_pressed = false;
boolean brasao_restart_pressed = false;
boolean bombas_restart_pressed = false;

boolean atualiza_status() {

  // save old status
  old_arvore_ligada = arvore_ligada;
  old_rpg_ligado = rpg_ligado;
  old_brasao_ligado = brasao_ligado;
  old_bombas_ligada = bombas_ligada;

  old_arvore_ok = arvore_ok;
  old_rpg_ok = rpg_ok;
  old_brasao_ok = brasao_ok;
  old_bombas_ok = bombas_ok;
  old_bombas_porta = bombas_porta;

  // read new status; signals that are true when LOW are inverted on read to simplify logic
  arvore_ligada = digitalRead(IN_ARVORE_LIGADA);  
  rpg_ligado = digitalRead(IN_RPG_LIGADO);  
  brasao_ligado = digitalRead(IN_BRASAO_LIGADO);  
  bombas_ligada = digitalRead(IN_BOMBAS_LIGADA);  

  // botão de bypass não pode ser sinal elétrico; precisa ser um io separado, porque
  // senão eu desligo o módulo e ele para de funcionar pra passar o resultado
  if (true || arvore_ligada) { arvore_ok = read_arvore_ok(); } else { arvore_ok = false; }
  if (true || rpg_ligado) { rpg_ok = read_rpg_ok(); } else { rpg_ok = false; }
  if (true || brasao_ligado) {  brasao_ok = read_brasao_ok(); } else { brasao_ok = false; }
  if (true || bombas_ligada) {
    bombas_ok = !digitalRead(IN_BOMBAS_OK);
    bombas_porta = !digitalRead(IN_BOMBAS_PORTA);
  }
  else {
    bombas_ok = false;
    bombas_porta = !digitalRead(IN_BOMBAS_PORTA);
  }

  // returns true if anything changed
  return (
    (old_arvore_ok != arvore_ok) ||
    (old_rpg_ok != rpg_ok) ||
    (old_brasao_ok != brasao_ok) ||
    (old_bombas_ok != bombas_ok) ||
    (old_bombas_porta != bombas_porta)
    );
}

void imprime_status() {
  Serial.println();
  Serial.print("STATUS ("); Serial.print(long(millis()/1000)); Serial.println(")");
  Serial.print("Estagio:"); Serial.print(int(estagio)); Serial.println("");

  Serial.print("Árvore: ");
  Serial.print(arvore_ligada ? "[LIGADO]" : "[DESLIGADO]"); Serial.print(" ");
  Serial.print(arvore_ok ? "[OK]" : "[NÃO OK]"); Serial.print(" ");
  Serial.println(arvore_resolvida ? "[RESOLVIDO]" : "[NÃO RESOLVIDO]");

  Serial.print("RPG: ");
  Serial.print(rpg_ligado ? "[LIGADO]" : "[DESLIGADO]"); Serial.print(" ");
  Serial.print(rpg_ok ? "[OK]" : "[NÃO OK]"); Serial.print(" ");
  Serial.println(rpg_resolvido ? "[RESOLVIDO]" : "[NÃO RESOLVIDO]");

  Serial.print("Will: ");
  Serial.print(brasao_ligado ? "[LIGADO]" : "[DESLIGADO]"); Serial.print(" ");
  Serial.print(brasao_ok ? "[OK]" : "[NÃO OK]"); Serial.print(" ");
  Serial.println(brasao_resolvido ? "[RESOLVIDO]" : "[NÃO RESOLVIDO]");

  Serial.print("Armadilha: ");
  Serial.print(bombas_ligada ? "[LIGADO]" : "[DESLIGADO]"); Serial.print(" ");
  Serial.print(bombas_ok ? "[OK]" : "[NÃO OK]"); Serial.print(" ");
  Serial.print(bombas_porta ? "[FECHADA]" : "[ABERTA]"); Serial.print(" ");
  Serial.println(bombas_resolvida ? "[RESOLVIDO]" : "[NÃO RESOLVIDO]");
}

void setup() {
  // inicialização normal
  Serial.begin(115200);
  Serial.println();
  Serial.println();
  Serial.println();
  Serial.println("BHESCAPE STRANGER THINGS");
  Serial.println("NOVO JOGO");

  // delay de segurança, pra não entrar de cara atualizando a fita de LEDs etc
  delay(500);

  // setup FASTLED
  Serial.println("Configurando LEDs");
  FastLED.addLeds<WS2811, LEDS_DATA_PIN>(leds, NUM_LEDS);
  delay(50);

  reset_game();
}

long last_loop = 0;

void loop() {
  // Serial.println("LOOP");
  // Serial.println(analogRead(IN_RESTART_BRASAO));

  // imprime um ponto a cada 5s pra ver se o loop está rodando
  long this_loop = long(millis()/5000);
  if (this_loop > last_loop) {
    last_loop = this_loop;
    Serial.print(".");
  }

  // leds[FL_ARVORE_OK] = random(16777215);
  // leds[FL_ARVORE_OK] = (random(192)*256*256) + (random(192)*256) + (random(128));
  // leds[FL_ARVORE_OK] += 71;
  // Serial.println("apresentando LEDs");
  // Serial.println(leds[FL_ARVORE_OK]);
  // FastLED.show(); 
  // delay(50);

  // delay(300);
  // return; // pula o resto do código durante essa fase de teste do loop,

  if (inicial_blink) {
    unsigned long blink_time;
    blink_time = millis()/1000;
    if ((blink_time % 2) == 0) {
      leds[FL_ARVORE_OK] = COR_AMARELO;
      leds[FL_RPG_OK] = COR_AMARELO;
      leds[FL_BRASAO_OK] = COR_AMARELO;
      leds[FL_BOMBAS_OK] = COR_AMARELO;
      Serial.print("+");
    }
    else {
      leds[FL_ARVORE_OK] = COR_APAGADO;
      leds[FL_RPG_OK] = COR_APAGADO;
      leds[FL_BRASAO_OK] = COR_APAGADO;
      leds[FL_BOMBAS_OK] = COR_APAGADO;
      Serial.print("-");
    }
  }
  else if (bombas_blink) {
    unsigned long blink_time;
    blink_time = millis()/1000;
    if ((blink_time % 2) == 0) {
      leds[FL_BOMBAS_OK] = COR_VERDE;
    }
    else {
      leds[FL_BOMBAS_OK] = COR_APAGADO;
    }
  }
  FastLED.show(); 

  boolean status_changed;

  status_changed = atualiza_status();
  if (status_changed) {
    imprime_status();
  }

  // ARVORE GENEALOGICA
  if (arvore_ok != old_arvore_ok) {
    if (arvore_ok) {
      Serial.println("Árvore OK");
      if (estagio == ESTAGIO_ARVORE) {
        leds[FL_ARVORE_OK] = COR_VERDE;
        FastLED.show(); 
        Serial.println("Árvore RESOLVIDA");
        estagio_rpg();
      }
      else {
        Serial.println("Árvore ok descartada (estágio errado)");      
      }
    }
    else {
      Serial.println("Árvore NÃO OK");
      leds[FL_ARVORE_OK] = COR_APAGADO;
      FastLED.show(); 
    }
  }

  // RPG
  if (rpg_ok != old_rpg_ok) {
    if (rpg_ok) {
      Serial.println("RPG OK");
      if (estagio == ESTAGIO_RPG) {
        leds[FL_RPG_OK] = COR_VERDE;
        FastLED.show(); 
        Serial.println("RPG RESOLVIDO");
        estagio_will();
      }
      else {
        Serial.println("RPG ok descartado (estágio errado)");      
      }
    }
    else {
      Serial.println("RPG NÃO OK");
    leds[FL_RPG_OK, COR_APAGADO];
    FastLED.show(); 
    }
  }

  // BRASAO
  if (brasao_ok != old_brasao_ok) {
    if (brasao_ok) {
      Serial.println("Will OK");
      if (estagio == ESTAGIO_BRASAO) {
        leds[FL_BRASAO_OK] = COR_VERDE;
        Serial.println("Will RESOLVIDO");
        estagio_bombas();
      }
      else {
        Serial.println("Will ok descartado (estágio errado)");
      }
    }
    else {
      Serial.println("Will NÃO OK");
      leds[FL_BRASAO_OK, COR_APAGADO];  
      FastLED.show(); 
    }
  }

  // BOMBAS
  if ((bombas_ok != old_bombas_ok) || (bombas_porta != old_bombas_porta)) {
    if (bombas_ok) {
      if (estagio == ESTAGIO_BOMBAS) {
        if (bombas_porta) {
          bombas_blink = false;
          Serial.println("Armadilha OK + Porta FECHADA");
          leds[FL_BOMBAS_OK] = COR_VERDE; 
          Serial.println("BOMBAS RESOLVIDA");
          estagio_final();
        }
        else {
          Serial.println("Armadilha OK + Porta ABERTA");
          bombas_blink = true;
          // liga a trava da armadilha quando as bombas são armadas
          trava_porta_bombas();
        }
      }
      else {
        Serial.println("Árvore ok descartada (estágio errado)");      
      }
    }
    else {
      Serial.println("Armadilha NÃO OK");
      leds[FL_BOMBAS_OK] = COR_APAGADO;  
      bombas_blink = false;
    }
  }

  if (digitalRead(IN_RESTART_ARVORE) == LOW) {
    // algoritmo simples de debounce
    delay(50);
    if (digitalRead(IN_RESTART_ARVORE) == LOW) {
      Serial.println("-----------------------");
      Serial.println("RESTART ARVORE PRESSIONADO");
      arvore_restart_pressed = true;
    }
  }
  if (arvore_restart_pressed && (digitalRead(IN_RESTART_ARVORE) == HIGH)) {
    // algoritmo simples de debounce
    delay(50);
    if (digitalRead(IN_RESTART_ARVORE) == HIGH) {
      Serial.println("RESTART ARVORE SOLTO");
      arvore_restart_pressed = false;
      estagio_arvore();
    }
  }

  if (digitalRead(IN_RESTART_RPG) == LOW) {
    // algoritmo simples de debounce
    delay(50);
    if ((digitalRead(IN_RESTART_RPG) == LOW) && (!rpg_restart_pressed)) {
      Serial.println("-----------------------");
      Serial.println("RESTART RPG PRESSIONADO");
      rpg_restart_pressed = true;
    }
  }
  if (rpg_restart_pressed && (digitalRead(IN_RESTART_RPG) == HIGH)) {
    // algoritmo simples de debounce
    delay(50);
    if (digitalRead(IN_RESTART_RPG) == HIGH) {
      Serial.println("RESTART RPG SOLTO");
      rpg_restart_pressed = false;
      estagio_rpg();
    }
  }

  if (analogRead(IN_RESTART_BRASAO) < 120) {
    // algoritmo simples de debounce
    delay(50);
    if (analogRead(IN_RESTART_BRASAO) < 120) {
      Serial.println();
      Serial.println("RESTART BRASAO PRESSIONADO");
      brasao_restart_pressed = true;
    }
  }
  if (brasao_restart_pressed && (analogRead(IN_RESTART_BRASAO) >= 120)) {
    // algoritmo simples de debounce
    delay(50);
    if (analogRead(IN_RESTART_BRASAO) >= 120) {
      Serial.println("RESTART BRASAO SOLTO");
      brasao_restart_pressed = false;
      estagio_will();
    }
  }

  if (!bombas_restart_pressed && (analogRead(IN_RESTART_BOMBAS) < 120)) {
    // algoritmo simples de debounce
    delay(50);
    if (analogRead(IN_RESTART_BOMBAS) < 120) {
      Serial.println();
      Serial.println("RESTART BOMBAS PRESSIONADO");
      bombas_restart_pressed = true;
      hora_restart_bombas = millis();
    }
  } 
  else if (bombas_restart_pressed && (analogRead(IN_RESTART_BOMBAS) >= 120)) {
    // algoritmo simples de debounce
    delay(50);
    if (analogRead(IN_RESTART_BOMBAS) >= 120) {
      Serial.println("RESTART BOMBAS SOLTO");
      bombas_restart_pressed = false;
      if ((millis() - hora_restart_bombas) <= 2000) {
        Serial.println("RESTART BOMBAS < 2000");
        hora_restart_bombas = 0;
        estagio_bombas();
      }
      else {
        Serial.println("RESTART BOMBAS > 2000");
        hora_restart_bombas = 0;
        estagio_final();
      }
    }
  }

  String input;
  if (Serial.available()) {
      input = Serial.readStringUntil('\n');
      input.trim();
      if (input.equalsIgnoreCase("STATUS")) {
        imprime_status();
      }
      else if (input.equalsIgnoreCase("RESTART")) {
        Serial.println("Reiniciando o jogo");
        reset_game();
      }
      else if (input.equalsIgnoreCase("LIGA TV")) {
        liga_tomada_tv();
      }
      else if (input.equalsIgnoreCase("DESLIGA TV")) {
        desliga_tomada_tv();
      }
      else if (input.equalsIgnoreCase("ABRIR SALA")) {
        destrava_porta_principal();
      }
      else if (input.equalsIgnoreCase("FECHAR SALA")) {
        trava_porta_principal();
      }
      else if (input.equalsIgnoreCase("ABRIR BOMBAS")) {
        destrava_porta_bombas();
      }
      else if (input.equalsIgnoreCase("FECHAR BOMBAS")) {
        trava_porta_bombas();
      }
      else if (input.equalsIgnoreCase("ABRIR ARMARIO")) {
        destrava_porta_armario();
      }
      else if (input.equalsIgnoreCase("FECHAR ARMARIO")) {
        trava_porta_armario();
      }
      else if (input.equalsIgnoreCase("A6")) {
         Serial.println("Pino A6: ");
         for (int i = 0; i<30; i++) {
           Serial.print(analogRead(A6));
           Serial.print(", ");
           delay(100);
         }
         Serial.println();
      }
      else if (input.equalsIgnoreCase("TEST")) {
         Serial.println("TEST");
         test_game();
      }
      else {
        Serial.print("Comando não reconhecido: <");
        Serial.print(input); Serial.print("> "); Serial.println(input.length());
      }
  }
 
  delay(100);
}
