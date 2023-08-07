#include "shell.h"

/**
 * _myhistory - program prints list of history..
 * @info: Parameter.
 *  Return: 0
 */
int _myhistory(info_t *info)
{
	print_list(info->history);
	return (0);
}

/**
 * unset_alias - program unsets string alias.
 * @info: parameter.
 * @str: pointer.
 *
 * Return: 0 or 1.
 */
int unset_alias(info_t *info, char *str)
{
	char *p, a;
	int ret;

	p = _strchr(str, '=');
	if (!p)
		return (1);
	a = *p;
	*p = 0;
	ret = delete_node_at_index(&(info->alias),
		get_node_index(info->alias, node_starts_with(info->alias, str, -1)));
	*p = a;
	return (ret);
}

/**
 * set_alias - program sets the alias of a string
 * @info: struct parameter.
 * @str: pointer.
 *
 * Return: 0 or 1.
 */
int set_alias(info_t *info, char *str)
{
	char *p;

	p = _strchr(str, '=');
	if (!p)
		return (1);
	if (!*++p)
		return (unset_alias(info, str));

	unset_alias(info, str);
	return (add_node_end(&(info->alias), str, 0) == NULL);
}

/**
 * print_alias - prints the string alias.
 * @node: node of the alias.
 *
 * Return: 0 or 1.
 */
int print_alias(list_t *node)
{
	char *p = NULL, *m = NULL;

	if (node)
	{
		p = _strchr(node->str, '=');
		for (m = node->str; m <= p; m++)
			_putchar(*m);
		_putchar('\'');
		_puts(p + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * _myalias - acts like a builtin alias.
 * @info: parameter.
 *  Return: 0
 */
int _myalias(info_t *info)
{
	int m = 0;
	char *p = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (m = 1; info->argv[m]; m++)
	{
		p = _strchr(info->argv[m], '=');
		if (p)
			set_alias(info, info->argv[m]);
		else
			print_alias(node_starts_with(info->alias, info->argv[m], '='));
	}

	return (0);
}

