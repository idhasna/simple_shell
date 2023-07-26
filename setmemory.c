#include "shell.h"

/**
 * _memrealloc - Reallocates the memory block .
 * @pre_size: The size of the previous block .
 * @cur_size: The size of the current block .
 * @pntr: Pointer for the previous malloc'ated block .
 * Return: Pointer to the memory block that has been reallocated.
 */

void *_memrealloc(void *pntr, unsigned int pre_size, unsigned int cur_size)
{
	char *pos;

	if (!pntr)
		return (malloc(cur_size));
	if (!cur_size)
		return (free(pntr), NULL);
	if (cur_size == pre_size)
		return (pntr);

	pos = malloc(cur_size);
	if (!pos)
		return (NULL);

	pre_size = pre_size < cur_size ? pre_size : cur_size;
	while (pre_size--)
		pos[pre_size] = ((char *)pntr)[pre_size];
	free(pntr);
	return (pos);
}

/**
 * str_free - Frees the array of strings .
 * @str_arr: The array of strings .
 */

void str_free(char **str_arr)
{
	char **index = str_arr;

	if (!str_arr)
		return;
	while (*str_arr)
		free(*str_arr++);
	free(index);
}

/**
 * fill_mem - Fills the memory with a constant byte .
 * @pntr: The pointer of the memory .
 * @byte: The byte used to fill the memory with .
 * @numb: The number of bytes used to fill the memory .
 * Return: the pointer of the memory .
 */

char *fill_mem(char *pntr, char byte, unsigned int numb)
{
	unsigned int index;

	for (index = 0; index < numb; index++)
		pntr[index] = byte;
	return (pntr);
}
