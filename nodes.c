#include "shell.h"

/**
 * _deletenode - Deletes the node at an specific index .
 * @first: The address of pointer to the first node .
 * @_index: The index of the node to be deleted .
 * Return: On success 1, on error 0 .
 */

int _deletenode(list_t **first, unsigned int _index)
{
	list_t *als_node, *prev_node;
	unsigned int index = 0;

	if (!first || !*first)
		return (0);

	if (!_index)
	{
		als_node = *first;
		*first = (*first)->_next;
		free(als_node->sttr);
		free(als_node);
		return (1);
	}
	als_node = *first;
	while (als_node)
	{
		if (index == _index)
		{
			prev_node->next = als_node->_next;
			free(als_node->sttr);
			free(als_node);
			return (1);
		}
		index++;
		prev_node = als_node;
		als_node = als_node->_next;
	}
	return (0);
}

/**
 * _addnodend - A node is added to the end of the list .
 * @sttr: The string file descriptor of the node .
 * @first: The address of the first node .
 * @numb: The node index used by the history .
 * Return: The size of the list .
 */

list_t *_addnodend(list_t **first, const char *sttr, int numb)
{
	list_t *_newnode, *als_node;

	if (!first)
		return (NULL);

	als_node = *first;
	_newnode = malloc(sizeof(list_t));
	if (!_newnode)
		return (NULL);
	memset((void *)_newnode, 0, sizeof(list_t));
	_newnode->numb = numb;
	if (sttr)
	{
		_newnode->sttr = dup_str(sttr);
		if (!_newnode->sttr)
		{
			free(_newnode);
			return (NULL);
		}
	}
	if (als_node)
	{
		while (als_node->_next)
			als_node = als_node->_next;
		als_node->_next = _newnode;
	}
	else
		*first = _newnode;
	return (_newnode);
}

/**
 * list_free - Frees all the nodes of the list .
 * @pntr_head: The address of the pointer to the head node .
 * Return: void .
 */

void list_free(list_t **pntr_head)
{
	list_t *als_node, *_nextnode, *first;

	if (!pntr_head || !*pntr_head)
		return;
	first = *pntr_head;
	als_node = first;
	while (als_node)
	{
		_nextnode = als_node->_next;
		free(als_node->sttr);
		free(als_node);
		als_node = _nextnode;
	}
	*pntr_head = NULL;
}

/**
 * _addnode - Adds the node at the top of the list .
 * @numb: The node index which is used by the history .
 * @sttr: The string file descriptor of the node .
 * @first: Address of pointer to header node .
 * Return: The size of the list .
 */

list_t *_addnode(list_t **first, const char *sttr, int numb)
{
	list_t *_newfirst;

	if (!first)
		return (NULL);
	_newfirst = malloc(sizeof(list_t));
	if (!_newfirst)
		return (NULL);
	_memset((void *)_newfirst, 0, sizeof(list_t));
	_newfirst->numb = numb;
	if (sttr)
	{
		_newfirst->sttr = dup_str(sttr);
		if (!_newfirst->sttr)
		{
			free(_newfirst);
			return (NULL);
		}
	}
	_newfirst->_next = *first;
	*first = _newfirst;
	return (_newfirst);
}

/**
 * write_sttr_list - Writes the strings element of a linked list .
 * @pheader: Poiner to the first node .
 * Return: The size of the linked list .
 */

size_t write_sttr_list(const list_t *pheader)
{
	size_t index = 0;

	while (pheader)
	{
		_myputs(pheader->sttr ? pheader->sttr : "(NULL)");
		_myputs("\n");
		pheader = pheader->_next;
		index++;
	}
	return (index);
}
