/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrucker <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/05 18:04:17 by nbrucker          #+#    #+#             */
/*   Updated: 2019/02/05 18:04:26 by nbrucker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H

# include <unistd.h>
# include <sys/mman.h>

# define TINY  128
# define SMALL 1024
# define LARGE 999999

typedef struct		s_map
{
	int				type;
	size_t			size;
	struct s_map	*next;
	struct s_map	*previous;
	struct s_alloc	*alloc;
}					t_map;

typedef struct		s_alloc
{
	size_t			size;
	int				free;
	struct s_alloc	*next;
	struct s_alloc	*previous;
}					t_alloc;

t_map				*g_map;

void				*malloc(size_t size);
void				free(void *ptr);
void				*realloc(void *ptr, size_t size);
void				show_alloc_mem(void);

t_alloc				*is_existing_alloc(void *ptr);
t_alloc				*split_alloc(t_alloc *alloc, size_t size);
t_map				*create_map(size_t size, int type);
int					get_type(size_t size);
size_t				get_map_size(size_t size, size_t type);

#endif
