#include "shell.h"

/**
 * list_history - Adds an entry from a list that is linked to history .
 * @buff: The buffer .
 * @info: A structure with a potential arguments. Used
 * to keep a constant prototype of the function .
 * @line_count: The linecount of the history .
 * Return: All the times 0 .
 */

int list_history(info_t *info, char *buff, int line_count)
{
	list_t *als_node = NULL;

	if (info->_history)
		als_node = info->_history;
	add_node_end(&als_node, buff, line_count);

	if (!info->_history)
		info->_history = als_node;
	return (0);
}

/**
 * print_history - create a new file, or add to the current file .
 * @info: The structure of the parameter .
 * Return: On success 1, on error -1 .
 */

int print_history(info_t *info)
{
	ssize_t file_des;
	char *f_name = _gethistory(info);
	list_t *als_node = NULL;

	if (!f_name)
		return (-1);

	file_des = open(f_name, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(f_name);
	if (file_des == -1)
		return (-1);
	for (als_node = info->_history; als_node; als_node = als_node->_next)
	{
		my_putsfd(als_node->sttr, file_des);
		_myputfd('\n', file_des);
	}
	_myputfd(BUF_FLUSH, file_des);
	close(file_des);
	return (1);
}

/**
 * _renumbhistory - After modifications the history link list is renumbered .
 * @info: A structure with potential arguments. Used
 * to keep a constant prototype of the function .
 * Return: The histcount which is new .
 */

int _renumbhistory(info_t *info)
{
	list_t *als_node = info->_history;
	int index = 0;

	while (als_node)
	{
		als_node->numb = index++;
		als_node = als_node->_next;
	}
	return (info->hist_count = index);
}

/**
 * _gethistory - Gets the file of the history .
 * @info: The structure of the parameter .
 * Return: Appended string that contain the history file .
 */

char *_gethistory(info_t *info)
{
	char *buff, *diry;

	diry = get_env(info, "HOMEDIR=");
	if (!diry)
		return (NULL);
	buff = malloc(sizeof(char) * (length_str(diry) + length_str(HIST_FILE) + 2));
	if (!buff)
		return (NULL);
	buff[0] = 0;
	str_cpy(buff, diry, BUFSIZ);
	str_cnct(buff, "/", BUFSIZ);
	str_cnct(buff, HIST_FILE, BUFSIZ);
	return (buff);
}

/**
 * _readhistory - Read the history's file; add it to the history linked list .
 * @info: The structure of the parameter .
 * Return: On success histcount, on error 0 .
 */

int _readhistory(info_t *info)
{
	int index, last = 0, line_count = 0;
	ssize_t file_des, rd_len, filesize = 0;
	struct stat st;
	char *buff = NULL, *filename = _gethistory(info);

	if (!filename)
		return (0);

	file_des = open(filename, O_RDONLY);
	free(filename);
	if (file_des == -1)
		return (0);
	if (!fstat(file_des, &st))
		filesize = st.st_size;
	if (filesize < 2)
		return (0);
	buff = malloc(sizeof(char) * (filesize + 1));
	if (!buff)
		return (0);
	rd_len = read(file_des, buff, filesize);
	buff[filesize] = 0;
	if (rd_len <= 0)
		return (free(buff), 0);
	close(file_des);
	for (index = 0; index < filesize; index++)
		if (buff[index] == '\n')
		{
			buff[index] = 0;
			list_history(info, buff + last, line_count++);
			last = index + 1;
		}
	if (last != index)
		list_history(info, buff + last, line_count++);
	free(buff);
	info->hist_count = line_count;
	while (info->hist_count-- >= HIST_MAX)
		_deletenode(&(info->_history), 0);
	_renumbhistory(info);
	return (info->hist_count);
}
