#include "game.h"
#include "graphics.h"

SDL_Window* window;
SDL_Renderer* renderer;
SDL_Texture* hangman;

TTF_Font* font;
SDL_Texture* textTexture;
SDL_Surface* text;
SDL_Color color;
char* word;
int* quessed;
int* wordRight;
int qNumber;

void EndGame() {
  TTF_CloseFont(font);
  SDL_DestroyTexture(hangman);
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
  IMG_Quit();
  TTF_Quit();
}

int main(int argc, char* argv[]) {
  if (!InitWindow(window)) {
    EndGame();
    return 0;
  }
  if (!InitTextures()) {
    EndGame();
    return 0;
  }
  if (!InitText()) {
    EndGame();
    return 0;
  }

  SetUpGame();

  printf("%s ! \n", word);

  SDL_Rect hangmanPosition = {0, 0, 480, 480};
  SDL_Event event;
  bool running = true;
  bool pressed = false;
  while (running) {
    while (SDL_PollEvent(&event)) {
      switch (event.type) {
        case SDL_QUIT:
          running = false;
          break;
        case SDL_KEYDOWN:
          const char* tmp = SDL_GetKeyName(event.key.keysym.sym);
          if (pressed || strlen(tmp) != 1 || isalpha(tmp[0]) == 0) {
            break;
          }
          pressed = true;
          if (quessed[tmp[0] - 'a' + 1] == 1) {
            printf("You have already quessed: %s\n", tmp);
          } else {
            QuessLetter(tmp[0]);
            printf("Quessed: %s\n", tmp);
          }
          break;
        case SDL_KEYUP:
          pressed = false;
          break;
      }
    }

    if (Win()) {
      printf("You won! \n");
      break;
    }

    if (qNumber > 6) {
      printf("You Lost! \n");
      break;
    }

    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, hangman, NULL, &hangmanPosition);
    SDL_RenderPresent(renderer);
  }

  EndGame();
  return 0;
}