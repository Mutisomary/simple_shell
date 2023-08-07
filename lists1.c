#include "shell.h"

/**
 * list_len - program determines linked list length.
 * @a: pinter.
 * Return: list size.
 */
size_t list_len(const list_t *a)
{
	size_t b = 0;

	while (a)
	{
		a = a->next;
		b++;
	}
	return (b);
}

/**
 * list_to_strings - programs returns an array of strings.
 * @head: pointer.
 *
 * Return: the array.
 */
char **list_to_strings(list_t *head)
{
	list_t *node = head;
	size_t a = list_len(head), b;
	char **strs;
	char *str;

	if (!head || !a)
		return (NULL);
	strs = malloc(sizeof(char *) * (a + 1));
	if (!strs)
		return (NULL);
	for (a = 0; node; node = node->next, a++)
	{
		str = malloc(_strlen(node->str) + 1);
		if (!str)
		{
			for (b = 0; b < a; b++)
				free(strs[b]);
			free(strs);
			return (NULL);
		}

		str = _strcpy(str, node->str);
		strs[a] = str;
	}
	strs[a] = NULL;
	return (strs);
}


/**
 * print_list - program prints the elements of a linked list.
 * @a: pointer.
 *
 * Return: size of list
 */
size_t print_list(const list_t *a)
{
	size_t b = 0;

	while (a)
	{
		_puts(convert_number(a->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(a->str ? a->str : "(nil)");
		_puts("\n");
		a = a->next;
		b++;
	}
	return (b);
}

/**
 * node_starts_with - entry point.
 * @node: pointer.
 * @prefix: the string.
 * @a: next character.
 *
 * Return: NULL or match node.
 */
list_t *node_starts_with(list_t *node, char *prefix, char a)
{
	char *pp = NULL;

	while (node)
	{
		pp = starts_with(node->str, prefix);
		if (pp && ((a == -1) || (*pp == a)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * get_node_index - entry pointer.
 * @head: head pointer.
 * @node: node pointer.
 * Return: node index.
 */
ssize_t get_node_index(list_t *head, list_t *node)
{
	size_t a = 0;

	while (head)
	{
		if (head == node)
			return (a);
		head = head->next;
		a++;
	}
	return (-1);
}
