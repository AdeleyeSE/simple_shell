#include "shell.h"

/**
 **_strncpy - copies a strig
 *@dest: th destinatn strig to be copied to
 *@src: th source strig
 *@n: th amount of charctrs to be copied
 *Retun: th concatenatd strig
 */
char *_strncpy(char *dest, char *src, int n)
{
	int i, j;
	char *s = dest;

	i = 0;
	while (src[i] != '\0' && i < n - 1)
	{
		dest[i] = src[i];
		i++;
	}
	if (i < n)
	{
		j = i;
		while (j < n)
		{
			dest[j] = '\0';
			j++;
		}
	}
	return (s);
}

/**
 **_strncat - concatenates two strigs
 *@dest: th first strig
 *@src: th secnd strig
 *@n: th amount of bytes to be maximally used
 *Retun: th concatenatd strig
 */
char *_strncat(char *dest, char *src, int n)
{
	int i, j;
	char *s = dest;

	i = 0;
	j = 0;
	while (dest[i] != '\0')
		i++;
	while (src[j] != '\0' && j < n)
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	if (j < n)
		dest[i] = '\0';
	return (s);
}

/**
 **_strchr - loctes a charctr in a strig
 *@s: th strig to be parsed
 *@c: th charctr to look for
 *Retun: (s) a pointr to th memory area s
 */
char *_strchr(char *s, char c)
{
	do {
		if (*s == c)
			return (s);
	} while (*s++ != '\0');

	return (NULL);
}
