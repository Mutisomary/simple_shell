#include "shell.h"

/**
 * interactive - program in shell interactive mode returns 1.
 * @info: parameter.
 *
 * Return: 1 or 0.
 */
int interactive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}
				

/**
 * is_delim - program analyze if character is a delimiter
 * @a: character
 * @delim: delimiter
 * Return: 1 or 0.
 */
int is_delim(char a, char *delim)
{
	while (*delim)
		if (*delim++ == a)
			return (1);
	return (0);
}

/**
 * _isalpha - program check for alphabetic character.
 * @a: The character.
 * Return: 1 or 0.
 */

int _isalpha(int a)
{
	if ((a >= 'a' && a <= 'z') || (a >= 'A' && a <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * _atoi - integer conversion.
 * @s: string.
 * Return: converted number.
 */

int _atoi(char *s)
{
	int m, sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (m = 0; s[m] != '\0' && flag != 2; m++)
	{
		if (s[m] == '-')
			sign *= -1;

		if (s[m] >= '0' && s[m] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (s[m] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		output = -result;
	else
		output = result;

	return (output);
}
