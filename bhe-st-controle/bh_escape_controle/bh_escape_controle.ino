// (C) 2021 FAZ MAKERSPACE
// CAIXA DE CONTROLE BH ESCAPE
// SALA STRANGER THINGS
//
// pins

#define IN_ARVORE_LIGADA       (2)
#define IN_ARVORE_OK           (3)
// #define LED_ARVORE_OK          (4)
#define IN_RPG_LIGADO          (5)
#define IN_RPG_OK              (6)
#define LED_RPG_OK             (7)
#define IN_WILL_LIGADO         (8)
#define IN_WILL_OK             (9)
#define LED_WILL_OK            (10)
#define IN_ARMADILHA_LIGADA    (11)
#define IN_ARMADILHA_OK        (12)
#define IN_ARMADILHA_PORTA     (4)
#define LED_ARMADILHA_OK       (13)
#define RELE_LIGA_TV           (A0)
#define RELE_PORTA_ARMADILHA   (A1)
#define RELE_PORTA_ARMARIO     (A2)
#define RELE_PORTA_PRINCIPAL   (A3)

#define IN_RESTART_ARVORE      (A4)
#define IN_RESTART_RPG         (A5)
#define IN_RESTART_WILL        (A6)
#define IN_RESTART_ARMADILHA   (A7)

boolean arvore_ligada = false;
boolean rpg_ligado = false;
boolean will_ligado = false;
boolean armadilha_ligada = false;

boolean arvore_ok = false;
boolean rpg_ok = false;
boolean will_ok = false;
boolean armadilha_ok = false;
boolean armadilha_porta = false;

boolean arvore_resolvida = false;
boolean rpg_resolvido = false;
boolean will_resolvido = false;
boolean armadilha_resolvida = false;

#define ESTAGIO_INICIAL   (0)
#define ESTAGIO_ARVORE    (1)
#define ESTAGIO_RPG       (2)
#define ESTAGIO_WILL      (3)
#define ESTAGIO_ARMADILHA (4)
#define ESTAGIO_FINAL     (5)
#define ESTAGIO_NENHUM   (-1)

int estagio = ESTAGIO_NENHUM;
boolean armadilha_blink = false;
boolean inicial_blink = false;
unsigned long hora_restart_armadilha = 0;

boolean read_will_ok() {
  if (!digitalRead(IN_WILL_OK)) {
    delay(30);
    if (!digitalRead(IN_WILL_OK)) {
      return true;
    }
  }
  return false;
}

void reset_game() {

  // configura pinos
  pinMode(IN_ARVORE_LIGADA, INPUT); // pulldown?
  pinMode(IN_ARVORE_OK, INPUT_PULLUP);
  //pinMode(LED_ARVORE_OK, OUTPUT);
  pinMode(IN_RPG_LIGADO, INPUT);
  pinMode(IN_RPG_OK, INPUT_PULLUP);
  pinMode(LED_RPG_OK, OUTPUT);
  pinMode(IN_WILL_LIGADO, INPUT);
  pinMode(IN_WILL_OK, INPUT_PULLUP);
  pinMode(LED_WILL_OK, OUTPUT);
  pinMode(IN_ARMADILHA_LIGADA, INPUT);
  pinMode(IN_ARMADILHA_OK, INPUT_PULLUP);
  pinMode(IN_ARMADILHA_PORTA, INPUT_PULLUP);
  pinMode(LED_ARMADILHA_OK, OUTPUT);
  pinMode(RELE_LIGA_TV, OUTPUT);
  pinMode(RELE_PORTA_ARMADILHA, OUTPUT);
  pinMode(RELE_PORTA_ARMARIO, OUTPUT);
  pinMode(RELE_PORTA_PRINCIPAL, OUTPUT);
  pinMode(IN_RESTART_ARVORE, INPUT_PULLUP);
  pinMode(IN_RESTART_RPG, INPUT_PULLUP);
  pinMode(IN_RESTART_WILL, INPUT_PULLUP);
  pinMode(IN_RESTART_ARMADILHA, INPUT_PULLUP);

  estagio = ESTAGIO_INICIAL;

  // zera variáveis de controle
  arvore_ligada = digitalRead(IN_ARVORE_LIGADA);  
  rpg_ligado = digitalRead(IN_RPG_LIGADO);  
  will_ligado = digitalRead(IN_WILL_LIGADO);  
  armadilha_ligada = digitalRead(IN_ARMADILHA_LIGADA);  

  arvore_ok = !digitalRead(IN_ARVORE_OK);
  rpg_ok = !digitalRead(IN_RPG_OK);
  will_ok = read_will_ok();
  armadilha_ok = !digitalRead(IN_ARMADILHA_OK);
  armadilha_porta = !digitalRead(IN_ARMADILHA_PORTA);

  arvore_resolvida = false;  
  digitalWrite(RELE_LIGA_TV, LOW);
  rpg_resolvido = false;  
  digitalWrite(RELE_PORTA_ARMADILHA, LOW);
  will_resolvido = false;  
  digitalWrite(RELE_PORTA_ARMARIO, LOW);
  armadilha_resolvida = false;  
  digitalWrite(RELE_PORTA_PRINCIPAL, LOW);

  inicial_blink = true;
}

