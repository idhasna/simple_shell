#include "shell.h"

/**
 * free_pntr - Frees the pointer and NULLs the address .
 * @pntr: The address of the pointer to be freed .
 * Return: If freed 1, if not 0 .
 */

int free_pntr(void **pntr)
{
	if (pntr && *pntr)
	{
		free_pntr(*pntr);
		*pntr = NULL;
		return (1);
	}
	return (0);
}
