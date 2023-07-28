#include "shell.h"

/**
 * str_ch - Finds the character in a string .
 * @charc: The character to search .
 * @sttr: The string to be looking for .
 * Reurn: The string, or if not found NULL .
 */

char *str_ch(char *sttr, char charc)
{
	do {
		if (*sttr == charc)
			return (sttr);
	} while (*sttr++ != '\0');
	return (NULL);
}

/**
 * str_cnct - It concatenates two strings .
 * @scnd_str: The second string to be conactecated .
 * @frst_str: The first string to be conactecated .
 * @nb: The maximall number of bytes to be used .
 * Return: The string which is conactecated .
 */

char *str_cnct(char *frst_str, char *scnd_str, int nb)
{
	int dest_index, src_index;
	char *sttr = frst_str;

	dest_index = 0;
	src_index = 0;
	while (frst_str[dest_index] != '\0')
		dest_index++;
	while (scnd_str[src_index] != '\0' && src_index < nb)
	{
		frst_str[dest_index] = scnd_str[src_index];
		dest_index++;
		src_index++;
	}
	if (src_index < nb)
		frst_str[dest_index] = '\0';
	return (sttr);
}
i
/**
 * str_cpy - It copies the string .
 * @nb: The number of characters to be copied .
 * @scnd_str: The second string to be copied .
 * @frst_str: The first string to be copied .
 * Return: The string which is copied .
 */

char *str_cpy(char *frst_str, char *scnd_str, int nb)
{
	int dest_index, src_index;
	char *sttr = frst_str;

	dest_index = 0;
	while (scnd_str[dest_index] != '\0' && dest_index < nb - 1)
	{
		frst_str[dest_index] = scnd_str[dest_index];
		dest_index++;
	}
	if (dest_index < nb)
	{
		src_index = dest_index;
		while (src_index < nb)
		{
			frst_str[src_index] = '\0';
			src_index++;
		}
	}
	return (sttr);
}
