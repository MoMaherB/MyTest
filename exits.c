#include "shell.h"

/**
 **_strncpy - copy a string
 *@dest: the destination string to be copied to
 *@src: source string
 *@n: amount of characters copied
 *Return: the concatenat string
 */
char *_strncpy(char *dest, char *src, int n)
{
	int ii, jj;
	char *str = dest;

	ii = 0;
	while (src[ii] != '\0' && ii < n - 1)
	{
		dest[ii] = src[ii];
		ii++;
	}
	if (ii < n)
	{
		jj = ii;
		while (jj < n)
		{
			dest[jj] = '\0';
			jj++;
		}
	}
	return (str);
}

/**
 **_strncat - concatenates two strings
 *@dest: first string
 *@src: second string
 *@n: amount of bytes to be maximal used
 *Return: concatenated string
 */
char *_strncat(char *dest, char *src, int n)
{
	int ii, jj;
	char *str = dest;

	ii = 0;
	jj = 0;
	while (dest[ii] != '\0')
		ii++;
	while (src[jj] != '\0' && jj < n)
	{
		dest[ii] = src[jj];
		ii++;
		jj++;
	}
	if (jj < n)
		dest[ii] = '\0';
	return (str);
}

/**
 **_strchr - locate a char in a str
 *@s: string to be parsed
 *@c: character to look for
 *Return: (s) a pointer to the memory area s
 */
char *_strchr(char *s, char c)
{
	do {
		if (*s == c)
			return (s);
	} while (*s++ != '\0');

	return (NULL);
}
