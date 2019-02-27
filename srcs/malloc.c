/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrucker <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/05 18:04:57 by nbrucker          #+#    #+#             */
/*   Updated: 2019/02/05 18:04:58 by nbrucker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_alloc	*split_alloc(t_alloc *alloc, size_t size)
{
	t_alloc	*new;

	if (alloc->size == size - sizeof(t_alloc))
		return (alloc);
	else if (alloc->size < size)
		return (NULL);
	new = (t_alloc*)((void*)alloc + alloc->size + sizeof(t_alloc) - size);
	alloc->size -= size;
	new->size = size - sizeof(t_alloc);
	new->free = 1;
	new->next = alloc->next;
	new->previous = alloc;
	alloc->next = new;
	if (new->next)
		new->next->previous = new;
	return (new);
}

void	*get_new(size_t size)
{
	t_map	*map;
	size_t	map_size;
	int		type;
	t_alloc	*alloc;

	type = get_type(size);
	map_size = get_map_size(size, type);
	map = create_map(map_size, type);
	if (map == NULL)
		return (NULL);
	alloc = split_alloc(map->alloc, size + sizeof(t_alloc));
	if (alloc == NULL)
		return (NULL);
	alloc->free = 0;
	return ((void*)alloc + sizeof(t_alloc));
}

t_alloc	*get_from_existing_alloc(t_alloc *alloc, size_t size)
{
	while (alloc && alloc->previous)
		alloc = alloc->previous;
	while (alloc)
	{
		if (alloc->size >= size + sizeof(t_alloc) && alloc->free == 1)
			return (split_alloc(alloc, size + sizeof(t_alloc)));
		alloc = alloc->next;
	}
	return (NULL);
}

void	*get_from_existing_map(size_t size)
{
	int		type;
	t_map	*map;
	t_alloc	*alloc;

	type = get_type(size);
	map = g_map;
	alloc = NULL;
	while (map)
	{
		if (map->type == type)
		{
			alloc = get_from_existing_alloc(map->alloc, size);
			if (alloc)
			{
				alloc->free = 0;
				return ((void*)alloc + sizeof(t_alloc));
			}
		}
		map = map->next;
	}
	return (NULL);
}

void	*malloc(size_t size)
{
	void	*addr;

	if ((int)size < 1)
		return (NULL);
	addr = get_from_existing_map(size);
	if (addr)
		return (addr);
	addr = get_new(size);
	if (addr)
		return (addr);
	return (NULL);
}
