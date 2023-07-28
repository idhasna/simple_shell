#include "shell.h"

/**
 * rmv_unsetenv - The environment variable is removed .
 * @info: A structure with potential arguments. Used
 * to keep a constant prototype of the function.
 * Return: All the times 0 .
 */

int rmv_unsetenv(info_t *info)
{
	int index;

	if (info->argc == 1)
	{
		my_eputs("One or two arguements.\n");
		return (1);
	}
	for (index = 1; index <= info->argc; index++)
		unset_env(info, info->argv[index]);

	return (0);
}

/**
 * get_env - Getting the value of an environ variable .
 * @name: The name of an environment variable .
 * @info: A structure with potential arguments. Used
 * to keep a constant prototype of the function .
 * Return: Write the value .
 */

char *get_env(info_t *info, const char *name)
{
	list_t *als_node = info->env;
	char *pos;

	while (als_node)
	{
		pos = begins_with(als_node->sttr, name);
		if (pos && *pos)
			return (pos);
		als_node = als_node->_next;
	}
	return (NULL);
}

/**
 * pop_envlist - A linked list of populates environment .
 * @info: A structure with potential arguments. Used
 * to keep a constant prototype of the function .
 * Return: all the times 0 .
 */

int pop_envlist(info_t *info)
{
	list_t *als_node = NULL;
	size_t index;

	for (index = 0; _environ[index]; index++)
		_addnodeend(&als_node, _environ[index], 0);
	info->env = als_node;
	return (0);
}

/**
 * print_env - Writes the current environment .
 * @info: A structure with potential arguments. Used
 * to keep a constant prototype of the function .
 * Return: All the times 0 .
 */

int print_env(info_t *info)
{
	write_sttr_list(info->env);
	return (0);
}

/**
 * mod_setenv - Initialize a new environment parameter,
 * or make changes to the existing one .
 * @info: A structure with potential arguments. Used
 * to keep a constant prototype of the function .
 * Return: All the times 0 .
 */

int mod_setenv(info_t *info)
{
	if (info->argc != 3)
	{
		_myeputs("The number of arguements is incorrect\n");
		return (1);
	}
	if (set_env(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}
