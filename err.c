#include "shell.h"

/**
 * _myputfd - Prints the character to a given file descriptor .
 * @charc: The character to print .
 * @file_des: The file descriptor to use for writing .
 * Return: On success 1. When error occurs,
 * -1 is returned and errno set to correct .
 */

int _myputfd(char charc, int file_des)
{
	static int index;
	static char buff[WRITE_BUF_SIZE];

	if (charc == BUF_FLUSH || index >= WRITE_BUF_SIZE)
	{
		print(file_des, buff, index);
		index = 0;
	}
	if (charc != BUF_FLUSH)
		buff[index++] = charc;
	return (1);
}

/**
 * _myeputs - Writes the input string .
 * @sttr: The printed string .
 * Return: Nothing .
 */

void _myeputs(char *sttr)
{
	int index = 0;

	if (!sttr)
		return;
	while (sttr[index] != '\0')
	{
		_myeputchar(sttr[index]);
		index++;
	}
}

/**
 * _myputsfd - Writes the input string to a given file descriptor .
 * @file_des: The file descriptor to use for writing .
 * @sttr: The printed string .
 * Return: The number of characters .
 */

int _myputsfd(char *sttr, int file_des)
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
 * _myeputchar - Prints the character to the standard error .
 * @charc: The printed character .
 * Return: On success 1. When error occurs,
 * -1 is returned and errno set to correct .
 */
int _myeputchar(char charc)
{
	static int index;
	static char buff[WRITE_BUF_SIZE];

	if (charc == BUF_FLUSH || index >= WRITE_BUF_SIZE)
	{
		print(2, buff, index);
		index = 0;
	}
	if (charc != BUF_FLUSH)
		buff[index++] = charc;
	return (1);
}
