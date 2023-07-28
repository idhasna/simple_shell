#include "shell.h"

/**
 * prefix_node - Find the node that starts with a prefix .
 * @_prefix: The string to match .
 * @als_node: The head of the list is pointed .
 * @charc: The next character after the matched prefix .
 * Return: Math the node or NULL .
 */

list_t *prefix_node(list_t *als_node, char *_prefix, char charc)
{
	char *pos = NULL;

	while (als_node)
	{
		pos = begins_with(als_node->sttr, _prefix);
		if (pos && ((charc == -1) || (*pos == charc)))
			return (als_node);
		als_node = als_node->_next;
	}
	return (NULL);
}

/**
 * conve_list_str - Converts to str elements an array of strings from a list .
 * @first: Points to the first node .
 * Return: An array of strings .
 */

char **conve_list_str(list_t *first)
{
	list_t *als_node = first;
	size_t index = length_list(first), k;
	char **sttrs;
	char *sttr;

	if (!first || !index)
		return (NULL);
	sttrs = malloc(sizeof(char *) * (index + 1));
	if (!sttrs)
		return (NULL);
	for (index = 0; als_node; als_node = als_node->_next, index++)
	{
		sttr = malloc(length_str(als_node->sttr) + 1);
		if (!sttr)
		{
			for (k = 0; k < index; k++)
				free(sttrs[k]);
			free(sttrs);
			return (NULL);
		}

		sttr = copy_str(sttr, als_node->sttr);
		sttrs[index] = sttr;
	}
	sttrs[index] = NULL;
	return (sttrs);
}

/**
 * node_index - Find the index of the node .
 * @als_node: Pointer to the node .
 * @first: Pointer to the top of the list .
 * Return: The index of the node; or -1 .
 */

ssize_t node_index(list_t *first, list_t *als_node)
{
	size_t index = 0;

	while (first)
	{
		if (first == als_node)
			return (index);
		first = first->_next;
		index++;
	}
	return (-1);
}

/**
 * length_list - The length of the linked list is determined .
 * @pheader: The pointer of the first node .
 * Return: The size of the list .
 */

size_t length_list(const list_t *pheader)
{
	size_t index = 0;

	while (pheader)
	{
		pheader = pheader->_next;
		index++;
	}
	return (index);
}

/**
 * write_list - Write all the elements of the linked list .
 * @pheader: The pointer of the first node .
 * Return: The size of the list .
 */

size_t write_list(const list_t *pheader)
{
	size_t index = 0;

	while (pheader)
	{
		_myputs(conv_number(pheader->numb, 10, 0));
		_myputchar(':');
		_myputchar(' ');
		_myputs(pheader->sttr ? pheader->sttr : "(NULL)");
		_myputs("\n");
		pheader = pheader->_next;
		index++;
	}
	return (index);
}
