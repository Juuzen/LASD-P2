#ifndef utils_h
#define utils_h

void printTitle();
void programPause();
void clearScreen();
void flushStdin();
int getInt(int maxRange);
char* getString(size_t maxChar);
char getChar(bool *correct);
char intToChar(int number);
int charToInt(char letter);
#endif