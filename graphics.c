#include "graphics.h"

bool InitWindow() {
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
    return false;
  }

  window = SDL_CreateWindow("Hangman", SDL_WINDOWPOS_CENTERED,
                            SDL_WINDOWPOS_CENTERED, 720, 540, SDL_WINDOW_SHOWN);

  if (!window) {
    printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
    return false;
  }
  return true;
}

bool InitTextures() {
  if (IMG_Init(IMG_INIT_PNG) == 0) {
    printf("SDL_image could not initialize! SDL_image Error: %s\n",
           IMG_GetError());
    return false;
  }

  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  if (!renderer) {
    printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
    return false;
  }

  hangman = IMG_LoadTexture(renderer, "Assets/Frame.png");
  if (!hangman) {
    printf("Could not load texture! SDL_Error: %s\n", SDL_GetError());
    return false;
  }
  return true;
}

bool InitText() {
  if (TTF_Init() == -1) {
    printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
    return false;
  }
  font = TTF_OpenFont("Assets/OpenSans.ttf", 40);
  if (!font) {
    printf("Failed to load font! SDL_ttf Error: %s\n", TTF_GetError());
    return false;
  }

  color.r = 255;
  color.g = 255;
  color.b = 255;

  text = TTF_RenderText_Solid(font, "Placeholder!", color);
  if (!text) {
    printf("Unable to create text surface! SDL_ttf Error: %s\n",
           TTF_GetError());
    return false;
  }
  textTexture = SDL_CreateTextureFromSurface(renderer, text);
  SDL_FreeSurface(text);
  if (!textTexture) {
    return false;
  }
  return true;
}

void UpdateHangman() {
  switch (qNumber) {
    case 0:
      hangman = IMG_LoadTexture(renderer, "Assets/Frame.png");
      break;
    case 1:
      hangman = IMG_LoadTexture(renderer, "Assets/Head.png");
      break;
    case 2:
      hangman = IMG_LoadTexture(renderer, "Assets/Body.png");
      break;
    case 3:
      hangman = IMG_LoadTexture(renderer, "Assets/Arm1.png");
      break;
    case 4:
      hangman = IMG_LoadTexture(renderer, "Assets/Arm2.png");
      break;
    case 5:
      hangman = IMG_LoadTexture(renderer, "Assets/Leg1.png");
      break;
    case 6:
      hangman = IMG_LoadTexture(renderer, "Assets/Leg2.png");
      break;
    default:
      hangman = NULL;
      break;
  }
}