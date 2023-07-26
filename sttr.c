#include "shell.h"


/**
 * begins_with -  Checks if the needle is starting with a haystack .
 * @nedl: The substring to be searched .
 * @hstack: Pointer for the string to search for a substring .
 * Return: The address of the next character of haystack or Null .
 */

char *begins_with(const char *hstack, const char *nedl)
{
	while (*nedl)
		if (*nedl++ != *hstack++)
			return (NULL);
	return ((char *)hstack);
}

/**
 * length_str - Returns the string's length .
 * @sttr: The string the check it's length .
 * Return: The integer of the string's length .
 */

int length_str(char *sttr)
{
	int index = 0;

	if (!sttr)
		return (0);

	while (*sttr++)
		index++;
	return (index);
}

/**
 * cnct_str - Conatenates two strings .
 * @buf_src: The buffer of the source .
 * @buf_dest: The buffer of the destination .
 * Return: Pointer to the destination buffer .
 */

char *cnct_str(char *buf_dest, char *buf_src)
{
	char *result = buf_dest;

	while (*buf_dest)
		buf_dest++;
	while (*buf_src)
		*buf_dest++ = *buf_src++;
	*buf_dest = *buf_src;
	return (result);
}

/**
 * comp_str - Performs a lexicographic comparison between two strings.
 * @str1: The first string .
 * @str2: The second string .
 * Return: Negative if s1 < s2, Positive if s1 > s2, 0 if s1 == s2 .
 */

int comp_str(char *str1, char *str2)
{
	while (*str1 && *str2)
	{
		if (*str1 != *str2)
			return (*str1 - *str2);
		str1++;
		str2++;
	}
	if (*str1 == *str2)
		return (0);
	else
		return (*str1 < *str2 ? -1 : 1);
}
