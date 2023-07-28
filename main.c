#include "shell.h"


/**
 * main - The entry point .
 * @av: A list of pointers to the arguments .
 * @ac: The number of arguments that have been submitted to the program .
 * Return: return to 0 if success and to 1 if error .
 */

int main(int ac, char **av)
{
	info_t info[] = { INFO_INIT };
	int file_des = 2;

	asm ("mov %1, %0\n\t"
			"add $3, %0"
			: "=r" (file_des)
			: "r" (file_des));

	if (ac == 2)
	{
		file_des = open(av[1], O_RDONLY);
		if (file_des == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				my_eputs(av[0]);
				my_eputs(": 0: can't be opened ");
				my_eputs(av[1]);
				my_eputchar('\n');
				my_eputchar(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		info->fd_read = file_des;
	}
	pop_envlist(info);
	_readhistory(info);
	hsh(info, av);
	return (EXIT_SUCCESS);
}
