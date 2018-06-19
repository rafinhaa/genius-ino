//-----------------------#define e Variáveis------------------------//
#define LED_A 5
#define LED_B 6
#define LED_C 7

#define BUTTON_A 8
#define BUTTON_B 9
#define BUTTON_C 10

#define BUZZER 11

#define TOM_A 1200
#define TOM_B 1600
#define TOM_C 2000

#define TEMPO_PISCA 600
#define TEMPO_ENTRE 150

int qt_seq = 0;
boolean continua = false;


//--------------Declaração da função de cada elemento---------------//
void setup() {
  Serial.begin(9600);

  pinMode(LED_A, OUTPUT);
  pinMode(LED_B, OUTPUT);
  pinMode(LED_C, OUTPUT);

  pinMode(BUTTON_A, INPUT_PULLUP);
  pinMode(BUTTON_B, INPUT_PULLUP);
  pinMode(BUTTON_C, INPUT_PULLUP);

  pinMode(BUZZER, OUTPUT);

  randomSeed(analogRead(0)); //Sorteia uma nova sequencia toda vez que liga o Arduino
}

//----------Loop do sorteio, leitura de botão e comparação----------//
void loop() {
  Serial.print("Rodada = ");
  Serial.println(qt_seq);
  if (continua) {
    qt_seq = qt_seq + 1;
  } else {
    qt_seq = 1;
    //Acende tudo
    digitalWrite(LED_A, HIGH);
    digitalWrite(LED_B, HIGH);
    digitalWrite(LED_C, HIGH);
    delay(500); //Apaga tudo
    digitalWrite(LED_A, LOW);
    digitalWrite(LED_B, LOW);
    digitalWrite(LED_C, LOW);
    delay(500);
    le_botao(); //Jogador aperta qlqer botão e já inicia o sorteio
  }

  int sorteados[qt_seq]; // qt_seq é o tamanho da sequência dos leds




  //-----------------------Sorteio da sequência-----------------------//
  //qt_seq é o tamanho da sequência - quantas vezes os LEDs piscam
  for (int jogada = 0; jogada < qt_seq; jogada ++) {
    sorteados[jogada] = random(2);
    pisca_led(sorteados[jogada]);
    delay(TEMPO_ENTRE);
  } //Fim do sorteio

  //---------------------Comparação da sequência----------------------//
  int vez; //Definido fora do for para poder verificar numero de acertos no final
  for (vez = 0; vez < qt_seq; vez ++) {
    delay(250);
    if (le_botao() == sorteados[vez]) {
      pisca_led(sorteados[vez]);
    } else {

      pisca_led(sorteados[vez]);
      break; //Sai do for
    }
  }

  //----------------------------Resultado-----------------------------//
  if (vez == qt_seq) { //Acertou seq. inteira
    Serial.println("Acertou");
    continua = true;
    delay(500);
    for (int i = 0; i < 3; i++) {
      tone(BUZZER, 2000);
      delay(200);
      tone(BUZZER, 4000);
      delay(200);
    }
    noTone(BUZZER);
  } else { //Errou algo
    Serial.println("Errou");
    continua = false;
    delay(500);
    for (int i = 0; i < 3; i++) {
      tone(BUZZER, 200);
      delay(200);
      tone(BUZZER, 300);
      delay(200);
      tone(BUZZER, 400);
      delay(200);
    }
    noTone(BUZZER);
  }
} //Fim do loop




//------------------------Função piscar LED-------------------------//
void pisca_led(int posicao) {
  Serial.print(posicao);

  if (posicao == 0) {
    Serial.println(" Vermelho");
    digitalWrite(LED_A, HIGH);
    tone(BUZZER, TOM_A);
    delay(TEMPO_PISCA);
    digitalWrite(LED_A, LOW);
  } else if (posicao == 1) {
    Serial.println(" Branco");
    digitalWrite(LED_B, HIGH);
    tone(BUZZER, TOM_B);
    delay(TEMPO_PISCA);
    digitalWrite(LED_B, LOW);
  } else if (posicao == 2) {
    Serial.println(" Azul");
    digitalWrite(LED_C, HIGH);
    tone(BUZZER, TOM_C);
    delay(TEMPO_PISCA);
    digitalWrite(LED_C, LOW);
  }
  delay(100);
  noTone(BUZZER);
} //Fim do pisca_led

//------------------------Função ler os botões----------------------//
int le_botao () {
  int result = -1; //-1 indica que nenhum botão foi apertado

  while (result == -1) {
    if (digitalRead(BUTTON_A) == LOW) {
      result = 0;    //Posição 0
    } else if (digitalRead(BUTTON_B) == LOW) {
      result = 1;
    } else if (digitalRead(BUTTON_C) == LOW) {
      result = 2;
    }
  }
  return result; //Retorna o inteiro int le_botao
}
