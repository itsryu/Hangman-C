#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <time.h>

#define MAX_ATTEMPTS 10
#define MAX_LENGTH 100

void configEnviroment();
void menuScreen();
void singlePlayerScreen();
void multiplayerScreen();
void aboutScreen();
void exitScreen();
void clearScreen();
void backToMenu();
void gameEngine(char *word, int max_attempts);

int main(void) {
  configEnviroment();
  clearScreen();
  menuScreen();

  return 0;
}

void configEnviroment() {
  setlocale(LC_ALL, "Portuguese");
  system("color 0A");
};

void clearScreen() {
  #ifdef _WIN32
    system("cls");
  #elif __linux__
    system("clear");
  #endif
}

void menuScreen() {
  int input;

  printf("Bem-vindo(a) ao jogo da forca.\n");
  printf("1 - Jogar sozinho\n");
  printf("2 - Jogar com um amigo\n");
  printf("3 - Sobre\n");
  printf("4 - Sair\n");

  printf("Escolha uma opção: ");
  scanf("%d", &input);

  while (input > 1 || input < 4) {
    switch (input) {
      case 1:
        clearScreen();
        singlePlayerScreen();
        break;

      case 2:
        clearScreen();
        multiplayerScreen();
        break;

      case 3:
        clearScreen();
        aboutScreen();
        break;

      case 4:
        clearScreen();
        exitScreen();
        break;

      default:
        printf("Opção inválida, tente novamente: ");
        scanf("%d", &input);
    }
  }
}

void singlePlayerScreen() {
  srand((unsigned)time(NULL));

  int index = rand() % 10;
  char words[10][20] = {"cachorro", "gato", "elefante", "vaca", "tigre", "girafa", "macaco", "papagaio", "pato", "cavalo"};

  printf("Bem-vindo(a) ao jogo!\n\n");

  gameEngine(words[index], MAX_ATTEMPTS);
}

void multiplayerScreen() {
  char input[MAX_LENGTH];
  int attempts;

  printf("Digite uma palavra para a forca: ");

  fflush(stdin);
  fgets(input, sizeof(input), stdin);

  printf("Digite o número máximo de tentativas: ");
  scanf("%d", &attempts);

  while(attempts < 1 || attempts > 20) {
    printf("Tentativas permitidas: 0 - 20\n");
    printf("Número de tentativas inválido, tente novamente: ");
    scanf("%d", &attempts);
  }

  input[strlen(input) - 1] = '\0';

  clearScreen();

  printf("Bem-vindo(a) ao jogo!\n");

  gameEngine(input, attempts);
}

void aboutScreen() {
  printf("Jogo da forca desenvolvido por: \n");
  printf("Autor: itsryu\n");
  printf("Github: https://github.com/itsryu/\n");
  printf("Código-fonte: https://github.com/itsryu/Hangman-C\n");

  backToMenu();
}

void exitScreen() {
  printf("Obrigado por jogar o jogo da forca!\n");
  printf("Até a próxima!\n");
  exit(0);
}

void backToMenu() {
  printf("Pressione qualquer tecla para voltar ao menu principal...\n");
  fflush(stdin);
  getchar();
  clearScreen();
  menuScreen();
}

void gameEngine(char *word, int max_attempts) {
  int attempts = 0, hasWord = 0;

  char spaces[MAX_LENGTH] = "";
  char triedLetters[MAX_LENGTH] = "";
  char letter;

  for (int i = 0; i < strlen(word); i++) {
    strcat(spaces, "_ ");
  }

  printf("Palavra: %s (Tamanho: %d letras)\n", spaces, strlen(word));

  while (attempts < max_attempts) {
    printf("Digite uma letra: ");
    fflush(stdin);
    scanf("%c", &letter);

    clearScreen();

    for (int i = 0; i < strlen(word); i++) {
      if (letter == spaces[i * 2] || letter == triedLetters[i * 2]) {
        printf("Você já tentou essa letra! Tente outra.\n");
      }

      if (letter == word[i]) {
        spaces[i * 2] = letter;
        hasWord = 1;
      }
    }

    if (strstr(spaces, "_") == NULL) {
      printf("Parabéns! Você acertou a palavra: %s\n", word);
      backToMenu();
      break;
    }

    if (!hasWord) {
      char tmpstr[3] = {" "};
      tmpstr[0] = letter;
      tmpstr[1] = ' ';
      tmpstr[2] = '\0';

      strcat(triedLetters, tmpstr);
      
      attempts++;
    }

    printf("Palavra: %s (Tentativas restantes: %d tentativas)\n", spaces, (max_attempts - attempts));
    printf("Letras incorretas já utilizadas: %s\n", triedLetters);

    hasWord = 0;
  }

  if (attempts == max_attempts) {
    printf("Você perdeu! A palavra era: %s\n", word);
    backToMenu();
  }
}