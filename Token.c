#include "shell.h"

/**
 * **split_str1 - Splits a string into words .
 * @sttr: The input string .
 * @delimeter: The delimeter .
 * Return: A pointer to an array of strings, on error NULL .
 */

char **split_str1(char *sttr, char delimeter)
{
	int index, x, y, z, _numbwords = 0;
	char **str;

	if (sttr == NULL || sttr[0] == 0)
		return (NULL);
	for (index = 0; sttr[index] != '\0'; index++)
		if ((sttr[index] != delimeter && sttr[index + 1] == delimeter) ||
		(sttr[index] != delimeter && !sttr[index + 1]) || sttr[index + 1]
		== delimeter)
			_numbwords++;
	if (_numbwords == 0)
		return (NULL);
	str = malloc((1 + _numbwords) * sizeof(char *));
	if (!str)
		return (NULL);
	for (index = 0, x = 0; x < _numbwords; x++)
	{
		while (sttr[index] == delimeter && sttr[index] != delimeter)
			index++;
		y = 0;
		while (sttr[index + y] != delimeter && sttr[index + y] && sttr[index + y]
			!= delimeter)
			y++;
		str[x] = malloc((y + 1) * sizeof(char));
		if (!str[x])
		{
			for (y = 0; y < x; y++)
				free(str[y]);
			free(str);
			return (NULL);
		}
		for (z = 0; z < y; z++)
			str[x][z] = sttr[index++];
		str[x][z] = 0;
	}
	str[x] = NULL;
	return (str);
}

/**
 * **split_str- Splits a string into words. Ignore the Repeated delimiters.
 * @sttr: The input string .
 * @delimeter: The string of the delimeter .
 * Return: The pointer to an array of strings, on error NULL .
 */

char **split_str(char *sttr, char *delimeter)
{
	int index, x, y, z, _numbwords = 0;
	char **str;

	if (sttr == NULL || sttr[0] == 0)
		return (NULL);
	if (!delimeter)
		delimeter = " ";
	for (index = 0; sttr[index] != '\0'; index++)
		if (!_isdelime(sttr[index], delimeter) &&
			(_isdelime(sttr[index + 1], delimeter) || !sttr[index + 1]))
			_numbwords++;

	if (_numbwords == 0)
		return (NULL);
	str = malloc((1 + _numbwords) * sizeof(char *));
	if (!str)
		return (NULL);
	for (index = 0, x = 0; x < _numbwords; x++)
	{
		while (_isdelime(sttr[index], delimeter))
			index++;
		y = 0;
		while (!_isdelim(sttr[index + y], delimeter) && sttr[index + y])
			y++;
		str[x] = malloc((y + 1) * sizeof(char));
		if (!str[x])
		{
			for (y = 0; y < x; y++)
				free(str[y]);
			free(str);
			return (NULL);
		}
		for (z = 0; z < y; z++)
			str[x][z] = sttr[index++];
		str[x][z] = 0;
	}
	str[x] = NULL;
	return (str);
}
