#include "shell.h"

/**
 * **strtow - function that splits a string to two words.
 * @str: string
 * @f: delimiter.
 * Return: NULL or a pointer
 */
char **strtow(char *str, char *f)
{
	int a, b, c, d, nwords = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!f)
		f = " ";
	for (a = 0; str[a] != '\0'; a++)
		if (!is_delim(str[a], f) && (is_delim(str[a + 1], f) || !str[a + 1]))
			nwords++;

	if (nwords == 0)
		return (NULL);
	s = malloc((1 + nwords) * sizeof(char *));
	if (!s)
		return (NULL);
	for (a = 0, b = 0; b < nwords; b++)
	{
		while (is_delim(str[a], f))
			a++;
		c = 0;
		while (!is_delim(str[a + c], f) && str[a + c])
			c++;
		s[b] = malloc((c + 1) * sizeof(char));
		if (!s[b])
		{
			for (c = 0; c < b; c++)
				free(s[c]);
			free(s);
			return (NULL);
		}
		for (d = 0; d < c; d++)
			s[b][d] = str[a++];
		s[b][d] = 0;
	}
	s[b] = NULL;
	return (s);
}

/**
 * **strtow2 - function split words in a string.
 * @str: string
 * @f: the delimiter
 * Return: NULL or a  pointer
 */
char **strtow2(char *str, char f)
{
	int a, b, c, d, nwords = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (a = 0; str[a] != '\0'; a++)
		if ((str[a] != f && str[a + 1] == f) ||
				(str[a] != f && !str[a + 1]) || str[a + 1] == f)
			nwords++;
	if (nwords == 0)
		return (NULL);
	s = malloc((1 + nwords) * sizeof(char *));
	if (!s)
		return (NULL);
	for (a = 0, b = 0; b < nwords; b++)
	{
		while (str[a] == d && str[a] != d)
			a++;
		c = 0;
		while (str[a + c] != f && str[a + c] && str[a + c] != f)
			c++;
		s[b] = malloc((c + 1) * sizeof(char));
		if (!s[b])
		{
			for (c = 0; c < b; c++)
				free(s[c]);
			free(s);
			return (NULL);
		}
		for (d = 0; d < c; d++)
			s[b][d] = str[a++];
		s[b][d] = 0;
	}
	s[b] = NULL;
	return (s);
}

