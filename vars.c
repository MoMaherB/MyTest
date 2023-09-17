#include "shell.h"

/**
 * isChain - test if current char in buffer is a chain delimeter
 * @info: the parameter struct
 * @buf: the char buffer
 * @p: address of current position in buf
 *
 * Return: 1 if chain delimeter, 0 otherwise
 */
int isChain(info_t *info, char *buf, size_t *p)
{
	size_t k = *p;

	if (buf[k] == '|' && buf[k + 1] == '|')
	{
		buf[k] = 0;
		k++;
		info->cmd_buf_type = CMD_OR;
	}
	else if (buf[k] == '&' && buf[k + 1] == '&')
	{
		buf[k] = 0;
		k++;
		info->cmd_buf_type = CMD_AND;
	}
	else if (buf[k] == ';') /* found end of this command */
	{
		buf[k] = 0; /* replace semicolon with null */
		info->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*p = k;
	return (1);
}

/**
 * checkChain - checks we should continue chaining based on last status
 * @info: the parameter struct
 * @buf: the char buffer
 * @p: address of current position in buf
 * @i: starting position in buf
 * @len: length of buf
 *
 * Return: Void
 */
void checkChain(info_t *info, char *buf, size_t *p, size_t i, size_t len)
{
	size_t k = *p;

	if (info->cmd_buf_type == CMD_AND)
	{
		if (info->status)
		{
			buf[i] = 0;
			k = len;
		}
	}
	if (info->cmd_buf_type == CMD_OR)
	{
		if (!info->status)
		{
			buf[i] = 0;
			k = len;
		}
	}

	*p = k;
}

/**
 * replaceAlias - replaces an aliases in the tokenized string
 * @info: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replaceAlias(info_t *info)
{
	int k;
	list_t *node;
	char *ptr;

	for (k = 0; k < 10; k++)
	{
		node = nodeStartsWith(info->alias, info->argv[0], '=');
		if (!node)
			return (0);
		free(info->argv[0]);
		ptr = _strchr(node->str, '=');
		if (!ptr)
			return (0);
		ptr = _strdup(ptr + 1);
		if (!ptr)
			return (0);
		info->argv[0] = ptr;
	}
	return (1);
}

/**
 * replaceVars - replaces vars in the tokenized string
 * @info: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replaceVars(info_t *info)
{
	int k = 0;
	list_t *node;

	for (k = 0; info->argv[k]; k++)
	{
		if (info->argv[k][0] != '$' || !info->argv[k][1])
			continue;

		if (!_strcmp(info->argv[k], "$?"))
		{
			replaceString(&(info->argv[k]),
				_strdup(convertNumber(info->status, 10, 0)));
			continue;
		}
		if (!_strcmp(info->argv[k], "$$"))
		{
			replaceString(&(info->argv[k]),
				_strdup(convertNumber(getpid(), 10, 0)));
			continue;
		}
		node = nodeStartsWith(info->env, &info->argv[k][1], '=');
		if (node)
		{
			replaceString(&(info->argv[k]),
				_strdup(_strchr(node->str, '=') + 1));
			continue;
		}
		replaceString(&info->argv[k], _strdup(""));

	}
	return (0);
}

/**
 * replaceString - replaces string
 * @old: address of old string
 * @new: new string
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replaceString(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}