void desliga_tomada_tv() {
  Serial.println("Desliga tomada da TV");
  arvore_resolvida = false;
  digitalWrite(RELE_LIGA_TV, LOW);
}

void liga_tomada_tv() {
  Serial.println("Liga tomada da TV");
  arvore_resolvida = true;
  digitalWrite(RELE_LIGA_TV, HIGH);
}

/*
void reset_rpg() {
  Serial.println("Reseta o RPG");
  digitalWrite(LED_RPG_OK, LOW);
  digitalWrite(OUTPUT_RESET_RPG, HIGH);
}
*/

void trava_porta_armadilha() {
  Serial.println("Trava porta da armadilha");
  rpg_resolvido = false;
  digitalWrite(RELE_PORTA_ARMADILHA, LOW);
}

void destrava_porta_armadilha() {
  Serial.println("Destrava porta da armadilha");
  rpg_resolvido = true;
  digitalWrite(RELE_PORTA_ARMADILHA, HIGH);
}

void trava_porta_armario() {
  Serial.println("Trava porta do armário");
  will_resolvido = false;
  digitalWrite(RELE_PORTA_ARMARIO, LOW);
}

void destrava_porta_armario() {
  Serial.println("Destrava porta do armário");
  will_resolvido = true;
  digitalWrite(RELE_PORTA_ARMARIO, HIGH);
}

void trava_porta_principal() {
  Serial.println("Trava porta principal");
  armadilha_resolvida = false;
  digitalWrite(RELE_PORTA_PRINCIPAL, LOW);
}

void destrava_porta_principal() {
  Serial.println("Destrava porta principal");
  armadilha_resolvida = true;
  digitalWrite(RELE_PORTA_PRINCIPAL, HIGH);
}

void estagio_arvore() {
  inicial_blink = false;  
  digitalWrite(LED_RPG_OK, rpg_ok);  
  digitalWrite(LED_WILL_OK, will_ok);  
  digitalWrite(LED_ARMADILHA_OK, LOW);  

  estagio = ESTAGIO_ARVORE;
  Serial.println("Estágio ARVORE");
  desliga_tomada_tv();
  trava_porta_armadilha();
  trava_porta_armario();
  trava_porta_principal();
}

void estagio_rpg() {
  inicial_blink = false;  
  digitalWrite(LED_RPG_OK, rpg_ok);  
  digitalWrite(LED_WILL_OK, will_ok);  
  digitalWrite(LED_ARMADILHA_OK, LOW);  

  estagio = ESTAGIO_RPG;
  Serial.println("Estágio RPG");
  liga_tomada_tv();
  trava_porta_armadilha();
  trava_porta_armario();
  trava_porta_principal();
}

