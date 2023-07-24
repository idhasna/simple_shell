#include "shell.h"


/**
 * set_env - Set up a new environment variable, and adapt the current one .
 * @varb: The string that represents the environment variable property .
 * @strenvalue: The string represents the environment variable value property .
 * @info: A structure with potential arguments.
 * Used to keep a constant prototype of the function .
 * Return: All the times 0 .
 */

int set_env(info_t *info, char *varb, char *strenvalue)
{
	char *buff = NULL;
	list_t *als_node;
	char *pos;

	if (!varb || !strenvalue)
		return (0);

	buff = malloc(_strlen(varb) + _strlen(strenvalue) + 2);
	if (!buff)
		return (1);
	str_cpy(buff, varb);
	str_cnct(buff, "=");
	str_cnct(buff, strenvalue);
	als_node = info->env;
	while (als_node)
	{
		pos = starts_with(als_node->sttr, varb);
		if (pos && *pos == '=')
		{
			free(als_node->sttr);
			als_node->sttr = buff;
			info->env_changed = 1;
			return (0);
		}
		als_node = als_node->next;
	}
	add_node_end(&(info->env), buff, 0);
	free(buff);
	info->env_changed = 1;
	return (0);
}

/**
 * unset_env - Delete The environment variable .
 * @varb: The string that represent the environment variable property .
 * @info: A structure with potentil arguments. Used
 * to keep a constant prototype of the function .
 * Return: On success 1 , on error 0 .
 */

int unset_env(info_t *info, char *varb)
{
	list_t *als_node = info->env;
	size_t index = 0;
	char *pos;

	if (!als_node || !varb)
		return (0);

	while (als_node)
	{
		pos = starts_with(als_node->sttr, varb);
		if (pos && *pos == '=')
		{
			info->env_changed = delete_node_at_index(&(info->env), index);
			index = 0;
			als_node = info->env;
			continue;
		}
		als_node = als_node->next;
		index++;
	}
	return (info->env_changed);
}

/**
 * get_env_cpy - Returns the array string copy of our environ .
 * @info: A structure with potential arguments. Used
 * to keep a constant prototype of the function .
 * Return: All the times 0 .
 */

char **get_env_cpy(info_t *info)
{
	if (!info->environ || info->env_changed)
	{
		info->environ = list_to_strings(info->env);
		info->env_changed = 0;
	}

	return (info->environ);
}
