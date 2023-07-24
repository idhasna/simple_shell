#include "shell.h"

/**
 * get_line - Get the next line of STDIN input .
 * @pntr: The adress of pointer to buffer .
 * @info: The structure of a parameter .
 * @_bufflength: The size of preallocated buffer if it's not NULL .
 * Return: To the string .
 */

int get_line(info_t *info, char **pntr, size_t *_bufflength)
{
	static char buff[READ_BUF_SIZE];
	static size_t index, _bufflen;
	size_t count;
	ssize_t result = 0, sttr = 0;
	char *pos = NULL, *new_pos = NULL, *charc;

	pos = *pntr;
	if (pos && _bufflength)
		sttr = *_bufflength;
	if (index == _bufflen)
		index = _bufflen = 0;

	result = read_buf(info, buff, &_bufflen);
	if (result == -1 || (result == 0 && _bufflen == 0))
		return (-1);

	charc = str_ch(buff + index, '\n');
	count = charc ? 1 + (unsigned int)(c - buf) : len;
	new_pos = _realloc(pos, sttr, sttr ? sttr + count : count + 1);
	if (!new_pos) /* NON6SUCCESS OF MALLOC ! */
		return (pos ? free(pos), -1 : -1);

	if (sttr)
		str_cnct(new_pos, buff + index, count - index);
	else
		str_cpy(new_pos, buff + index, count - index + 1);

	sttr += count - index;
	index = count;
	pos = new_pos;

	if (_bufflength)
		*_bufflength = sttr;
	*pntr = pos;
	return (sttr);
}

/**
 * _getinput - Gets a line that's minus the newline .
 * @info: The structure of the parameter .
 * Return: The amount of bytes read .
 */

ssize_t _getinput(info_t *info)
{
	static char *buff; /* the ';' command chain buffer */
	static size_t index, j, _bufflen;
	ssize_t result = 0;
	char **_buffpos = &(info->arg), *pos;

	_putchar(BUF_FLUSH);
	result = _buffinput(info, &buff, &_bufflen);
	if (result == -1) /* End Of File */
		return (-1);
	if (_bufflen) /* In the chain buffer, we've got commands left. */
	{
		j = index; /* initialize new iterator into the buf position */
		pos = buff + index; /* For return get a pointer */

		check_chain(info, buff, &j, index, _bufflen);
		while (j < _bufflen)
		{
			if (is_chain(info, buff, &j))
				break;
			j++;
		}

		index = j + 1;
		if (i >= _bufflen) /* Is the buffer reached its end?*/
		{
			index = _bufflen = 0; /* Init length and position */
			info->cmd_buf_type = CMD_NORM;
		}

		*_buffpos = pos; /* Return  pointer to existing command position */
		return (_strlen(pos)); /* Return  length of present command */
	}

	*_buffpos = buff; /* Return buffer from get_line(), if it's not a chain*/
	return (result); /* Return length of buffer from get_line() */
}

/**
 * _siginthandler - Handles the signit (ctrl-C) .
 * @_signumb - The signal number .
 * Return: Void .
 */

void _siginthandler(__attribute__((unused))int _signumb)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}

/**
 * _buffinput - The buffers of chained commands .
 * @_bufflen: The adress of the length .
 * @buff: The adress of the buffer .
 * @info: The structure of the parameter .
 */

ssize_t _buffinput(info_t *info, char **buff, size_t *_bufflen)
{
	ssize_t result = 0;
	size_t _lenpos = 0;

	if (!*_bufflen) /* Fill it up if nothing's left of the buffer. */
	{
		free(*buff);
		*buff = NULL;
		signal(SIGINT, _siginthandler);
#if USE_GETLINE
		result = get_line(buff, &_lenpos, stdin);
#else
		result = get_line(info, buff, &_lenpos);
#endif
		if (result > 0)
		{
			if ((*buff)[result - 1] == '\n')
			{
				(*buff)[result - 1] = '\0'; /* Delete The trailing newline */
				result--;
			}
			info->linecount_flag = 1;
			rmv_comment(*buff);
			build_history_list(info, *buff, info->histcount++);
			{
				*_bufflen = result;
				info->cmd_buf = buff;
			}
		}
	}
	return (result);
}

/**
 * _buffread - It reads the buffer .
 * @buff: The buffer .
 * @info: The structure of the parameter .
 * @index: The size of buffers .
 */

ssize_t _buffread(info_t *info, char *buff, size_t *index)
{
	ssize_t result = 0;

	if (*index)
		return (0);
	result = read(info->readfd, buff, READ_BUF_SIZE);
	if (result >= 0)
		*index = result;
	return (result);
}
