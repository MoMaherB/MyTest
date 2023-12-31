#include "shell.h"

/**
 * clearInfo - initializes info_t struct
 * @info: struct address
 */
void clearInfo(info_t *info)
{
	info->arg = NULL;
	info->argv = NULL;
	info->path = NULL;
	info->argc = 0;
}

/**
 * setInfo - initializes info_t struct
 * @info: struct address
 * @av: argument vector
 */
void setInfo(info_t *info, char **av)
{
	int k = 0;

	info->fname = av[0];
	if (info->arg)
	{
		info->argv = strtow(info->arg, " \t");
		if (!info->argv)
		{

			info->argv = malloc(sizeof(char *) * 2);
			if (info->argv)
			{
				info->argv[0] = _strdup(info->arg);
				info->argv[1] = NULL;
			}
		}
		for (k = 0; info->argv && info->argv[k]; k++)
			;
		info->argc = k;

		replaceAlias(info);
		replaceVars(info);
	}
}

/**
 * freeInfo - frees info_t struct fields
 * @info: struct address
 * @all: true if freeing all fields
 */
void freeInfo(info_t *info, int all)
{
	ffree(info->argv);
	info->argv = NULL;
	info->path = NULL;
	if (all)
	{
		if (!info->cmd_buf)
			free(info->arg);
		if (info->env)
			freeList(&(info->env));
		if (info->history)
			freeList(&(info->history));
		if (info->alias)
			freeList(&(info->alias));
		ffree(info->environ);
			info->environ = NULL;
		bFree((void **)info->cmd_buf);
		if (info->readfd > 2)
			close(info->readfd);
		_putchar(BUF_FLUSH);
	}
}
