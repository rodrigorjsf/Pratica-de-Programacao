#include "teclas.h"

Keyboard GetUserInput() {
	Keyboard c;
	c.Command = 0;
	c.Key = ' ';

	int ch1, ch2;
	ch1 = _getch();
	ch2 = 0;

	if (ch1 == SCROLL)
	{
		ch2 = _getch();
		switch (ch2)
		{
		case 72:
			c.Command = UP_ARROW;
			break;
		case 80:
			c.Command = DOWN_ARROW;
			break;
		case 75:
			c.Command = LEFT_ARROW;
			break;
		case 77:
			c.Command = RIGHT_ARROW;
			break;
		case 83:
			c.Command = DEL;
			break;
		default:
			c.Command = 0;
			break;
		}
	}
	else
	{
		if (ch1 == 8)
			c.Command = BACKSPACE;
		else if (ch1 == 13)
			c.Command = ENTER;
		else if (ch1 == 19)
			c.Command = SAVE_FILE;
		else if (ch1 == 1)
			c.Command = OPEN_FILE;
		else if (ch1 == 27)
			c.Command = ESC;
		else if (ch1 == 5)
			c.Command = CLOSE;
		else if (ispunct(ch1) || isalnum(ch1) || isspace(ch1) || isprint(ch1))
			c.Key = ch1;
		else
			c.Key = 0;
	}
	return c;
}

