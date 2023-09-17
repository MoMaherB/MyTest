#include "shell.h"

/**
 * getHistoryFile - get history file
 * @info: param struct
 *
 * Return: allocated string containg history file
 */

char *getHistoryFile(info_t *info)
{
	char *buff, *dire;

	dire = _getenv(info, "HOME=");
	if (!dire)
		return (NULL);
	buff = malloc(sizeof(char) * (_strlen(dir) + _strlen(HIST_FILE) + 2));
	if (!buff)
		return (NULL);
	buff[0] = 0;
	_strcpy(buff, dire);
	_strcat(buff, "/");
	_strcat(buff, HIST_FILE);
	return (buff);
}

/**
 * writeHistory - creates a file, or appends to an existing file
 * @info: the parameter struct
 *
 * Return: 1 on success, else -1
 */
int writeHistory(info_t *info)
{
	ssize_t fd;
	char *fileName = getHistoryFile(info);
	list_t *node = NULL;

	if (!fileName)
		return (-1);

	fd = open(fileName, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(fileName);
	if (fd == -1)
		return (-1);
	for (node = info->history; node; node = node->next)
	{
		_putsfd(node->str, fd);
		_putfd('\n', fd);
	}
	_putfd(BUF_FLUSH, fd);
	close(fd);
	return (1);
}

/**
 * readHistory - reads history from file
 * @info: the parameter struct
 *
 * Return: histcount on success, 0 otherwise
 */
int readHistory(info_t *info)
{
	int j, la = 0, linecounter = 0;
	ssize_t fd, rdlen, fsiz = 0;
	struct stat st;
	char *buff = NULL, *filename = getHistoryFile(info);

	if (!filename)
		return (0);

	fd = open(filename, O_RDONLY);
	free(filename);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		fsiz = st.st_size;
	if (fsiz < 2)
		return (0);
	buff = malloc(sizeof(char) * (fsiz + 1));
	if (!buff)
		return (0);
	rdlen = read(fd, buff, fsiz);
	buf[fsiz] = 0;
	if (rdlen <= 0)
		return (free(buff), 0);
	close(fd);
	for (j = 0; j < fsiz; j++)
		if (buff[j] == '\n')
		{
			buff[j] = 0;
			buildHistoryList(info, buff + la, linecounter++);
			la = j + 1;
		}
	if (la != j)
		buildHistoryList(info, buff + la, linecounter++);
	free(buff);
	info->histcount = linecounter;
	while (info->histcount-- >= HIST_MAX)
		deleteNodeAtIndex(&(info->history), 0);
	renumberHistory(info);
	return (info->histcount);
}

/**
 * buildHistoryList - adds entry to a history linked list
 * @info: Structure containing potential arguments. Used to maintain
 * @buf: buffer
 * @linecount: the history linecount, histcount
 *
 * Return: Always 0
 */
int buildHistoryList(info_t *info, char *buf, int linecount)
{
	list_t *no = NULL;

	if (info->history)
		no = info->history;
	addNodeEnd(&no, buf, linecount);

	if (!info->history)
		info->history = no;
	return (0);
}

/**
 * renumberHistory - renumbers the history linked list after changes
 * @info: Structure containing potential arguments. Used to maintain
 *
 * Return: the new histcount
 */
int renumberHistory(info_t *info)
{
	list_t *node = info->history;
	int i = 0;

	while (node)
	{
		node->num = i++;
		node = node->next;
	}
	return (info->histcount = i);
}
