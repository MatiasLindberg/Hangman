#include "game.h"

void RandomWord() {
  char buffer[50];
  int findLine = rand() % 5000;

  FILE* file;

  file = fopen("Assets/words.txt", "r");
  int currLine = 1;

  while (fgets(buffer, 50, file)) {
    if (currLine == findLine) {
      buffer[strcspn(buffer, "\n")] = '\0';
      word = malloc(strlen(buffer) + 1);
      strcpy(word, buffer);
      break;
    }
    currLine++;
  }
  fclose(file);
}

void SetUpGame() {
  RandomWord();
  for (int i = 0; i < strlen(word); i++) {
    word[i] = toupper(word[i]);
  }

  printf("%s \n", word);

  qNumber = 0;
  msg[0] = '\0';

  size_t length = strlen(word);
  wordRight = (int*)malloc(length * sizeof(int));

  for (size_t i = 0; i < length; i++) {
    wordRight[i] = 0;
  }

  quessed = (int*)malloc(27 * sizeof(int));
  for (size_t i = 0; i < 26; i++) {
    quessed[i] = 0;
  }
  InitWordText();
  UpdateHangman();
  UpdateGuessed();
}

void QuessLetter(char c) {
  if (quessed[(c - 'A')] == 0) {
    quessed[(c - 'A')] = 1;
  }
  bool q = false;
  for (size_t i = 0; i < strlen(word); i++) {
    if (word[i] == c) {
      wordRight[i] = 1;
      q = true;
    }
  }
  if (!q) {
    qNumber++;
    UpdateHangman();
  } else {
    UpdateWordText();
  }
}

bool Win() {
  for (size_t i = 0; i < strlen(word); i++) {
    if (wordRight[i] == 0) {
      return false;
    }
  }
  return true;
}
