#include "shell.h"

/**
 *_eputs - print inp str
 * @str: printed string t
 *
 * Return: Nothing
 */
void _eputs(char *str)
{
	int k = 0;

	if (!str)
		return;
	while (str[k] != '\0')
	{
		_eputchar(str[k]);
		k++;
	}
}

/**
 * _eputchar - write char c to stderr
 * @c: char to print
 *
 * Return: On success 1.
 * On error, -1 is returned
 */
int _eputchar(char c)
{
	static int k;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || k >= WRITE_BUF_SIZE)
	{
		write(2, buf, k);
		k = 0;
	}
	if (c != BUF_FLUSH)
		buf[k++] = c;
	return (1);
}

/**
 * _putfd - write char c to given fd
 * @c: The character to print
 * @fd: The filedescriptor to write to
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putfd(char c, int fd)
{
	static int k;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || k >= WRITE_BUF_SIZE)
	{
		write(fd, buf, k);
		k = 0;
	}
	if (c != BUF_FLUSH)
		buf[k++] = c;
	return (1);
}

/**
 *_putsfd - print input str
 * @str: string to be printed
 * @fd: filedescriptor to write to
 *
 * Return: number of chars put
 */
int _putsfd(char *str, int fd)
{
	int k = 0;

	if (!str)
		return (0);
	while (*str)
	{
		k += _putfd(*str++, fd);
	}
	return (k);
}
