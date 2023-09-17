#include "shell.h"

/**
 * _myhistory - displays history list, one command by line
 * @info: Structure containing potential arguments
 *  Return: Always 0
 */
int _myhistory(info_t *info)
{
	printList(info->history);
	return (0);
}

/**
 * unsetAlias - sets alias to string
 * @info: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int unsetAlias(info_t *info, char *str)
{
	char *ptr, ch;
	int re;

	ptr = _strchr(str, '=');
	if (!ptr)
		return (1);
	ch = *ptr;
	*ptr = 0;
	re = deleteNodeAtIndex(&(info->alias),
		getNodeIndex(info->alias, nodeStartsWith(info->alias, str, -1)));
	*ptr = ch;
	return (re);
}

/**
 * setAlias - sets alias to string
 * @info: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int setAlias(info_t *info, char *str)
{
	char *ptr;

	ptr = _strchr(str, '=');
	if (!ptr)
		return (1);
	if (!*++ptr)
		return (unsetAlias(info, str));

	unsetAlias(info, str);
	return (addNodeEnd(&(info->alias), str, 0) == NULL);
}

/**
 * printAlias - prints an alias string
 * @node: the alias node
 *
 * Return: Always 0 on success, 1 on error
 */
int printAlias(list_t *node)
{
	char *ptr = NULL, *aa = NULL;

	if (node)
	{
		ptr = _strchr(node->str, '=');
		for (aa = node->str; aa <= ptr; aa++)
			_putchar(*aa);
		_putchar('\'');
		_puts(ptr + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * _myalias - mimics the alias builtin (man alias)
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int _myalias(info_t *info)
{
	int k = 0;
	char *p = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			printAlias(node);
			node = node->next;
		}
		return (0);
	}
	for (k = 1; info->argv[k]; k++)
	{
		p = _strchr(info->argv[k], '=');
		if (p)
			setAlias(info, info->argv[k]);
		else
			printAlias(nodeStartsWith(info->alias, info->argv[k], '='));
	}

	return (0);
}
