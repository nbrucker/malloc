/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrucker <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/05 18:05:08 by nbrucker          #+#    #+#             */
/*   Updated: 2019/02/05 18:05:08 by nbrucker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	*create_new_alloc_cp(void *ptr, size_t size, size_t n)
{
	char	*src;
	char	*dst;
	size_t	i;

	src = (char*)ptr;
	dst = (char*)malloc(size);
	if (dst == NULL)
		return (NULL);
	i = 0;
	while (i < size && i < n)
	{
		dst[i] = src[i];
		i++;
	}
	free(ptr);
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

void	*realloc(void *ptr, size_t size)
{
	t_alloc	*alloc;
	int		diff;

	if (ptr == NULL)
		return (malloc(size));
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
		return (create_new_alloc_cp(ptr, size, alloc->size));
}
