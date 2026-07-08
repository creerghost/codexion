#include "codexion.h"

/* Returns the minimum of two integers */
int ft_min(int a, int b)
{
    if (a < b)
        return (a);
    return (b);
}

/* Returns the maximum of two integers */
int ft_max(int a, int b)
{
    if (a > b)
        return (a);
    return (b);
}

/* Allocates memory for an array of elements and initializes them to zero. */
void	*ft_calloc(size_t size)
{
	void	*ptr;

	ptr = (void *)malloc(size);
	if (!ptr)
		return (NULL);
	memset(ptr, 0, size);
	return (ptr);
}