void estagio_will() {
  inicial_blink = false;  
  digitalWrite(LED_RPG_OK, rpg_ok);  
  digitalWrite(LED_WILL_OK, will_ok);  
  digitalWrite(LED_ARMADILHA_OK, LOW);  

  estagio = ESTAGIO_WILL;
  Serial.println("Estágio WILL");
  liga_tomada_tv();
  destrava_porta_armadilha();
  trava_porta_armario();
  trava_porta_principal();
}

void estagio_armadilha() {
  inicial_blink = false;  
  digitalWrite(LED_RPG_OK, rpg_ok);  
  digitalWrite(LED_WILL_OK, will_ok);  
  digitalWrite(LED_ARMADILHA_OK, LOW);  

  estagio = ESTAGIO_ARMADILHA;
  Serial.println("Estágio ARMADILHA");
  liga_tomada_tv();
  destrava_porta_armadilha();
  destrava_porta_armario();
  trava_porta_principal();
}

void estagio_final() {  
  estagio = ESTAGIO_FINAL;
  desliga_tomada_tv();
  destrava_porta_armadilha();
  destrava_porta_armario();
  destrava_porta_principal();
  inicial_blink = true;  
}

void test_game() {
  // digitalWrite(LED_ARVORE_OK, HIGH); delay(500);
  // digitalWrite(LED_ARVORE_OK, LOW); delay(500);
  digitalWrite(LED_RPG_OK, HIGH); delay(500);
  digitalWrite(LED_RPG_OK, LOW); delay(500);
  digitalWrite(LED_WILL_OK, HIGH); delay(500);
    digitalWrite(LED_WILL_OK, LOW); delay(500);
  digitalWrite(LED_ARMADILHA_OK, HIGH); delay(500);
  digitalWrite(LED_ARMADILHA_OK, LOW); delay(500);
  delay(2000);
  liga_tomada_tv(); delay(500);
  trava_porta_armadilha(); delay(500);
  trava_porta_armario(); delay(500);
  trava_porta_principal(); delay(500);
  delay(2000);
  desliga_tomada_tv(); delay(500);
  destrava_porta_armadilha(); delay(500);
  destrava_porta_armario(); delay(500);
  destrava_porta_principal(); delay(500);
  delay(2000);
  reset_game();
}

boolean old_arvore_ok = false;
boolean old_rpg_ok = false;
boolean old_will_ok = false;
boolean old_armadilha_ok = false;
boolean old_armadilha_porta = false;

boolean old_arvore_ligada = false;
boolean old_rpg_ligado = false;
boolean old_will_ligado = false;
boolean old_armadilha_ligada = false;

boolean arvore_restart_pressed = false;
boolean rpg_restart_pressed = false;
boolean will_restart_pressed = false;
boolean armadilha_restart_pressed = false;

boolean atualiza_status() {

  // save old status
  old_arvore_ligada = arvore_ligada;
  old_rpg_ligado = rpg_ligado;
  old_will_ligado = will_ligado;
  old_armadilha_ligada = armadilha_ligada;

  old_arvore_ok = arvore_ok;
  old_rpg_ok = rpg_ok;
  old_will_ok = will_ok;
  old_armadilha_ok = armadilha_ok;
  old_armadilha_porta = armadilha_porta;

  // read new status; signals that are true when LOW are inverted on read to simplify logic
  arvore_ligada = digitalRead(IN_ARVORE_LIGADA);  
  rpg_ligado = digitalRead(IN_RPG_LIGADO);  
  will_ligado = digitalRead(IN_WILL_LIGADO);  
  armadilha_ligada = digitalRead(IN_ARMADILHA_LIGADA);  

  // botão de bypass não pode ser sinal elétrico; precisa ser um io separado, porque
  // senão eu desligo o módulo e ele para de funcionar pra passar o resultado
  if (true || arvore_ligada) { arvore_ok = !digitalRead(IN_ARVORE_OK); } else { arvore_ok = false; }
  if (true || rpg_ligado) { rpg_ok = !digitalRead(IN_RPG_OK); } else { rpg_ok = false; }
  if (true || will_ligado) {  will_ok = read_will_ok(); } else { will_ok = false; }
  if (true || armadilha_ligada) {
    armadilha_ok = !digitalRead(IN_ARMADILHA_OK);
    armadilha_porta = !digitalRead(IN_ARMADILHA_PORTA);
  }
  else {
    armadilha_ok = false;
    armadilha_porta = !digitalRead(IN_ARMADILHA_PORTA);
  }

  // returns true if anything changed
  return (
    (old_arvore_ok != arvore_ok) ||
    (old_rpg_ok != rpg_ok) ||
    (old_will_ok != will_ok) ||
    (old_armadilha_ok != armadilha_ok) ||
    (old_armadilha_porta != armadilha_porta)
    );
}

