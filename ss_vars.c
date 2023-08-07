#include "shell.h"

/**
 * is_chain - program tests if the character is a delimiter or buffer
 * @info: parameter
 * @buf: buffer
 * @p: buffer address.
 *
 * Return: 1 or 0
 */
int is_chain(info_t *info, char *buf, size_t *p)
{
	size_t b = *p;

	if (buf[b] == '|' && buf[b + 1] == '|')
	{
		buf[b] = 0;
		b++;
		info->cmd_buf_type = CMD_OR;
	}
	else if (buf[b] == '&' && buf[b + 1] == '&')
	{
		buf[b] = 0;
		b++;
		info->cmd_buf_type = CMD_AND;
	}
	else if (buf[b] == ';')
	{
		buf[b] = 0;
		info->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*p = b;
	return (1);
}

/**
 * check_chain - program checks where we should chain.
 * @info: parameter
 * @buf: buffer
 * @p: buffer addres
 * @a: buffer starting position.
 * @length: buffer length
 *
 * Return: Void
 */
void check_chain(info_t *info, char *buf, size_t *p, size_t a, size_t length)
{
	size_t b = *p;

	if (info->cmd_buf_type == CMD_AND)
	{
		if (info->status)
		{
			buf[a] = 0;
			b = length;
		}
	}
	if (info->cmd_buf_type == CMD_OR)
	{
		if (!info->status)
		{
			buf[a] = 0;
			b = length;
		}
	}

	*p = b;
}

/**
 * replace_alias - alias is replaced on the string
 * @info: parameter
 *
 * Return: 1 or 0
 */
int replace_alias(info_t *info)
{
	int a;
	list_t *node;
	char *p;

	for (a = 0; a < 10; a++)
	{
		node = node_starts_with(info->alias, info->argv[0], '=');
		if (!node)
			return (0);
		free(info->argv[0]);
		p = _strchr(node->str, '=');
		if (!p)
			return (0);
		p = _strdup(p + 1);
		if (!p)
			return (0);
		info->argv[0] = p;
	}
	return (1);
}

/**
 * replace_vars - program replaces variables.
 * @info: parameter.
 *
 * Return: 0 or 1.
 */
int replace_vars(info_t *info)
{
	int a = 0;
	list_t *node;

	for (a = 0; info->argv[a]; a++)
	{
		if (info->argv[a][0] != '$' || !info->argv[a][1])
			continue;

		if (!_strcmp(info->argv[a], "$?"))
		{
			replace_string(&(info->argv[a]),
					_strdup(convert_number(info->status, 10, 0)));
			continue;
		}
		if (!_strcmp(info->argv[a], "$$"))
		{
			replace_string(&(info->argv[a]),
					_strdup(convert_number(getpid(), 10, 0)));
			continue;
		}
		node = node_starts_with(info->env, &info->argv[a][1], '=');
		if (node)
		{
			replace_string(&(info->argv[a]),
					_strdup(_strchr(node->str, '=') + 1));
			continue;
		}
		replace_string(&info->argv[a], _strdup(""));

	}
	return (0);
}

/**
 * replace_string - string replacement.
 * @old: old string
 * @new: new string
 *
 * Return: 0 or 1.
 */
int replace_string(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}

