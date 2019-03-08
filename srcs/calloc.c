/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrucker <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 18:34:48 by nbrucker          #+#    #+#             */
/*   Updated: 2019/02/28 18:34:48 by nbrucker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include "libft.h"

void		*calloc(size_t nmemb, size_t size)
{
	void	*ptr;
	size_t	x;

	if ((int)nmemb < 1)
		nmemb = 1;
	if ((int)size < 1)
		size = 1;
	x = nmemb * size;
	while (x % 16 != 0)
		x++;
	ptr = malloc(x);
	if (ptr)
		ft_bzero(ptr, x);
	return (ptr);
}
