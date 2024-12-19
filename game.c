#include "game.h"

void SetUpGame() {
  word = "SANA";

  qNumber = 0;

  UpdateHangman();

  size_t length = strlen(word);
  wordRight = (int*)malloc(length * sizeof(int));

  for (size_t i = 0; i < length; i++) {
    wordRight[i] = 0;
  }

  quessed = (int*)malloc(27 * sizeof(int));
  for (size_t i = 0; i < 26; i++) {
    quessed[i] = 0;
  }
}

void QuessLetter(char c) {
  quessed[c - 'a' + 1] = 1;
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
