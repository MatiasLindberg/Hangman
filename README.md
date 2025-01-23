Hangman game that gives you random word from 5000 word list and shows you how many letters it has. Wrong answer adds letter to list that shows what letters you have already quessed and adds one more body part to the hangman. When hangman is finished you lose the game and can start a new game by pressing Enter or exit pressing Esc. 


build and run:
gcc -o hangman game.c graphics.c main.c -L/usr/local/lib -lSDL2 -lSDL2_image -lSDL2_ttf
./hangman