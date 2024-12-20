#ifndef GAME_H
#define GAME_H

#include "graphics.h"

#include <stdlib.h>
#include <time.h>

extern char* word;
extern int* wordRight;
extern int* quessed;
extern int qNumber;
extern char msg[27];

void RandomWord();
void SetUpGame();
void QuessLetter(char c);
bool Win();

#endif