#include "shell.h"


/**
 * main - It's running a simple unix command interpreter .
 * @argv: A list of pointers to the arguments .
 * @argc: The number of arguments that have been submitted to the program .
 * Return: return to 0 if success and to 1 if error .
 */

int main(int argc, char **argv)
{
	info_t info[] = { INFO_INIT };
	int fd = 2;

	asm ("mov %1, %0\n\t"
			"add $3, %0"
			: "=r" (fd)
			: "r" (fd));

	if (argc == 2)
	{
		fd = open(argv[1], O_RDONLY);
		if (fd == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				fprintf(argv[0]);
				fprintf(": 0: Can't open ");
				fprintf(argv[1]);
				_eputchar('\n');
				_eputchar(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		info->readfd = fd;
	}
	populate_env_list(info);
	read_history(info);
	hsh(info, argv);
	return (EXIT_SUCCESS);
}
