#include "shell.h"

/**
 * _eputs - program prints an input string.
 * @str: string
 *
 * Return: 0.
 */
void _eputs(char *str)
{
	int a = 0;

	if (!str)
		return;
	while (str[a] != '\0')
	{
		_eputchar(str[a]);
		a++;
	}
}

/**
 * _eputchar - program writes the character m to stderr
 * @m: character
 *
 * Return: 1, -1 or errno.
 */
int _eputchar(char m)
{
	static int a;
	static char buf[WRITE_BUF_SIZE];

	if (m == BUF_FLUSH || a >= WRITE_BUF_SIZE)
	{
		write(2, buf, a);
		a = 0;
	}
	if (m != BUF_FLUSH)
		buf[a++] = m;
	return (1);
}

/**
 * _putfd - program prints the character m to given fd
 * @m: character.
 * @fd: filedescriptor.
 *
 * Return: 1, -1 or errno.
 */
int _putfd(char m, int fd)
{
	static int a;
	static char buf[WRITE_BUF_SIZE];

	if (m == BUF_FLUSH || a >= WRITE_BUF_SIZE)
	{
		write(fd, buf, a);
		a = 0;
	}
	if (m != BUF_FLUSH)
		buf[a++] = m;
	return (1);
}

/**
 * _putsfd - program displays input string.
 * @str: string.
 * @fd: filedescriptor
 *
 * Return: no. of characters.
 */
int _putsfd(char *str, int fd)
{
	int a = 0;

	if (!str)
		return (0);
	while (*str)
	{
		a += _putfd(*str++, fd);
	}
	return (a);
}
