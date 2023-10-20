#include "shell.h"

/**
 * _eputs - prnts an input strig
 * @str: th strig to be prntd
 *
 * Retun: Nothing
 */
void _eputs(char *str)
{
	int i = 0;

	if (!str)
		return;
	while (str[i] != '\0')
	{
		_eputchar(str[i]);
		i++;
	}
}

/**
 * _eputchar - writes th charctr c to stderr
 * @c: Th charctr to prnt
 *
 * Retun: On success 1.
 * On error, -1 is retund, and errno is set appropriately.
 */
int _eputchar(char c)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(2, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}

/**
 * _putfd - writes the charctr c to given fd
 * @c: Th charctr to prnt
 * @fd: Th filedescriptor to write to
 *
 * Retun: On success 1.
 * On error, -1 is retuned, and errno is set appropriately.
 */
int _putfd(char c, int fd)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(fd, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}

/**
 * _putsfd - prnts an input strig
 * @str: the strig to be prntd
 * @fd: th filedescriptor to write to
 *
 * Retun: th numbr of chars put
 */
int _putsfd(char *str, int fd)
{
	int i = 0;

	if (!str)
		return (0);
	while (*str)
	{
		i += _putfd(*str++, fd);
	}
	return (i);
}
