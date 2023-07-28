#include "shell.h"

/**
 * _findpath - Finds the command in a given path string .
 * @comnd: The command to be finded .
 * @info: The information structure .
 * @str_path: The path string .
 * Return: If found full path of the command; otherwise NULL .
 */

char *_findpath(info_t *info, char *str_path, char *comnd)
{
	int index = 0, _currpos = 0;
	char *f_path;

	if (!str_path)
		return (NULL);
	if ((length_str(comnd) > 2) && begins_with(comnd, "./"))
	{
		if (execut_comnd(info, comnd))
			return (comnd);
	}
	while (1)
	{
		if (!str_path[index] || str_path[index] == ':')
		{
			f_path = _dupcharacter(str_path, _currpos, index);
			if (!*f_path)
				cnct_str(f_path, comnd);
			else
			{
				cnct_str(f_path, "/");
				cnct_str(f_path, comnd);
			}
			if (execut_comnd(info, f_path))
				return (f_path);
			if (!str_path[index])
				break;
			_currpos = index;
		}
		index++;
	}
	return (NULL);
}

/**
 * _dupcharacter - Duplicates the characters .
 * @begin: Begining the index .
 * @end: Ending the index .
 * @str_path: The string of the path .
 * Return: Pointer to the new buffer .
 */

char *_dupcharacter(char *str_path, int begin, int end)
{
	static char buff[1024];
	int index = 0, j = 0;

	for (j = 0, index = begin; index < end; index++)
		if (str_path[index] != ':')
			buff[j++] = str_path[index];
	buff[j] = 0;
	return (buff);
}

/**
 * execut_comnd - Determines if the file is an command which is executable .
 * @f_path: The file of the path .
 * @info: The information structure .
 * Return: On success 1; On error 0 .
 */

int execut_comnd(info_t *info, char *f_path)
{
	struct stat f_st;

	(void)info;
	if (!f_path || stat(f_path, &f_st))
		return (0);

	if (f_st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}
