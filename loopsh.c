#include "shell.h"


/**
 * _findcomnd - Finds the command in the path .
 * @info: The structure of the parameter .
 * Return: Void .
 */

void _findcomnd(info_t *info)
{
	char *f_path = NULL;
	int index, j;

	info->f_path = info->argv[0];
	if (info->_flinecount == 1)
	{
		info->_linecount++;
		info->_flinecount = 0;
	}
	for (index = 0, j = 0; info->arg[index]; index++)
		if (!_isdelime(info->arg[index], " \t\n"))
			j++;
	if (!j)
		return;

	f_path = _findpath(info, get_env(info, "PATH="), info->argv[0]);
	if (f_path)
	{
		info->f_path = f_path;
		fork_cmd(info);
	}
	else
	{
		if ((_isinteractive(info) || get_env(info, "PATH=")
					|| info->argv[0][0] == '/') && execut_comnd(info, info->argv[0]))
			_forkcomnd(info);
		else if (*(info->arg) != '\n')
		{
			info->_status = 127;
			_printerr(info, "Not exist\n");
		}
	}
}

/**
 * hsh - The main shell loop .
 * @av: The argument vector .
 * @info: The structure of the parameter .
 * Return: On success 0, On error 1 .
 */

int hsh_loop(info_t *info, char **av)
{
	ssize_t result = 0;
	int return_builtin = 0;

	while (result != -1 && return_builtin != -2)
	{
		_clearinfo(info);
		if (_isinteractive(info))
			_myputs("$ ");
		_myeputchar(BUF_FLUSH);
		result = _getinput(info);
		if (result != -1)
		{
			_setinfo(info, av);
			(return_builtin = builtin_find(info));
			if (return_builtin == -1)
				_findcomnd(info);
		}
		else if (_isinteractive(info))
			_myputchar('\n');
		_freeinfo(info, 0);
	}
	print_history(info);
	_freeinfo(info, 1);
	if (!_isinteractive(info) && info->_status)
		exit(info->_status);
	if (return_builtin == -2)
	{
		if (info->err_num == -1)
			exit(info->status);
		exit(info->_errnum);
	}
	return (return_builtin);
}

/**
 * _forkcomnd - Forks an executable command to run the command .
 * @info: The structure of the parameter .
 * Return: Void .
 */

void _forkcomnd(info_t *info)
{
	pid_t pid_child;

	pid_child = fork();
	if (pid_child == -1)
	{
		/* TODO: Write the error function */
		perror("Error:");
		return;
	}
	if (pid_child == 0)
	{
		if (execve(info->f_path, info->argv, get_env_cpy(info)) == -1)
		{
			free_info(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
		/* TODO: Write the error function */
	}
	else
	{
		wait(&(info->_status));
		if (WIFEXITED(info->_status))
		{
			info->_status = WEXITSTATUS(info->_status);
			if (info->_status == 126)
				_printerr(info, "The permission is refused\n");
		}
	}
}

/**
 * builtin_find - Finds the builtin command .
 * @info: The structure of the parameter .
 * Return: -1 If builtins are not located,
 * 0 if builtin is successfully implemented,
 * 1 if builtin didn't find or wasn't successful,
 * 2 if the builtin signal comes out.
 */

int builtin_find(info_t *info)
{
	int index, builtin_return = -1;
	builtin_t built_intbl[] = {
		{"exit", exit_sh},
		{"env", print_env},
		{"help", get_help},
		{"history", _dishistory},
		{"setenv", mod_setenv},
		{"unsetenv", rmv_unsetenv},
		{"cd", _mycd},
		{"alias", m_alias},
		{NULL, NULL}
	};

	for (index = 0; built_intbl[index].type; index++)
		if (comp_str(info->argv[0], built_intbl[index].type) == 0)
		{
			info->_linecount++;
			builtin_return = built_intbl[i].fnc(info);
			break;
		}
	return (builtin_return);
}
