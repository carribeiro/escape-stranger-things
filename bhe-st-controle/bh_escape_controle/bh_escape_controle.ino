// (C) 2021 FAZ MAKERSPACE
// CAIXA DE CONTROLE BH ESCAPE
// SALA STRANGER THINGS
//
// pins

#define IN_ARVORE_LIGADA       (2)
#define IN_ARVORE_OK           (3)
#define LED_ARVORE_OK          (4)
#define IN_RPG_LIGADO          (5)
#define IN_RPG_OK              (6)
#define LED_RPG_OK             (7)
#define IN_WILL_LIGADO         (8)
#define IN_WILL_OK             (9)
#define LED_WILL_OK            (10)
#define IN_ARMADILHA_LIGADA    (11)
#define IN_ARMADILHA_OK        (12)
#define LED_ARMADILHA_OK       (13)
#define RELE_LIGA_TV           (A0)
#define RELE_PORTA_ARMADILHA   (A1)
#define RELE_PORTA_ARMARIO     (A2)
#define RELE_PORTA_PRINCIPAL   (A3)
#define IN_RESTART_ARVORE      (A4)
#define IN_RESTART_RPG         (A5)
#define IN_RESTART_WILL        (A5)
#define IN_RESTART_ARMADILHA   (A7)

boolean arvore_ligada = false;
boolean rpg_ligado = false;
boolean will_ligado = false;
boolean armadilha_ligada = false;

boolean arvore_ok = false;
boolean rpg_ok = false;
boolean will_ok = false;
boolean armadilha_ok = false;

boolean arvore_resolvida = false;
boolean rpg_resolvido = false;
boolean will_resolvido = false;
boolean armadilha_resolvida = false;

void reset_game() {

  // configura pinos
  pinMode(IN_ARVORE_LIGADA, INPUT); // pulldown?
  pinMode(IN_ARVORE_OK, INPUT_PULLUP);
  pinMode(LED_ARVORE_OK, OUTPUT);
  pinMode(IN_RPG_LIGADO, INPUT);
  pinMode(IN_RPG_OK, INPUT_PULLUP);
  pinMode(LED_RPG_OK, OUTPUT);
  pinMode(IN_WILL_LIGADO, INPUT);
  pinMode(IN_WILL_OK, INPUT_PULLUP);
  pinMode(LED_WILL_OK, OUTPUT);
  pinMode(IN_ARMADILHA_LIGADA, INPUT);
  pinMode(IN_ARMADILHA_OK, INPUT_PULLUP);
  pinMode(LED_ARMADILHA_OK, OUTPUT);
  pinMode(RELE_LIGA_TV, OUTPUT);
  pinMode(RELE_PORTA_ARMADILHA, OUTPUT);
  pinMode(RELE_PORTA_ARMARIO, OUTPUT);
  pinMode(RELE_PORTA_PRINCIPAL, OUTPUT);
  pinMode(IN_RESTART_ARVORE, INPUT_PULLUP);
  pinMode(IN_RESTART_RPG, INPUT_PULLUP);
  pinMode(IN_RESTART_WILL, INPUT_PULLUP);
  pinMode(IN_RESTART_ARMADILHA, INPUT_PULLUP);

  // zera variáveis de controle
  arvore_ligada = digitalRead(IN_ARVORE_LIGADA);  
  rpg_ligado = digitalRead(IN_RPG_LIGADO);  
  will_ligado = digitalRead(IN_WILL_LIGADO);  
  armadilha_ligada = digitalRead(IN_ARMADILHA_LIGADA);  

  arvore_ok = digitalRead(IN_ARVORE_OK);
  rpg_ok = digitalRead(IN_RPG_OK);
  will_ok = digitalRead(IN_WILL_OK);
  armadilha_ok = digitalRead(IN_ARMADILHA_OK);

  arvore_resolvida = false;  
  digitalWrite(RELE_LIGA_TV, LOW);
  rpg_resolvido = false;  
  digitalWrite(RELE_PORTA_ARMADILHA, LOW);
  will_resolvido = false;  
  digitalWrite(RELE_PORTA_ARMARIO, LOW);
  armadilha_resolvida = false;  
  digitalWrite(RELE_PORTA_PRINCIPAL, LOW);

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
  Serial.println("Estágio ARVORE");
  desliga_tomada_tv();
  trava_porta_armadilha();
  trava_porta_armario();
  trava_porta_principal();
}

