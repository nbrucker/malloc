/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrucker <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/05 18:04:52 by nbrucker          #+#    #+#             */
/*   Updated: 2019/02/05 18:04:53 by nbrucker         ###   ########.fr       */
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

void	merge_alloc(t_alloc *alloc)
{
	t_alloc	*next;
	t_alloc	*previous;

	alloc->free = 1;
	next = alloc->next;
	if (next != NULL && next->free == 1)
	{
		alloc->size += next->size + sizeof(t_alloc);
		alloc->next = next->next;
	}
	previous = alloc->previous;
	if (previous != NULL && previous->free == 1)
	{
		previous->size += alloc->size + sizeof(t_alloc);
		previous->next = alloc->next;
	}
}

int		are_all_free(t_map *map)
{
	t_alloc *alloc;

	alloc = map->alloc;
	while (alloc)
	{
		if (alloc->free == 0)
			return (0);
		alloc = alloc->next;
	}
	return (1);
}

void	remove_map(t_map *map)
{
	t_map	*next;
	t_map	*previous;

	next = map->next;
	previous = map->previous;
	if (next)
		next->previous = previous;
	if (previous)
		previous->next = next;
	if (g_map == map)
		g_map = next;
	munmap((void*)map, map->size + sizeof(t_map));
}

void	free(void *ptr)
{
	t_alloc	*alloc;
	t_map	*map;

	if (ptr == NULL)
		return ;
	alloc = is_existing_alloc(ptr);
	if (alloc == NULL)
		return ;
	map = get_map_from_alloc(alloc);
	if (map == NULL)
		return ;
	if (map->type != LARGE)
		merge_alloc(alloc);
	else
	{
		alloc->free = 1;
		if (are_all_free(map) == 1)
			remove_map(map);
		else
			merge_alloc(alloc);
	}
}
