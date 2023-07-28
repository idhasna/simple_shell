#include "shell.h"

/**
 * _freeinfo - It frees the structures of fields in the information .
 * @_freeall: Frees all the fields .
 * @info: The structure's address .
 */

void _freeinfo(info_t *info, int _freeall)
{
	str_free(info->argv);
	info->argv = NULL;
	info->f_path = NULL;
	if (_freeall)
	{
		if (!info->cmd_buf)
			free(info->arg);
		if (info->env)
			list_free(&(info->env));
		if (info->_history)
			list_free(&(info->_history));
		if (info->als)
			list_free(&(info->als));
		str_free(info->_environ);
			info->_environ = NULL;
		free_pntr((void **)info->cmd_buf);
		if (info->fd_read > 2)
			close(info->fd_read);
		_myputchar(BUF_FLUSH);
	}
}

/**
 * _setinfo - Sets the information structure .
 * @av: The argument vector .
 * @info: The structure adresse .
 */

void _setinfo(info_t *info, char **av)
{
	int index = 0;

	info->f_name = av[0];
	if (info->arg)
	{
		info->argv = split_str(info->arg, " \t");
		if (!info->argv)
		{
			info->argv = malloc(sizeof(char *) * 2);
			if (info->argv)
			{
				info->argv[0] = dup_str(info->arg);
				info->argv[1] = NULL;
			}
		}
		for (index = 0; info->argv && info->argv[index]; index++)
			;
		info->argc = index;

		rep_als(info);
		rep_vars(info);
	}
}

/**
 * _clearinfo - Sets the information structure .
 * @info: The address's structure .
 */

void _clearinfo(info_t *info)
{
	info->arg = NULL;
	info->argv = NULL;
	info->f_path = NULL;
	info->argc = 0;
}
