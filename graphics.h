#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdbool.h>
#include <stdio.h>
#include "SDL2/SDL_keyboard.h"

#include "game.h"

extern SDL_Window* window;
extern SDL_Renderer* renderer;
extern SDL_Texture* hangman;

extern TTF_Font* font;
extern SDL_Texture* textTexture;
extern SDL_Surface* text;
extern SDL_Color color;
extern SDL_Texture* wordTexture;
extern SDL_Surface* wordText;
extern SDL_Rect qLetterPos;
extern SDL_Texture* infoTexture;
extern SDL_Surface* infoText;

extern int qNumber;
extern char msg[27];

bool InitWindow();
bool InitTextures();
bool InitText();
bool InitWordText();

void UpdateWordText();
void UpdateHangman();
void UpdateGuessed();

#endif