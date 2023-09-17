#include "shell.h"

/**
 * **strtow - splits a string into words. Repeat delimiters are ignored
 * @str: the input string
 * @d: the delimeter string
 * Return: a pointer to an array of strings, or NULL on failure
 */

char **strtow(char *str, char *d)
{
	int ii, jj, kk, m, numwords = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!d)
		d = " ";
	for (ii = 0; str[ii] != '\0'; ii++)
		if (!isDelim(str[ii], d) && (isDelim(str[ii + 1], d) || !str[ii + 1]))
			numwords++;

	if (numwords == 0)
		return (NULL);
	s = malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return (NULL);
	for (ii = 0, jj = 0; jj < numwords; jj++)
	{
		while (isDelim(str[ii], d))
			ii++;
		kk = 0;
		while (!isDelim(str[ii + kk], d) && str[ii + kk])
			k++;
		s[jj] = malloc((kk + 1) * sizeof(char));
		if (!s[jj])
		{
			for (kk = 0; kk < jj; kk++)
				free(s[kk]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < kk; m++)
			s[jj][m] = str[ii++];
		s[j][m] = 0;
	}
	s[jj] = NULL;
	return (s);
}

/**
 * **strtow2 - splits string into words
 * @str: the input string
 * @d: the delimeter
 * Return: a pointer to an array of strings, or NULL on failure
 */
char **strtow2(char *str, char d)
{
	int ii, jj, kk, m, numwords = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (ii = 0; str[ii] != '\0'; ii++)
		if ((str[ii] != d && str[ii + 1] == d) ||
		    (str[ii] != d && !str[ii + 1]) || str[ii + 1] == d)
			numwords++;
	if (numwords == 0)
		return (NULL);
	s = malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return (NULL);
	for (ii = 0, jj = 0; jj < numwords; jj++)
	{
		while (str[ii] == d && str[ii] != d)
			ii++;
		kk = 0;
		while (str[ii + kk] != d && str[ii + kk] && str[ii + kk] != d)
			kk++;
		s[jj] = malloc((kk + 1) * sizeof(char));
		if (!s[jj])
		{
			for (kk = 0; kk < jj; kk++)
				free(s[kk]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			s[jj][m] = str[ii++];
		s[jj][m] = 0;
	}
	s[jj] = NULL;
	return (s);
}
