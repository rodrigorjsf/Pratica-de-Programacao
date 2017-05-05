#include <stdio.h>
#include <ctype.h>
#include <conio.h>

#define FALSE 0
#define TRUE 1
#define SCROLL 0xE0
#define UP_ARROW 1
#define DOWN_ARROW 2
#define LEFT_ARROW 3
#define RIGHT_ARROW 4
#define SAVE_FILE 5
#define OPEN_FILE 6
#define BACKSPACE 7
#define DEL 8
#define ENTER 9
#define ESC 10
#define CLOSE 11

typedef struct TKeyboard {
	char Key;
	int Command;
}Keyboard;

Keyboard GetUserInput();