void imprime_status() {
  Serial.println();
  Serial.print("STATUS ("); Serial.print(long(millis()/1000)); Serial.println(")");

  Serial.print("Árvore: ");
  Serial.print(arvore_ligada ? "[LIGADO]" : "[DESLIGADO]"); Serial.print(" ");
  Serial.print(arvore_ok ? "[OK]" : "[NÃO OK]"); Serial.print(" ");
  Serial.println(arvore_resolvida ? "[RESOLVIDO]" : "[NÃO RESOLVIDO]");

  Serial.print("RPG: ");
  Serial.print(rpg_ligado ? "[LIGADO]" : "[DESLIGADO]"); Serial.print(" ");
  Serial.print(rpg_ok ? "[OK]" : "[NÃO OK]"); Serial.print(" ");
  Serial.println(rpg_resolvido ? "[RESOLVIDO]" : "[NÃO RESOLVIDO]");

  Serial.print("Will: ");
  Serial.print(will_ligado ? "[LIGADO]" : "[DESLIGADO]"); Serial.print(" ");
  Serial.print(will_ok ? "[OK]" : "[NÃO OK]"); Serial.print(" ");
  Serial.println(will_resolvido ? "[RESOLVIDO]" : "[NÃO RESOLVIDO]");

  Serial.print("Armadilha: ");
  Serial.print(armadilha_ligada ? "[LIGADO]" : "[DESLIGADO]"); Serial.print(" ");
  Serial.print(armadilha_ok ? "[OK]" : "[NÃO OK]"); Serial.print(" ");
  Serial.print(armadilha_porta ? "[FECHADA]" : "[ABERTA]"); Serial.print(" ");
  Serial.println(armadilha_resolvida ? "[RESOLVIDO]" : "[NÃO RESOLVIDO]");
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
  // Serial.println(analogRead(IN_RESTART_WILL));

  if (inicial_blink) {
    unsigned long blink_time;
    blink_time = millis()/1000;
    if ((blink_time % 2) == 0) {
      digitalWrite(LED_RPG_OK, HIGH);  
      digitalWrite(LED_WILL_OK, HIGH);  
      digitalWrite(LED_ARMADILHA_OK, HIGH);  
    }
    else {
      digitalWrite(LED_RPG_OK, LOW);  
      digitalWrite(LED_WILL_OK, LOW);  
      digitalWrite(LED_ARMADILHA_OK, LOW);  
    }
  }
  else if (armadilha_blink) {
    unsigned long blink_time;
    blink_time = millis()/1000;
    if ((blink_time % 2) == 0) {
      digitalWrite(LED_ARMADILHA_OK, HIGH);  
    }
    else {
      digitalWrite(LED_ARMADILHA_OK, LOW);  
    }
  }

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
        // digitalWrite(LED_ARVORE_OK, HIGH);
        Serial.println("Árvore RESOLVIDA");
        estagio_rpg();
      }
      else {
        Serial.println("Árvore ok descartada (estágio errado)");      
      }
    }
    else {
      Serial.println("Árvore NÃO OK");
      // digitalWrite(LED_ARVORE_OK, LOW);
    }
  }

  // RPG
  if (rpg_ok != old_rpg_ok) {
    if (rpg_ok) {
      Serial.println("RPG OK");
      if (estagio == ESTAGIO_RPG) {
        digitalWrite(LED_RPG_OK, HIGH);
        Serial.println("RPG RESOLVIDO");
        estagio_will();
      }
      else {
        Serial.println("RPG ok descartado (estágio errado)");      
      }
    }
    else {
      Serial.println("RPG NÃO OK");
      digitalWrite(LED_RPG_OK, LOW);
    }
  }

  // WILL
  if (will_ok != old_will_ok) {
    if (will_ok) {
      Serial.println("Will OK");
      if (estagio == ESTAGIO_WILL) {
        digitalWrite(LED_WILL_OK, HIGH);
        Serial.println("Will RESOLVIDO");
        estagio_armadilha();
      }
      else {
        Serial.println("Will ok descartado (estágio errado)");
      }
    }
    else {
      Serial.println("Will NÃO OK");
      digitalWrite(LED_WILL_OK, LOW);
    }
  }

  // ARMADILHA
  if ((armadilha_ok != old_armadilha_ok) || (armadilha_porta != old_armadilha_porta)) {
    if (armadilha_ok) {
      if (estagio == ESTAGIO_ARMADILHA) {
        if (armadilha_porta) {
          armadilha_blink = false;
          Serial.println("Armadilha OK + Porta FECHADA");
          digitalWrite(LED_ARMADILHA_OK, HIGH);
          Serial.println("ARMADILHA RESOLVIDA");
          estagio_final();
        }
        else {
          Serial.println("Armadilha OK + Porta FECHADA");
          armadilha_blink = true;
        }
      }
      else {
        Serial.println("Árvore ok descartada (estágio errado)");      
      }
    }
    else {
      Serial.println("Armadilha NÃO OK");
      digitalWrite(LED_ARMADILHA_OK, LOW);
      armadilha_blink = false;
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

  if (analogRead(IN_RESTART_WILL) < 120) {
    // algoritmo simples de debounce
    delay(50);
    if (analogRead(IN_RESTART_WILL) < 120) {
      Serial.println();
      Serial.println("RESTART WILL PRESSIONADO");
      will_restart_pressed = true;
    }
  }
  if (will_restart_pressed && (analogRead(IN_RESTART_WILL) >= 120)) {
    // algoritmo simples de debounce
    delay(50);
    if (analogRead(IN_RESTART_WILL) >= 120) {
      Serial.println("RESTART WILL SOLTO");
      will_restart_pressed = false;
      estagio_will();
    }
  }

  if (!armadilha_restart_pressed && (analogRead(IN_RESTART_ARMADILHA) < 120)) {
    // algoritmo simples de debounce
    delay(50);
    if (analogRead(IN_RESTART_ARMADILHA) < 120) {
      Serial.println();
      Serial.println("RESTART ARMADILHA PRESSIONADO");
      armadilha_restart_pressed = true;
      hora_restart_armadilha = millis();
    }
  } 
  else if (armadilha_restart_pressed && (analogRead(IN_RESTART_ARMADILHA) >= 120)) {
    // algoritmo simples de debounce
    delay(50);
    if (analogRead(IN_RESTART_ARMADILHA) >= 120) {
      Serial.println("RESTART ARMADILHA SOLTO");
      armadilha_restart_pressed = false;
      if ((millis() - hora_restart_armadilha) <= 2000) {
        Serial.println("RESTART ARMADILHA < 2000");
        hora_restart_armadilha = 0;
        estagio_armadilha();
      }
      else {
        Serial.println("RESTART ARMADILHA > 2000");
        hora_restart_armadilha = 0;
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