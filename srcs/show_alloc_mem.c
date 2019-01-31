#include "malloc.h"
#include "libft.h"

void	print_addr(void *ptr)
{
	unsigned long long	nbr;
	int 				tmp;
	char				buf[4096];
	int 				i;

	nbr = (unsigned long long)ptr;
	ft_putstr("0x");
	if (nbr == 0)
		ft_putchar('0');
	i = 0;
	while (nbr != 0)
	{
		tmp = nbr % 16;
		if (tmp < 10)
			buf[i] = 48 + tmp;
		else
			buf[i] = 97 + tmp - 10;
		nbr /= 16;
		i++;
	}
	i--;
	while (i >= 0)
	{
		ft_putchar(buf[i]);
		i--;
	}
}

void	print_map(t_map *map)
{
	if (map->type == TINY)
		ft_putstr("TINY : ");
	else if (map->type == SMALL)
		ft_putstr("SMALL : ");
	else
		ft_putstr("LARGE : ");
	print_addr((void*)map);
	ft_putchar('\n');
}

void	print_alloc(t_alloc *alloc)
{
	print_addr((void*)alloc + sizeof(t_alloc));
	ft_putstr(" - ");
	print_addr((void*)alloc + sizeof(t_alloc) + alloc->size);
	ft_putstr(" : ");
	ft_putnbr(alloc->size);
	ft_putendl(" octets");
}

void	show_alloc_mem(void)
{
	t_map	*map;
	t_alloc	*alloc;
	size_t	total;

	total = 0;
	map = g_map;
	while (map->next)
		map = map->next;
	while (map)
	{
		print_map(map);
		alloc = map->alloc;
		while (alloc)
		{
			if (alloc->free == 0)
				print_alloc(alloc);
			total += alloc->size;
			alloc = alloc->next;
		}
		map = map->previous;
	}
	ft_putstr("Total : ");
	ft_putnbr(total);
	ft_putendl(" octets");
}
