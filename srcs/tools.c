/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrucker <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/06 13:53:57 by nbrucker          #+#    #+#             */
/*   Updated: 2019/02/06 13:53:57 by nbrucker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_alloc	*create_alloc(void *addr, size_t size)
{
	t_alloc	*new;

	new = addr;
	new->size = size - sizeof(t_alloc);
	new->free = 1;
	new->next = NULL;
	new->previous = NULL;
	return (new);
}

int		get_type(size_t size)
{
	if (size <= TINY)
		return (TINY);
	else if (size <= SMALL)
		return (SMALL);
	return (LARGE);
}

size_t	get_map_size(size_t size, size_t type)
{
	size_t	i;

	i = 0;
	if (type == TINY)
		while (i * getpagesize() < ((TINY + sizeof(t_alloc)) * 100)
			+ sizeof(t_map))
			i++;
	else if (type == SMALL)
		while (i * getpagesize() < ((SMALL + sizeof(t_alloc)) * 100)
			+ sizeof(t_map))
			i++;
	else
		while (i * getpagesize() < ((size + sizeof(t_alloc)) * 1)
			+ sizeof(t_map))
			i++;
	return (getpagesize() * i);
}

t_map	*create_map(size_t size, int type)
{
	t_map	*new;
	t_map	*map;

	new = mmap(NULL, size, PROT_READ | PROT_WRITE,
			MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	if (new == MAP_FAILED)
		return (NULL);
	map = g_map;
	new->previous = NULL;
	new->next = NULL;
	new->type = type;
	new->size = size - sizeof(t_map);
	new->alloc = create_alloc((void*)new + sizeof(t_map), new->size);
	if (map == NULL)
		g_map = new;
	else
	{
		while (map->next)
			map = map->next;
		map->next = new;
		new->previous = map;
	}
	return (new);
}

t_alloc	*is_existing_alloc(void *ptr)
{
	t_map	*map;
	t_alloc	*alloc;

	map = g_map;
	while (map)
	{
		alloc = map->alloc;
		while (alloc)
		{
			if ((void*)alloc + sizeof(t_alloc) == ptr)
				return (alloc);
			alloc = alloc->next;
		}
		map = map->next;
	}
	return (NULL);
}
