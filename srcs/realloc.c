#include "malloc.h"

void	*create_new_alloc(void *ptr, size_t size)
{
	char	*src;
	char 	*dst;
	size_t	i;

	src = (char*)ptr;
	dst = (char*)ft_malloc(size);
	if (dst == NULL)
		return (NULL);
	i = 0;
	while (i < size)
	{
		dst[i] = src[i];
		i++;
	}
	ft_free(ptr);
	return ((void*)dst);
}

void	*realloc(void *ptr, size_t size)
{
	t_alloc	*alloc;
	int		diff;

	if (size < 1)
		return (NULL);
	alloc = is_existing_alloc(ptr);
	if (alloc == NULL)
		return (NULL);
	diff = size - alloc->size;
	if (diff == 0)
		return (alloc);
	else if (diff < 0)
	{
		split_alloc(alloc, alloc->size - size);
		return (alloc);
	}
	else if (alloc->next && alloc->next->free == 1
	&& alloc->next->size > (size_t)diff)
	{
		alloc->next->size -= diff;
		alloc->next += diff;
		alloc->size = size;
		return (alloc);
	}
	else
		return (create_new_alloc(ptr, size));
}
