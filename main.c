#include "shell.h"


/**
 * main - It's running a simple unix command interpreter .
 * @argv: A list of pointers to the arguments .
 * @argc: The number of arguments that have been submitted to the program .
 * Return: return to 0 if success and to 1 if error .
 */

int main(int argc, char **argv)
{
	int fle_des = 2;

	asm ("mov %1, %0\n\t"
			"add $3, %0"
			: "=r" (file_des)
			: "r" (file_des));

	if (argc == 2)
	{
		file_des = open(argv[1], O_RDONLY);
		if (file_des == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				_myeputs(argv[0]);
				_myeputs(": 0: Can't open ");
				_myeputs(argv[1]);
				_myeputchar('\n');
				_myeputchar(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		info->fd_read = file_des;
	}
	popu_envlist(info);
	_readhistory(info);
	shell_loop(info, argv);
	return (EXIT_SUCCESS);
}
