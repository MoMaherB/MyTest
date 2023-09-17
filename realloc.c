#include "shell.h"

/**
 **_memset - fills memo with  cont byte
 *@s: pointer to the mem area
 *@b: byte to fill *s with
 *@n: amount of bytes to be filled
 *Return: (s) a point to the mem area s
 */
char *_memset(char *s, char b, unsigned int n)
{
	unsigned int k;

	for (k = 0; k < n; k++)
		s[k] = b;
	return (s);
}

/**
 * ffree - free str of strings
 * @pp: string of strings
 */
void ffree(char **pp)
{
	char **aa = pp;

	if (!pp)
		return;
	while (*pp)
		free(*pp++);
	free(aa);
}

/**
 * _realloc - reallocate a block of memory
 * @ptr: pointer to previous malloc
 * @old_size: byte size of prev block
 * @new_size: byte size of the new block
 *
 * Return: pointer .
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *pp;

	if (!ptr)
		return (malloc(new_size));
	if (!new_size)
		return (free(ptr), NULL);
	if (new_size == old_size)
		return (ptr);

	pp = malloc(new_size);
	if (!pp)
		return (NULL);

	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		p[old_size] = ((char *)ptr)[old_size];
	free(ptr);
	return (pp);
}
