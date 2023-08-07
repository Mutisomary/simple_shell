#include "shell.h"

/**
 * _memset - program fills memory.
 * @s: the pointer.
 * @a: bytes.
 * @j: number of bytes.
 * Return: pointer.
 */
char *_memset(char *s, char a, unsigned int j)
{
	unsigned int k;

	for (k = 0; k < j; k++)
		s[k] = a;
	return (s);
}

/**
 * ffree - entry point.
 * @p: string.
 */
void ffree(char **p)
{
	char **k = p;

	if (!p)
		return;
	while (*p)
		free(*p++);
	free(k);
}

/**
 * _realloc - program reallocates memory.
 * @ptr: pointer.
 * @old_size: old block of byte size.
 * @new_size: new block of byte size.
 *
 * Return: pointer.
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *k;

	if (!ptr)
		return (malloc(new_size));
	if (!new_size)
		return (free(ptr), NULL);
	if (new_size == old_size)
		return (ptr);

	k = malloc(new_size);
	if (!k)
		return (NULL);

	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		k[old_size] = ((char *)ptr)[old_size];
	free(ptr);
	return (k);
}
