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

t_alloc	*split_alloc(t_alloc *alloc, size_t size)
{
	t_alloc	*new;

	if (alloc->size == size)
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
		while (i * getpagesize() < ((TINY + sizeof(t_alloc)) * 100) + sizeof(t_map))
			i++;
	else if (type == SMALL)
		while (i * getpagesize() < ((SMALL + sizeof(t_alloc)) * 100) + sizeof(t_map))
			i++;
	else
		while (i * getpagesize() < ((size + sizeof(t_alloc)) * 1) + sizeof(t_map))
			i++;
	return (getpagesize() * i);
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
	while (alloc->previous)
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

void	*ft_malloc(size_t size)
{
	void	*addr;

	if (size < 1)
		return (NULL);
	addr = get_from_existing_map(size);
	if (addr)
		return (addr);
	addr = get_new(size);
	if (addr)
		return (addr);
	return (NULL);
}
