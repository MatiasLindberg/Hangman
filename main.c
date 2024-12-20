#include "game.h"
#include "graphics.h"

SDL_Window* window;
SDL_Renderer* renderer;
SDL_Texture* hangman;

TTF_Font* font;
SDL_Texture* textTexture;
SDL_Surface* text;
SDL_Color color;
SDL_Texture* wordTexture;
SDL_Surface* wordText;
SDL_Rect qLetterPos;
SDL_Texture* infoTexture;
SDL_Surface* infoText;

char* word;
int* quessed;
int* wordRight;
char msg[27];
int qNumber;

bool Init() {
  if (!InitTextures()) {
    return false;
  }
  if (!InitText()) {
    return false;
  }
  return true;
}

void ExitGame() {
  TTF_CloseFont(font);
  SDL_DestroyTexture(hangman);
  SDL_DestroyTexture(textTexture);
  SDL_DestroyTexture(wordTexture);
  SDL_DestroyTexture(infoTexture);
  SDL_DestroyRenderer(renderer);
  IMG_Quit();
  TTF_Quit();
}

bool EndGame() {
  SDL_Event event;
  while (true) {
    while (SDL_PollEvent(&event)) {
      switch (event.type) {
        case SDL_QUIT:
          return true;
        case SDL_KEYDOWN:
          if (strcmp(SDL_GetKeyName(event.key.keysym.sym), "Return") == 0) {
            return false;
          } else if (strcmp(SDL_GetKeyName(event.key.keysym.sym), "Escape") ==
                     0) {
            return true;
          }
      }
    }
  }
  return false;
}

void RunGame() {
  SetUpGame();

  SDL_Rect hangmanPosition = {0, 0, 450, 520};
  SDL_Rect qWordPos = {100, 50, wordText->w, wordText->h};
  SDL_Rect infoPos = {375, 150, infoText->w, infoText->h};

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
          char buffer[512];
          if (quessed[(tmp[0] - 'A')] == 1) {
            snprintf(buffer, sizeof(buffer), "Quess again!");
          } else {
            QuessLetter(tmp[0]);
            UpdateGuessed();
            snprintf(buffer, sizeof(buffer), "Guessed: %s\n", tmp);
          }
          infoText = TTF_RenderText_Blended_Wrapped(font, buffer, color, 350);
          infoTexture = SDL_CreateTextureFromSurface(renderer, infoText);
          infoPos.h = infoText->h;
          infoPos.w = infoText->w;
          SDL_FreeSurface(infoText);
          break;
        case SDL_KEYUP:
          pressed = false;
          break;
      }
    }

    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, textTexture, NULL, &qLetterPos);
    SDL_RenderCopy(renderer, wordTexture, NULL, &qWordPos);
    SDL_RenderCopy(renderer, infoTexture, NULL, &infoPos);
    SDL_RenderCopy(renderer, hangman, NULL, &hangmanPosition);
    SDL_RenderPresent(renderer);

    if (Win()) {
      infoText = TTF_RenderText_Blended_Wrapped(
          font, "You won!   Press Enter to play a new game or Esc to exit!",
          color, 330);
      infoTexture = SDL_CreateTextureFromSurface(renderer, infoText);
      infoPos.h = infoText->h;
      infoPos.w = infoText->w;
      SDL_FreeSurface(infoText);
      SDL_RenderClear(renderer);
      SDL_RenderCopy(renderer, wordTexture, NULL, &qWordPos);
      SDL_RenderCopy(renderer, infoTexture, NULL, &infoPos);
      SDL_RenderCopy(renderer, hangman, NULL, &hangmanPosition);
      SDL_RenderPresent(renderer);
      if (!EndGame()) {
        ExitGame();
        Init();
        RunGame();
      }
      return;
    } else if (qNumber > 5) {
      char buffer[512];
      snprintf(buffer, sizeof(buffer),
               "You lost!   Press Enter to play a new game or Esc to exit! "
               "Right answer was %s!",
               word);
      infoText = TTF_RenderText_Blended_Wrapped(font, buffer, color, 330);
      infoTexture = SDL_CreateTextureFromSurface(renderer, infoText);
      infoPos.h = infoText->h;
      infoPos.w = infoText->w;
      SDL_FreeSurface(infoText);
      SDL_RenderClear(renderer);
      SDL_RenderCopy(renderer, wordTexture, NULL, &qWordPos);
      SDL_RenderCopy(renderer, infoTexture, NULL, &infoPos);
      SDL_RenderCopy(renderer, hangman, NULL, &hangmanPosition);
      SDL_RenderPresent(renderer);
      if (!EndGame()) {
        ExitGame();
        Init();
        RunGame();
      }
      return;
    }
  }
  return;
}

int main(int argc, char* argv[]) {
  srand(time(NULL));
  if (InitWindow() && Init()) {
    RunGame();
    ExitGame();
  }
  SDL_DestroyWindow(window);
  SDL_Quit();
  return 0;
}