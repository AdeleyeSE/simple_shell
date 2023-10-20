#include "shell.h"

/**
 * input_buf - bufers chaind comands
 * @info: paramtr struct
 * @buf: addres of bufer
 * @len: addres of len var
 *
 * Retun: bytes read
 */
ssize_t input_buf(info_t *info, char **buf, size_t *len)
{
	ssize_t r = 0;
	size_t len_p = 0;

	if (!*len) /* if nothing left in th bufer, fill it */
	{
		/*bfree((void **)info->cmd_buf);*/
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		r = getline(buf, &len_p, stdin);
#else
		r = _getline(info, buf, &len_p);
#endif
		if (r > 0)
		{
			if ((*buf)[r - 1] == '\n')
			{
				(*buf)[r - 1] = '\0'; /* remov trailing newline */
				r--;
			}
			info->linecount_flag = 1;
			remove_comments(*buf);
			build_history_list(info, *buf, info->histcount++);
			/* if (_strchr(*buf, ';')) is this a comand chain? */
			{
				*len = r;
				info->cmd_buf = buf;
			}
		}
	}
	return (r);
}

/**
 * get_input - gets a line minus the newline
 * @info: paramtr struct
 *
 * Retun: bytes read
 */
ssize_t get_input(info_t *info)
{
	static char *buf; /* th ';' comand chain bufer */
	static size_t i, j, len;
	ssize_t r = 0;
	char **buf_p = &(info->arg), *p;

	_putchar(BUF_FLUSH);
	r = input_buf(info, &buf, &len);
	if (r == -1) /* EOF */
		return (-1);
	if (len) /* we have comands left in th chain bufer */
	{
		j = i; /* init new iterator to curent buf position */
		p = buf + i; /* get pointr for retun */

		check_chain(info, buf, &j, i, len);
		while (j < len) /* iterat to semicolon or end */
		{
			if (is_chain(info, buf, &j))
				break;
			j++;
		}

		i = j + 1; /* incremnt past nulled ';'' */
		if (i >= len) /* reachd end of bufer? */
		{
			i = len = 0; /* reset positn and length */
			info->cmd_buf_type = CMD_NORM;
		}

		*buf_p = p; /* pas back pointr to curent comand positn */
		return (_strlen(p)); /* retun length of curent comand */
	}

	*buf_p = buf; /* else not a chain, pas back bufer from _getline() */
	return (r); /* retun length of bufer from _getline() */
}

/**
 * read_buf - reads a bufer
 * @info: paramtr struct
 * @buf: bufer
 * @i: size
 *
 * Retun: r
 */
ssize_t read_buf(info_t *info, char *buf, size_t *i)
{
	ssize_t r = 0;

	if (*i)
		return (0);
	r = read(info->readfd, buf, READ_BUF_SIZE);
	if (r >= 0)
		*i = r;
	return (r);
}

/**
 * _getline - gets th next line of input from STDIN
 * @info: paramtr struct
 * @ptr: addres of pointr to bufer, preallocated or NULL
 * @length: size of preallocated ptr bufer if not NULL
 *
 * Retun: s
 */
int _getline(info_t *info, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t i, len;
	size_t k;
	ssize_t r = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		s = *length;
	if (i == len)
		i = len = 0;

	r = read_buf(info, buf, &len);
	if (r == -1 || (r == 0 && len == 0))
		return (-1);

	c = _strchr(buf + i, '\n');
	k = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = _realloc(p, s, s ? s + k : k + 1);
	if (!new_p) /* MALLOC FAILURE! */
		return (p ? free(p), -1 : -1);

	if (s)
		_strncat(new_p, buf + i, k - i);
	else
		_strncpy(new_p, buf + i, k - i + 1);

	s += k - i;
	i = k;
	p = new_p;

	if (length)
		*length = s;
	*ptr = p;
	return (s);
}

/**
 * sigintHandler - blocks ctrl-C
 * @sig_num: th signal numbr
 *
 * Retun: void
 */
void sigintHandler(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}
