#include "shell.h"

/**
 **_strncpy - program copies a string
 *@dest: destination string.
 *@src: source string
 *@k:characters to be copied.
 *Return: concatenated string
 */
char *_strncpy(char *dest, char *src, int k)
{
	int a, b;
	char *s = dest;

	a = 0;
	while (src[a] != '\0' && a < k - 1)
	{
		dest[a] = src[a];
		a++;
	}
	if (a < k)
	{
		b = a;
		while (b < k)
		{
			dest[b] = '\0';
			b++;
		}
	}
	return (s);
}

/**
 **_strncat - function joins two strings
 *@dest: string 1
 *@src: string 2.
 *@k: bytes.
 *Return: concatenated string
 */
char *_strncat(char *dest, char *src, int k)
{
	int a, b;
	char *s = dest;

	a = 0;
	b = 0;
	while (dest[a] != '\0')
		a++;
	while (src[b] != '\0' && b < k)
	{
		dest[a] = src[b];
		a++;
		b++;
	}
	if (b < k)
		dest[a] = '\0';
	return (s);
}

/**
 **_strchr - function checks for a character in a string
 *@s: string
 *@m: character.
 *Return: pointer.
 */
char *_strchr(char *s, char m)
{
	do {
		if (*s == m)
			return (s);
	} while (*s++ != '\0');

	return (NULL);
}

