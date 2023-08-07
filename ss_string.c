#include "shell.h"

/**
 * _strlen - function checks for string length.
 * @s: string.
 *
 * Return: length.
 */
int _strlen(char *s)
{
	int a = 0;

	if (!s)
		return (0);

	while (*s++)
		a++;
	return (a);
}

/**
 * _strcmp - compares two strangs.
 * @s1: string 1.
 * @s2: string 2.
 *
 * Return: 0, negative or positive.
 */
int _strcmp(char *s1, char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}
	if (*s1 == *s2)
		return (0);
	else
		return (*s1 < *s2 ? -1 : 1);
}

/**
 * starts_with - looks for haystack in the beginning of a string.
 * @haystack: strig.
 * @needle: sunstring.
 *
 * Return: address of character followingg haystack.
 */
char *starts_with(const char *haystack, const char *needle)
{
	while (*needle)
		if (*needle++ != *haystack++)
			return (NULL);
	return ((char *)haystack);
}

/**
 * _strcat - function joins  two strings
 * @dest: destination
 * @src: source
 *
 * Return: pointer to destination buffer
 */
char *_strcat(char *dest, char *src)
{
	char *ret = dest;

	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;
	*dest = *src;
	return (ret);
}

