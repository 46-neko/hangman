#include<stdio.h>
#include"libs/hangfunc.h"

#ifdef _WIN32
#include<conio.h>
#else
#define clrscr() printf("\e[1;1H\e[2J")
#endif

int main(){

	char secretWord[7];
	char lettersTried[26];
	int shotsFired = 0;
	int playAgain = 1;
	int userWonVar = 0;
	int gameOverVar = 0;

	showBanner();

	while(playAgain){
		chooseRandomWordFromArchive(secretWord);
		do{
			drawStickman(&shotsFired, lettersTried, secretWord);
			printSpaces(secretWord, lettersTried, shotsFired);
			userTried(&shotsFired, lettersTried);
			clrscr();
			userWonVar = userWon(&shotsFired, lettersTried, secretWord);
			gameOverVar = gameOverFunc(&shotsFired, lettersTried, secretWord);
		} while(!userWonVar && !gameOverVar);
		printVictoryOrLose(&shotsFired, lettersTried, secretWord);
		userWonVar = 0;
		gameOverVar = 0;
		playAgainFunc(&playAgain, &shotsFired, lettersTried, secretWord);
	}
	return 0;
}
