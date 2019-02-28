/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrucker <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 18:50:59 by nbrucker          #+#    #+#             */
/*   Updated: 2019/02/28 18:51:00 by nbrucker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_map	*get_map_from_alloc(t_alloc *search)
{
	t_map	*map;
	t_alloc	*alloc;

	map = g_map;
	while (map)
	{
		alloc = map->alloc;
		while (alloc)
		{
			if (alloc == search)
				return (map);
			alloc = alloc->next;
		}
		map = map->next;
	}
	return (NULL);
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
