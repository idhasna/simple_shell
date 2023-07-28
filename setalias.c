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
		_myputchar(*als_name);
		_myputchar("'\n");
		_myputs(pos + 1);
		_myputs("'\n");
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

int _unsetalias(info_t *info, char *sttr)
{
	char *pos, ch;
	int rtn;

	pos = str_ch(sttr, '=');
	if (!pos)
		return (1);
	ch = *pos;
	*pos = 0;
	rtn = _deletenode(&(info->als),
		node_index(info->als, prefix_node(info->als, sttr, -1)));
	*pos = ch;
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
			als_node = als_node->_next;
		}
		return (0);
	}
	for (index = 1; info->argv[index]; index++)
	{
		pos = str_ch(info->argv[index], '=');
		if (pos)
			_unsetalias(info, info->argv[index]);
		else
			write_alias(prefix_node(info->als, info->argv[index], '='));
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
	write_list(info->_history);
	return (0);

}

/**
 * _set_alias - Sets the alias to the strings .
 * @sttr: An alias of strings .
 * @info: The structure of the parameter .
 * Return: If success 0, if error 1 .
 */

int _set_alias(info_t *info, char *sttr)
{
	char *pos;

	pos = str_ch(sttr, '=');
	if (!pos)
		return (1);

	if (!*++pos)
		return (_unsetalias(info, sttr));

	_unsetalias(info, sttr);
	return (_addnodeend(&(info->als), sttr, 0) == NULL);
}
