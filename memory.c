#include "shell.h"

/**
 * bfree - frees a pointr and NULLs th addres
 * @ptr: addres of th pointr to free
 *
 * Retun: 1 if freed, otherwise 0.
 */
int bfree(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}
