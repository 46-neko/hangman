#include "hangfunc.h"
#include<stdio.h>
#include<string.h>
#include<time.h>
#include<stdlib.h>
#include<ctype.h>

#ifdef _WIN32
#include<conio.h>
#else
#define clrscr() printf("\e[1;1H\e[2J")
#endif

void showBanner(){
	clrscr();
	printf("**************************\n");
	printf("*      HANGMAN GAME      *\n");
	printf("**************************\n\n");
}

void userTried(int *shotsFired, char lettersTried[5]){
	char letterTriedBuffer[256];
	fgets(letterTriedBuffer, 256, stdin);
	letterTriedBuffer[0] = tolower(letterTriedBuffer[0]);

	lettersTried[(*shotsFired)] = letterTriedBuffer[0];
	(*shotsFired)++;
}

int letterAlreadyUsed(char characterTried, int shotsFired, char lettersTried[5]){
	int letterTrue = 0;
		for(int j = 0; j < shotsFired; j++){
			if(lettersTried[j] == characterTried){
				letterTrue = 1;
				break;
			}
		}
	return letterTrue;
}

void printSpaces(char secretWord[7], char lettersTried[5], int shotsFired){
	for(int i = 0; i < strlen(secretWord); i++){
			if(letterAlreadyUsed(secretWord[i], shotsFired, lettersTried)){
				printf("%c ", secretWord[i]);
			} else{
				printf("_ ");
			}
		}
	printf("\n");	
}

int gameOverFunc(int *shotsFired, char lettersTried[26], char secretWord[7]){
	return countingLivesLost(shotsFired, secretWord, lettersTried) >= 5;
}

int userWon(int *shotsFired, char lettersTried[26], char secretWord[7]){
	for(int i = 0; i < strlen(secretWord); i++){
		if(!letterAlreadyUsed(secretWord[i], (*shotsFired), lettersTried)){
			return 0;
		}
	}
	return 1;
}

void printVictoryOrLose(int *shotsFired, char lettersTried[26], char secretWord[7]){
	if(userWon(shotsFired, lettersTried, secretWord)){
		printf("**********************************************\n");
		printf("*                  You won!                  *\n");
		printf("**********************************************\n");
		printf("The word was: %s\n", secretWord);
	}

	else if(gameOverFunc(shotsFired, lettersTried, secretWord)){
		printf("**********************************************\n");
		printf("*                 You lost :(                *\n");
		printf("**********************************************\n");
		printf("The word was: %s\n", secretWord);
	}
}

void chooseRandomWordFromArchive(char secretWord[7]){
	FILE* f;

	int difficultyLoopVar = 1;

	while(difficultyLoopVar){

	switch(difficultySettings()){
		case 1:
			f = fopen("wordlist/3words.hwl", "r");
			difficultyLoopVar = 0;
		break;

		case 2:
			f = fopen("wordlist/4words.hwl", "r");
			difficultyLoopVar = 0;
		break;

		case 3:
			f = fopen("wordlist/5words.hwl", "r");
			difficultyLoopVar = 0;
		break;

		case 0:
			clrscr();
		break;
	}
}
	if(f == 0){
		printf("There was an error trying to open the word list. Make sure you do have the ''3words.hwl'', ''4words.hwl'' and ''5words.hwl'' files in the folder ''wordlist''\n");
		exit(1);
	}

	int wordQuantity;
	fscanf(f, "%d", &wordQuantity);

	srand(time(0));
	int randVar = rand() % wordQuantity;

	for(int i = 0; i <= randVar; i++){
		fscanf(f, "%s", secretWord);
	}

	fclose(f);
	clrscr();
}

int difficultySettings(){
	char difficultyBuffer[256];
	printf("*****************************************\n");
	printf("* Please choose the difficulty setting! *\n");
	printf("*    Difficulty 1: 3 character word     *\n");
	printf("*    Difficulty 2: 4 character word     *\n");
	printf("*    Difficulty 3: 5 character word     *\n");
	printf("*****************************************\n");

	fgets(difficultyBuffer, 256, stdin);

	if(strcmp(difficultyBuffer, "1\n") == 0){
		return 1;
	}

	else if(strcmp(difficultyBuffer, "2\n") == 0){
		return 2;
	}

	else if(strcmp(difficultyBuffer, "3\n") == 0){
		return 3;
	}

	else{
		return 0;
	}
}

int countingLivesLost(int *shotsFired, char secretWord[7], char lettersTried[26]){
	int livesLost = 0;

	for(int i = 0; i < (*shotsFired); i++){
		int letterExist = 0;
		for(int j = 0; j < strlen(secretWord); j++){
			if(lettersTried[i] == secretWord[j]){
				letterExist = 1;
				break;
			}	
		}

		if(!letterExist){
			livesLost++;
		} 
	}
	return livesLost;
}

void drawStickman(int *shotsFired, char lettersTried[26], char secretWord[7]){
	int livesLost = countingLivesLost(shotsFired, secretWord, lettersTried);

	printf("  _______       \n");
    printf(" |/      |      \n");
    printf(" |      %c%c%c  \n", (livesLost>=1?'(':' '), (livesLost>=1?'_':' '), (livesLost>=1?')':' '));
    printf(" |      %c%c%c  \n", (livesLost>=3?'\\':' '), (livesLost>=2?'|':' '), (livesLost>=3?'/': ' '));
    printf(" |       %c     \n", (livesLost>=2?'|':' '));
    printf(" |      %c %c   \n", (livesLost>=4?'/':' '), (livesLost>=4?'\\':' '));
    printf(" |              \n");
    printf("_|___           \n");
    printf("\n\n");
}

void playAgainFunc(int *playAgain, int *shotsFired, char lettersTried[26], char secretWord[7]){
	char playAgainBuffer[256];
	printf("Do you wish to play again?\ny = Yes\nn = No\n");
	fgets(playAgainBuffer, 256, stdin);
	playAgainBuffer[0] = tolower(playAgainBuffer[0]);

	if(strcmp(playAgainBuffer, "y\n") == 0){
		clrscr();
		(*shotsFired) = 0;
		memset(lettersTried, 0, sizeof((*lettersTried)));
		memset(secretWord, 0, sizeof((*secretWord)));
	}

	else if(strcmp(playAgainBuffer, "n\n") == 0){
		(*playAgain) = 0;
		clrscr();
		printf("***********************************************\n");
		printf("*      Thank you so much for playing! =)      *\n");
		printf("***********************************************\n");
	}

	else{
		clrscr();
		printf("Sorry, didn't get it.\n");
		playAgainFunc(playAgain, shotsFired, lettersTried, secretWord);
	}
}
