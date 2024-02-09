#include <iostream>

#include <locale.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_ATTEMPTS 10
#define MAX_LENGTH 100

using namespace std;

void configEnviroment();
void menuScreen();
void singlePlayerScreen();
void multiplayerScreen();
void aboutScreen();
void exitScreen();
void clearScreen();
void backToMenu();
void gameEngine(string word, int max_attempts);

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

  cout << "Bem-vindo(a) ao jogo da forca." << endl;
  cout << "1 - Jogar sozinho" << endl;
  cout << "2 - Jogar com um amigo" << endl;
  cout << "3 - Sobre" << endl;
  cout << "4 - Sair" << endl;

  cout << "Escolha uma opção: ";
  cin >> input;

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
        cout << "Opção inválida, tente novamente: ";
        cin >> input;
    }
  }
}

void singlePlayerScreen() {
  srand((unsigned)time(NULL));

  int index = rand() % 10;
  string words[10] = {"cachorro", "gato", "elefante", "tigre", "leão", "girafa", "macaco", "papagaio", "pato", "cavalo"};

  cout << "Bem-vindo(a) ao jogo!" << endl << endl;

  gameEngine(words[index], MAX_ATTEMPTS);
}

void multiplayerScreen() {
  string input;
  int attempts;

  cout << "Digite uma palavra para a forca: ";
  cin >> input;

  cout << "Digite o número máximo de tentativas: ";
  cin >> attempts;

  while (attempts < 1 || attempts > 20) {
    cout << "Tentativas permitidas: 0 - 20" << endl;
    cout << "Número de tentativas inválido, tente novamente: ";
    cin >> attempts;
  }

  clearScreen();

  cout << "Bem-vindo(a) ao jogo!" << endl;

  gameEngine(input, attempts);
}

void aboutScreen() {
  cout << "Jogo da forca desenvolvido por: " << endl;
  cout << "Autor: itsryu" << endl;
  cout << "Github: https://github.com/itsryu/" << endl;
  cout << "Código-fonte: https://github.com/itsryu/Hangman-C" << endl;

  backToMenu();
}

void exitScreen() {
  cout << "Obrigado por jogar o jogo da forca!" << endl;
  cout << "Até a próxima!" << endl;

  exit(0);
}

void backToMenu() {
  cout << "Pressione qualquer tecla para voltar ao menu principal..." << endl;

  fflush(stdin);
  getchar();
  clearScreen();
  menuScreen();
}

void gameEngine(string word, int max_attempts) {
  int attempts = 0, hasWord = 0;

  string spaces;
  string triedLetters;
  bool hasEnded = false;
  char letter;

  for (int i = 0; i < word.size(); i++) {
    spaces += "_ ";
  }

  cout << "Palavra: " << spaces << " (Tamanho: " << word.size() << " letras)" << endl;

  while (attempts < max_attempts) {
    cout << "Digite uma letra: ";
    cin >> letter;

    clearScreen();

    for (int i = 0; i < word.size(); i++) {
      if (letter == spaces[i * 2] || letter == triedLetters[i * 2]) {
        cout << "Você já tentou essa letra! Tente outra." << endl;
      }

      if (letter == word[i]) {
        spaces[i * 2] = letter;
        hasWord = 1;
      }
    }

    for (int i = 0; i < spaces.size(); i++) {
      if (spaces[i] == '_') {
        hasEnded = false;
        break;
      } else {
        hasEnded = true;
      }
    }

    if (hasEnded) {
      cout << "Parabéns! Você acertou a palavra: " << word << endl;
      backToMenu();
    }

    if (!hasWord) {
      triedLetters += letter;
      attempts++;
    }

    cout << "Palavra: " << spaces << "(Tentativas restantes: " << (max_attempts - attempts) << " tentativas)" << endl;
    cout << "Letras incorretas já utilizadas: ";

    for (int i = 0; i < triedLetters.size(); i++) {
      cout << triedLetters[i] << " ";
    }

    cout << endl;

    hasWord = 0;
  }

  if (attempts == max_attempts) {
    cout << "Você perdeu! A palavra era: " << word << endl;
    backToMenu();
  }
}