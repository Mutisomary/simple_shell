#include "shell.h"

/**
 * input_buf - program displays commands that are buffer chained.
 * @info: parameter.
 * @buf: buffer address.
 * @len: len address
 * Return: bytes read
 */
ssize_t input_buf(info_t *info, char **buf, size_t *len)
{
	ssize_t a = 0;
	size_t p_len = 0;

	if (!*len)
	{
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		a = getline(buf, &p_len, stdin);
#else
		a = _getline(info, buf, &p_len);
#endif
		if (a > 0)
		{
			if ((*buf)[a - 1] == '\n')
			{
				(*buf)[a - 1] = '\0';
				a--;
			}
			info->linecount_flag = 1;
			remove_comments(*buf);
			build_history_list(info, *buf, info->histcount++);
			{
				p_len = a;
				info->cmd_buf = buf;
			}
		}
	}
	return (a);
}

/**
 * get_input - gets a line minus the newline
 * @info: parameter struct
 *
 * Return: bytes read
 */
ssize_t get_input(info_t *info)
{
	static char *buf;
	static size_t m, j, p_len;
	ssize_t a = 0;
	char **buf_p = &(info->arg), *p;

	_putchar(BUF_FLUSH);
	a = input_buf(info, &buf, &p_len);
	if (a == -1)
		return (-1);
	if (p_len)
	{
		j = m;
		p = buf + m;

		check_chain(info, buf, &j, m, p_len);
		while (j < p_len)
		{
			if (is_chain(info, buf, &j))
				break;
			j++;
		}

		m = j + 1;
		if (m >= p_len)
		{
			m = p_len = 0;
			info->cmd_buf_type = CMD_NORM;
		}

		*buf_p = p;
		return (_strlen(p));
	}

	*buf_p = buf;
	return (a);
}

/**
 * read_buf - reads a buffer
 * @info: parameter struct
 * @buf: buffer
 * @j: size
 *
 * Return: r
 */
ssize_t read_buf(info_t *info, char *buf, size_t *j)
{
	ssize_t a = 0;

	if (*j)
		return (0);
	a = read(info->readfd, buf, READ_BUF_SIZE);
	if (a >= 0)
		*j = a;
	return (a);
}

/**
 * _getline - gets the next line of input from STDIN
 * @info: parameter struct
 * @ptr: address of pointer to buffer, preallocated or NULL
 * @length: size of preallocated ptr buffer if not NULL
 *
 * Return: s
 */
int _getline(info_t *info, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t m, p_len;
	size_t j;
	ssize_t a = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		s = *length;
	if (m == p_len)
		m = p_len = 0;

	a = read_buf(info, buf, &p_len);
	if (a == -1 || (a == 0 && p_len == 0))
		return (-1);

	c = _strchr(buf + m, '\n');
	j = c ? 1 + (unsigned int)(c - buf) : p_len;
	new_p = _realloc(p, s, s ? s + j : j + 1);
	if (!new_p)
		return (p ? free(p), -1 : -1);

	if (s)
		_strncat(new_p, buf + m, j - m);
	else
		_strncpy(new_p, buf + m, j - m + 1);

	s += j - m;
	m = j;
	p = new_p;

	if (length)
		*length = s;
	*ptr = p;
	return (s);
}

/**
 * sigintHandler - blocks ctrl-C
 * @sig_num: the signal number
 *
 * Return: void
 */
void sigintHandler(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}

