#include "shell.h"

/**
 * _myputs - Writes the input string .
 * @sttr: The string to print .
 * Return: Non .
 */

void _myputs(char *sttr)
{
	int index = 0;

	if (!sttr)
		return;
	while (sttr[index] != '\0')
	{
		_myputchar(sttr[index]);
		index++;
	}
}

/**
 * copy_str - Copies the string .
 * @buf_dest: The destination buffer .
 * @buf_src: The source buffer .
 * Return: Pointer to destination buffer .
 */

char *copy_str(char *buf_dest, char *buf_src)
{
	int index = 0;

	if (buf_dest == buf_src || buf_src == 0)
		return (buf_dest);
	while (buf_src[index])
	{
		buf_dest[index] = buf_src[index];
		index++;
	}
	buf_dest[index] = 0;
	return (buf_dest);
}


/**
 * _myputchar - Prints the character to standard output .
 * @charc: The character to be printed .
 * Return: If success 1.
 * If error, -1 is returned, and errno is set appropriately.
 */

int _myputchar(char charc)
{
	static int index;
	static char buff[WRITE_BUF_SIZE];

	if (charc == BUF_FLUSH || index >= WRITE_BUF_SIZE)
	{
		print(1, buff, index);
		index = 0;
	}
	if (charc != BUF_FLUSH)
		buff[index++] = charc;
	return (1);
}

/**
 * dup_str - Duplicates the string .
 * @sttr: The string to be duplicated .
 * Return: Pointer to the duplicated string .
 */

char *dup_str(const char *sttr)
{
	int _bufflength = 0;
	char *result;

	if (sttr == NULL)
		return (NULL);
	while (*sttr++)
		_bufflength++;
	result = malloc(sizeof(char) * (_bufflength + 1));
	if (!result)
		return (NULL);
	for (_bufflength++; _bufflength--;)
		result[_bufflength] = *--sttr;
	return (result);
}
