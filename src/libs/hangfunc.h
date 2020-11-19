#ifndef HANGFUNC_H_
#define HANGFUNC_H_

void showBanner();
void userTried(int *shotsFired, char lettersTried[5]);
int letterAlreadyUsed(char characterTried, int shotsFired, char lettersTried[5]);
void printSpaces(char secretWord[7], char lettersTried[5], int shotsFired);
int gameOverFunc(int *shotsFired, char lettersTried[5], char secretWord[7]);
void printVictoryOrLose(int *shotsFired, char lettersTried[26], char secretWord[7]);
int userWon(int *shotsFired, char lettersTried[26], char secretWord[7]);
void chooseRandomWordFromArchive(char secretWord[7]);
int difficultySettings();
int countingLivesLost(int *shotsFired, char secretWord[7], char lettersTried[26]);
void drawStickman(int *shotsFired, char lettersTried[26], char secretWord[7]);
void playAgainFunc(int *playAgain, int *shotsFired, char lettersTried[26], char secretWord[7]);

#endif