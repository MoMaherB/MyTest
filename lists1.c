#include "shell.h"

/**
 * listLen - determines length of linked list
 * @h: pointer to first node
 *
 * Return: size of list
 */
size_t listLen(const list_t *h)
{
	size_t k = 0;

	while (h)
	{
		h = h->next;
		k++;
	}
	return (k);
}

/**
 * listToStrings - returns an array of strings of the list->str
 * @head: pointer to first node
 *
 * Return: array of strings
 */
char **listToStrings(list_t *head)
{
	list_t *node = head;
	size_t i = listLen(head), j;
	char **strS;
	char *str;

	if (!head || !i)
		return (NULL);
	strS = malloc(sizeof(char *) * (i + 1));
	if (!strS)
		return (NULL);
	for (i = 0; node; node = node->next, i++)
	{
		str = malloc(_strlen(node->str) + 1);
		if (!str)
		{
			for (j = 0; j < i; j++)
				free(strS[j]);
			free(strS);
			return (NULL);
		}

		str = _strcpy(str, node->str);
		strS[i] = str;
	}
	strS[i] = NULL;
	return (strS);
}


/**
 * printList - prints all elements of a list_t linked list
 * @h: pointer to first node
 *
 * Return: size of list
 */
size_t printList(const list_t *h)
{
	size_t k = 0;

	while (h)
	{
		_puts(convertNumber(h->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		k++;
	}
	return (k);
}

/**
 * nodeStartsWith - returns node whose string starts with prefix
 * @node: pointer to list head
 * @prefix: string to match
 * @c: the next character after prefix to match
 *
 * Return: match node or null
 */
list_t *nodeStartsWith(list_t *node, char *prefix, char c)
{
	char *ptr = NULL;

	while (node)
	{
		ptr = startsWith(node->str, prefix);
		if (ptr && ((c == -1) || (*ptr == c)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * getNodeIndex - gets the index of a node
 * @head: pointer to list head
 * @node: pointer to the node
 *
 * Return: index of node or -1
 */
ssize_t getNodeIndex(list_t *head, list_t *node)
{
	size_t k = 0;

	while (head)
	{
		if (head == node)
			return (k);
		head = head->next;
		k++;
	}
	return (-1);
}
