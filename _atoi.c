#include "shell.h"

/**
 * interactive - ret true if shell is interactive mode
 * @info: struct add
 *
 * Return: 1 if interactiv mode, 0 otherwise
 */
int interactive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * isDelim - checks if char is a delim
 * @c: the char to check
 * @delim: the delimeter string
 * Return: 1 , 0
 */
int isDelim(char c, char *delim)
{
	while (*delim)
		if (*delim++ == c)
			return (1);
	return (0);
}

/**
 *_isalpha - checks alphabetic char
 *@c: char to input
 *Return: 1 if c is alphabet, 0 otherwise
 */

int _isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 *_atoi - convert str to int
 *@s: string to be convert
 *Return: 0 if no numbers in string, converted number otherwise
 */

int _atoi(char *s)
{
	int k, sign = 1, fl = 0, outP;
	unsigned int res = 0;

	for (k = 0;  s[k] != '\0' && fl != 2; k++)
	{
		if (s[k] == '-')
			sign *= -1;

		if (s[k] >= '0' && s[k] <= '9')
		{
			fl = 1;
			res *= 10;
			res += (s[i] - '0');
		}
		else if (fl == 1)
			fl = 2;
	}

	if (sign == -1)
		outP = -res;
	else
		outP = res;

	return (outP);
}

