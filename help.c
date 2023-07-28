#include "shell.h"

/**
 * change_cd - Changes the process's current directory .
 * @info:  A structure with potential arguments. Used to
 * keep a constant prototype of the function.
 * Return: All the times 0 .
 */

int change_cd(info_t *info)
{
	char *sttr, *diry, buffer[1024];
	int chdir_output;


	sttr = getcwd(buffer, 1024);
	if (!sttr)
		_myputs("TODO: >>getcwd non-success msg here<<\n");

	if (!info->argv[1])
	{
		diry = get_env(info, "HOME=");
		if (!diry)
			chdir_output = /* TODO:What's this supposed to be about? */
				chdir((diry = get_env(info, "PWD=")) ? diry : "/");
		else
			chdir_output = chdir(diry);
	}
	else if (comp_str(info->argv[1], "-") == 0)
	{
		if (!get_env(info, "OLDPWD="))
		{
			_myputs(sttr);
			_myputchar('\n');
			return (1);
		}
		_myputs(get_env(info, "OLDPWD=")), _myputchar('\n');
		chdir_output = /* TODO: What's this supposed to be about? */
			chdir((diry = get_env(info, "OLDPWD=")) ? diry : "/");
	}
	else
	{
		chdir_output = chdir(info->argv[1]);
	}
	if (chdir_output == -1)
	{
		_printerr(info, "can't change the directory to ");
		my_eputs(info->argv[1]), my_eputchar('\n');
	}
	else
	{
		set_env(info, "OLDPWD", get_env(info, "PWD="));
		set_env(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * exit_sh - It exits the shell .
 * @info: A structure with potential arguments. Used to
 * keep a constant prototype of the function.
 * Return: If 0 exit .
 */

int exit_sh(info_t *info)
{
	int status_exit;

	if (info->argv[1]) /* If there is an arguement on the exit */
	{
		status_exit = err_atoi(info->argv[1]);
		if (status_exit == -1)
		{
			info->_status = 2;
			_printerr(info, "Illicit number: ");
			my_eputs(info->argv[1]);
			my_eputchar('\n');
			return (1);
		}
		info->_errnum = err_atoi(info->argv[1]);
		return (-2);
	}
	info->_errnum = -1;
	return (-2);
}

/**
 * get_help - Changes the existing directory for this process .
 * @info: A structure with potential arguments. Used to
 * keep a constant prototype of the function.
 * Return: All the times 0 .
 */

int get_help(info_t *info)
{
	char **arg_array;

	arg_array = info->argv;
	_myputs("The help call working. The function is not yet implemented \n");
	if (0)
		_myputs(*arg_array);
	return (0);
}
