#include "shell.h"

/**
 * _myputfd - Prints the character to a given file descriptor .
 * @ch: The character to print .
 * @file_des: The file descriptor to use for writing .
 * Return: On success 1. When error occurs,
 * -1 is returned and errno set to correct .
 */

int _myputfd(char ch, int file_des)
{
	static int index;
	static char buff[WRITE_BUF_SIZE];

	if (ch == BUF_FLUSH || index >= WRITE_BUF_SIZE)
	{
		printf(file_des, buff, index);
		index = 0;
	}
	if (ch != BUF_FLUSH)
		buff[index++] = ch;
	return (1);
}

/**
 * my_eputs - Writes the input string .
 * @sttr: The printed string .
 * Return: Nothing .
 */

void my_eputs(char *sttr)
{
	int index = 0;

	if (!sttr)
		return;
	while (sttr[index] != '\0')
	{
		my_eputchar(sttr[index]);
		index++;
	}
}

/**
 * my_putsfd - Writes the input string to a given file descriptor .
 * @file_des: The file descriptor to use for writing .
 * @sttr: The printed string .
 * Return: The number of characters .
 */

int my_putsfd(char *sttr, int file_des)
{
	int index = 0;

	if (!sttr)
		return (0);
	while (*sttr)
	{
		index += _myputfd(*sttr++, file_des);
	}
	return (index);
}

/**
 * my_eputchar - Prints the character to the standard error .
 * @ch: The printed character .
 * Return: On success 1. When error occurs,
 * -1 is returned and errno set to correct .
 */
int _myeputchar(char ch)
{
	static int index;
	static char buff[WRITE_BUF_SIZE];

	if (ch == BUF_FLUSH || index >= WRITE_BUF_SIZE)
	{
		write(2, buff, index);
		index = 0;
	}
	if (ch != BUF_FLUSH)
		buff[index++] = ch;
	return (1);
}
