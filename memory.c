#include "shell.h"

/**
 * bFree - free pointer and NULL address
 * @ptr: address of the pointer
 *
 * Return: 1 if freed, otherwise 0.
 */
int bFree(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}
