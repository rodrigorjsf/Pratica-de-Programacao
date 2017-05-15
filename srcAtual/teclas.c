#include "teclas.h"

Keyboard GetUserInput() {
	Keyboard c;
	c.comando = 0;
	c.chave = ' ';

	int ch1, ch2;
	ch1 = _getch();
	ch2 = 0;
/* https://msdn.microsoft.com/en-us/library/078sfkak.aspx
 * The _getch and_getwch functions read a single character from the console without echoing the character.
 * None of these functions can be used to read CTRL+C.
 * When reading a function key or an arrow key, each function must be called twice; the first call returns 0 or 0xE0,
 * and the second call returns the actual key code.
 */
	if (ch1 == DEF)
	{
		ch2 = _getch();
		switch (ch2)
		{
		case 72:
			c.comando = UP_ARROW;
			break;
		case 80:
			c.comando = DOWN_ARROW;
			break;
		case 75:
			c.comando = LEFT_ARROW;
			break;
		case 77:
			c.comando = RIGHT_ARROW;
			break;
		case 82:
			c.comando = INSERT;
			break;
		case 83:
			c.comando = DEL;
			break;
		default:
			c.comando = 0;
			break;
		}
	}
	else
	{
		if (ch1 == 8)
			c.comando = BACKSPACE;
		else if (ch1 == 13)
			c.comando = ENTER;
		else if (ch1 == 19)
			c.comando = SAVE_FILE;
		else if (ch1 == 1)
			c.comando = OPEN_FILE;
		else if (ch1 == 27)
			c.comando = ESC;
		else if (ch1 == 5)
			c.comando = CLOSE;
		else if (ispunct(ch1) || isalnum(ch1) || isspace(ch1) || isprint(ch1))
			c.chave = ch1;
		else
			c.chave = 0;
	}
	return c;
}

