#include "shell.h"

/**
 * isCmd - determine if  file is an executable command
 * @info: info struct
 * @path: path to file
 *
 * Return: 1 if true, 0 otherwise
 */
int isCmd(info_t *info, char *path)
{
	struct stat sta;

	(void)info;
	if (!path || stat(path, &sta))
		return (0);

	if (sta.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * dupChars - duplicates characters
 * @pathstr: the PATH string
 * @start: starting index
 * @stop: stopping index
 *
 * Return: pointer to new buffer
 */
char *dupChars(char *pathstr, int start, int stop)
{
	static char buf[1024];
	int ii = 0, kk = 0;

	for (kk = 0, ii = start; ii < stop; ii++)
		if (pathstr[ii] != ':')
			buf[kk++] = pathstr[ii];
	buf[kk] = 0;
	return (buf);
}

/**
 * findPath - finds cmd in the PATH string
 * @info: info struct
 * @pathstr: the PATH string
 * @cmd: cmd to find
 *
 * Return: full path of cmd or NULL
 */
char *findPath(info_t *info, char *pathstr, char *cmd)
{
	int k = 0, cur_pos = 0;
	char *pa;

	if (!pathstr)
		return (NULL);
	if ((_strlen(cmd) > 2) && startsWith(cmd, "./"))
	{
		if (isCmd(info, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pathstr[k] || pathstr[k] == ':')
		{
			pa = dupChars(pathstr, cur_pos, k);
			if (!*pa)
				_strcat(pa, cmd);
			else
			{
				_strcat(pa, "/");
				_strcat(pa, cmd);
			}
			if (isCmd(info, pa))
				return (pa);
			if (!pathstr[k])
				break;
			cur_pos = k;
		}
		k++;
	}
	return (NULL);
}
