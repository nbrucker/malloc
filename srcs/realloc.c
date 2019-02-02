#include "malloc.h"

void	*create_new_alloc_cp(void *ptr, size_t size)
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

void	change_next_size(t_alloc *alloc, size_t size, int diff)
{
	t_alloc		*safe;

	safe = alloc->next;
	alloc->next = (void*)alloc->next + diff;
	alloc->next->next = safe->next;
	alloc->next->size = alloc->next->size - diff;
	alloc->next->free = 1;
	alloc->next->previous = alloc;
	alloc->size = size;
}

void	*ft_realloc(void *ptr, size_t size)
{
	t_alloc	*alloc;
	int		diff;

	alloc = is_existing_alloc(ptr);
	if (size < 1 || alloc == NULL)
		return (NULL);
	diff = size - alloc->size;
	if (diff == 0)
		return ((void*)alloc + sizeof(t_alloc));
	else if (diff < 0 && alloc->size - size >= sizeof(t_alloc))
	{
		split_alloc(alloc, alloc->size - size);
		return ((void*)alloc + sizeof(t_alloc));
	}
	else if (alloc->next && alloc->next->free == 1
	&& (int)alloc->next->size >= diff)
	{
		change_next_size(alloc, size, diff);
		return ((void*)alloc + sizeof(t_alloc));
	}
	else
		return (create_new_alloc_cp(ptr, size));
}
