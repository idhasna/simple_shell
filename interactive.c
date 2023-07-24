#include "shell.h"

/**
 * is_alphab - Checks if the characters are alphabetics .
 * @charc: The character to check .
 * Return: If the character is alphabetic 1, if no 0 .
 */

int is_alphab(int charc)
{
	if ((charc >= 'a' && charc <= 'z') || (charc >= 'A' && charc <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * _isinteractive - Checks if the Shell is in interactive mode .
 * @info: The address structure .
 * Return: If interactive mode 1, if not 0 .
 */

int _isinteractive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * _myatoi - The string is converted to an integer .
 * @sttr: The string to convert .
 * Return: If no number in string 0 .
 */

int _myatoi(char *sttr)
{
	int index, sign = 1, flg = 0, output;
	unsigned int result = 0;

	for (index = 0; sttr[index] != '\0' && flg != 2; index++)
	{
		if (sttr[index] == '-')
			sign *= -1;

		if (sttr[index] >= '0' && sttr[index] <= '9')
		{
			flg = 1;
			result *= 10;
			result += (sttr[index] - '0');
		}
		else if (flg == 1)
			flg = 2;
	}

	if (sign == -1)
		output = -result;
	else
		output = result;

	return (output);
}

/**
 * _isdelime - Checks if the characters are delimeters .
 * @str_delim: The string which is delimeter .
 * @charc: The character to be checked .
 * Return: 1 on success, 0 on error .
 */

int _isdelime(char charc, char *str_delim)
{
	while (*str_delim)
		if (*str_delim++ == c)
			return (1);
	return (0);
}
