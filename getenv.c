#include "shell.h"

/**
 * get_environ - entry point.
 * @info: parameter.
 * Return: 0
 */
char **get_environ(info_t *info)
{
	if (!info->environ || info->env_changed)
	{
		info->environ = list_to_strings(info->env);
		info->env_changed = 0;
	}

	return (info->environ);
}

/**
 * _unsetenv - program removes the variable environment.
 * @info: parameter.
 * @var:parameter.
 * Return: 0.
 */
int _unsetenv(info_t *info, char *var)
{
	list_t *node = info->env;
	size_t a = 0;
	char *pp;

	if (!node || !var)
		return (0);

	while (node)
	{
		pp = starts_with(node->str, var);
		if (pp && *pp == '=')
		{
			info->env_changed = delete_node_at_index(&(info->env), a);
			a = 0;
			node = info->env;
			continue;
		}
		node = node->next;
		a++;
	}
	return (info->env_changed);
}

/**
 * _setenv - program initializes a variable environment.
 * @info: Entry point.
 * @var: parameter.
 * @value: parameter.
 *  Return: 0
 */
int _setenv(info_t *info, char *var, char *value)
{
	char *buf = NULL;
	list_t *node;
	char *pp;

	if (!var || !value)
		return (0);

	buf = malloc(_strlen(var) + _strlen(value) + 2);
	if (!buf)
		return (1);
	_strcpy(buf, var);
	_strcat(buf, "=");
	_strcat(buf, value);
	node = info->env;
	while (node)
	{
		pp = starts_with(node->str, var);
		if (pp && *pp == '=')
		{
			free(node->str);
			node->str = buf;
			info->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	add_node_end(&(info->env), buf, 0);
	free(buf);
	info->env_changed = 1;
	return (0);
}