void estagio_rpg() {
  Serial.println("Estágio RPG");
  liga_tomada_tv();
  trava_porta_armadilha();
  trava_porta_armario();
  trava_porta_principal();
}

void estagio_will() {
  Serial.println("Estágio WILL");
  liga_tomada_tv();
  destrava_porta_armadilha();
  trava_porta_armario();
  trava_porta_principal();
}

void estagio_armadilha() {
  Serial.println("Estágio ARMADILHA");
  liga_tomada_tv();
  destrava_porta_armadilha();
  destrava_porta_armario();
  trava_porta_principal();
}

void estagio_final() {  
  desliga_tomada_tv();
  destrava_porta_armadilha();
  destrava_porta_armario();
  destrava_porta_principal();
}

void test_game() {
  digitalWrite(LED_ARVORE_OK, HIGH); delay(500);
  digitalWrite(LED_ARVORE_OK, LOW); delay(500);
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

boolean old_arvore_ligada = false;
boolean old_rpg_ligado = false;
boolean old_will_ligado = false;
boolean old_armadilha_ligada = false;

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

  // read new status; signals that are true when LOW are inverted on read to simplify logic
  arvore_ligada = digitalRead(IN_ARVORE_LIGADA);  
  rpg_ligado = digitalRead(IN_RPG_LIGADO);  
  will_ligado = digitalRead(IN_WILL_LIGADO);  
  armadilha_ligada = digitalRead(IN_ARMADILHA_LIGADA);  

  if (arvore_ligada) { arvore_ok = !digitalRead(IN_ARVORE_OK); } else { arvore_ok = false; }
  if (rpg_ligado) { rpg_ok = !digitalRead(IN_RPG_OK); } else { rpg_ok = false; }
  if (will_ligado) { will_ok = !digitalRead(IN_WILL_OK); } else { will_ok = false; }
  if (armadilha_ligada) { armadilha_ok = !digitalRead(IN_ARMADILHA_OK); } else { armadilha_ok = false; }

  // returns true if anything changed
  return (
    (old_arvore_ok != arvore_ok) ||
    (old_rpg_ok != rpg_ok) ||
    (old_will_ok != will_ok) ||
    (old_armadilha_ok != armadilha_ok) 
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

  boolean status_changed;

  status_changed = atualiza_status();
  if (status_changed) {
    imprime_status();
  }

  // ARVORE GENEALOGICA
  if (arvore_ok != old_arvore_ok) {
    if (arvore_ok) {
      Serial.println("Árvore OK");
      digitalWrite(LED_ARVORE_OK, HIGH);
      Serial.println("Árvore RESOLVIDA");
      estagio_rpg();
    }
    else {
      Serial.println("Árvore NÃO OK");
      digitalWrite(LED_ARVORE_OK, LOW);
    }
  }

  // RPG
  if (rpg_ok != old_rpg_ok) {
    if (rpg_ok) {
      Serial.println("RPG OK");
      digitalWrite(LED_RPG_OK, HIGH);
      Serial.println("RPG RESOLVIDO");
      estagio_will();
    }
    else {
      Serial.println("RPG NÃO OK");
      digitalWrite(LED_RPG_OK, LOW);
    }
  }

  if (will_ok != old_will_ok) {
    if (will_ok) {
      Serial.println("Will OK");
      digitalWrite(LED_WILL_OK, HIGH);
      Serial.println("Will RESOLVIDO");
      estagio_armadilha();
    }
    else {
      Serial.println("Will NÃO OK");
      digitalWrite(LED_WILL_OK, LOW);
    }
  }

  if (armadilha_ok != old_armadilha_ok) {
    if (armadilha_ok) {
      Serial.println("Armadilha OK");
      digitalWrite(LED_ARMADILHA_OK, HIGH);
      Serial.println("Will RESOLVIDO");
      estagio_final();
    }
    else {
      Serial.println("Armadilha OK");
      digitalWrite(LED_ARMADILHA_OK, LOW);
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
