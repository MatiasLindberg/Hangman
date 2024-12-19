#ifndef GAME_H
#define GAME_H

#include "graphics.h"

extern char* word;
extern int* wordRight;
extern int* quessed;
extern int qNumber;

void SetUpGame();
void QuessLetter(char c);
bool Win();

#endif