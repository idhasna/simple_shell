#include "shell.h"

/**
 * rep_vars - Replaces the variables in the tokenized string .
 * @info: The structure of the parameter .
 * Return: 1 if success, 0 otherwise .
 */

int rep_vars(info_t *info)
{
	int index = 0;
	list_t *als_node;

	for (index = 0; info->argv[index]; index++)
	{
		if (info->argv[index][0] != '$' || !info->argv[index][1])
			continue;

		if (!comp_str(info->argv[index], "$?"))
		{
			rep_str(&(info->argv[index]),
					dup_str(conv_number(info->status, 10, 0)));
			continue;
		}
		if (!comp_str(info->argv[index], "$$"))
		{
			rep_str(&(info->argv[index]),
					dup_str(conv_number(getpid(), 10, 0)));
			continue;
		}
		als_node = prefix_node(info->env, &info->argv[index][1], '=');
		if (als_node)
		{
			rep_str(&(info->argv[index]),
					dup_str(str_ch(als_node->sttr, '=') + 1));
			continue;
		}
		rep_str(&info->argv[index], dup_str(""));

	}
	return (0);
}

/**
 * chain_check - We're supposed to continue chaining, based on the last statu .
 * @index: The first position in the buffer .
 * @buff: The buffer of the characters .
 * @_bufflen: The buffer length .
 * @info: The structure of the parameter .
 * @pos: The address of the current position of the buffer .
 * Return: void .
 */

void chain_check(info_t *info, char *buff, size_t *pos,
		size_t index, size_t _bufflen)
{
	size_t x = *pos;

	if (info->cmd_buf_type == CMD_AND)
	{
		if (info->status)
		{
			buff[index] = 0;
			x = _bufflen;
		}
	}
	if (info->cmd_buf_type == CMD_OR)
	{
		if (!info->status)
		{
			buff[index] = 0;
			x = _bufflen;
		}
	}

	*pos = x;
}

/**
 * rep_str - Replaces the strings .
 * @pre: The address of the previous string .
 * @cur: The address of the current string .
 * Return: 1 on success, 0 otherwise .
 */

int rep_str(char **pre, char *cur)
{
	free(*pre);
	*pre = cur;
	return (1);
}

/**
 * _ischain - Verify that the current char in the buffer is a chain delimeter .
 * @pos: The address of the current position in the buffer .
 * @buff: The buffer of the character .
 * @info: The structure of the parameter .
 * Return: 1 on success, 0 otherwise .
 */

int _ischain(info_t *info, char *buff, size_t *pos)
{
	size_t x = *pos;

	if (buff[x] == '|' && buff[x + 1] == '|')
	{
		buff[x] = 0;
		x++;
		info->cmd_buf_type = CMD_OR;
	}
	else if (buff[x] == '&' && buff[x + 1] == '&')
	{
		buff[x] = 0;
		x++;
		info->cmd_buf_type = CMD_AND;
	}
	else if (buff[x] == ';') /* Found the end of this command */
	{
		buff[x] = 0; /* Replace the semicolon with null */
		info->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*pos = x;
	return (1);
}

/**
 * rep_als - Replaces the tokenized string's aliass .
 * @info: The structure of the parameter .
 * Return: 1 on success, 0 otherwise .
 */

int rep_als(info_t *info)
{
	int index;
	list_t *als_node;
	char *pos;

	for (index = 0; index < 10; index++)
	{
		als_node = prefix_node(info->alias, info->argv[0], '=');
		if (!als_node)
			return (0);
		free(info->argv[0]);
		pos = str_ch(als_node->sttr, '=');
		if (!pos)
			return (0);
		pos = dup_str(pos + 1);
		if (!pos)
			return (0);
		info->argv[0] = pos;
	}
	return (1);
}
