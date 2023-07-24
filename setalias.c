#include "shell.h"

/**
 * write_alias - Writes an alias of strings .
 * @als_node: The node of alias .
 * Return: If success 0, If error 1 .
 */

int write_alias(list_t *als_node)
{
	char *pos = NULL, *als_name = NULL;

	if (als_node)
	{
		pos = str_ch(als_node->sttr, '=');
		for (als_name = als_node->sttr; als_name <= pos; als_name++)
		_putchar(*als_name);
		_putchar("'\n");
		_puts(pos + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * _unsetalias - Unsets the alias to the strings .
 * @info: The structure parameter .
 * @sttr: The alias of strings .
 * Return: If success 0, if error 1 .
 */

int _unsetalias(info_t *info, char sttr)
{
	char *pos, charc;
	int rtn;

	pos = str_ch(sttr, '=');
	if (!pos)
		return (1);
	charc = *pos;
	*pos = 0;
	rtn = delete_node_at_index(&(info->als),
		get_node_index(info->als, node_starts_with(info->als, sttr, -1)));
	*pos = charc;
	return (rtn);
}

/**
 * m_alias - It imitates the alias of builtin .
 * @info: A structure with potentiel arguments, used
 * to keep a constant prototype of the function .
 * Return: All the times 0 .
 */

int m_alias(info_t *info)
{
	int index = 0;
	char *pos = NULL;
	list_t *als_node = NULL;

	if (info->argc == 1)
	{
		als_node = info->als;
		while (als_node)
		{
			write_alias(als_node);
			als_node = als_node->next;
		}
		return (0);
	}
	for (index = 1; info->argv[index]; index++)
	{
		pos = str_ch(info->argv[index], '=');
		if (pos)
			_setalias(info, info->argv[index]);
		else
			write_alias(node_starts_with(info->alias, info->argv[index], '='));
}
	return (0);
}

/**
 * _dishistory -  Displays a history list, one command at a time,
 * preceded by a line number starting at 0.
 * @info: A structure with potentiel arguments, used
 * to keep a constant prototype of the function .
 * Return: All the times 0 .
 */

int _dishistory(info_t *info)
{
	write_list(info->history);
	return (0);

}

/**
 * _setalias - Sets the alias to the strings .
 * @sttr: An alias of strings .
 * @info: The structure of the parameter .
 * Return: If success 0, if error 1 .
 */

int _setalias(info_t *info, char *sttr)
{
	char *pos;

	pos = str_ch(sttr, '=');
	if (!pos)
		return (1);

	if (!*++pos)
		return (_unsetalias(info, sttr));

	_unsetalias(info, sttr);
	return (add_node_end(&(info->alias), sttr, 0) == NULL);
}
