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

void		*ft_calloc(size_t nmemb, size_t size)
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
	ptr = ft_malloc(x);
	if (ptr)
		ft_bzero(ptr, x);
	return (ptr);
}

void		*calloc(size_t nmemb, size_t size)
{
	void	*ret;

	if (g_lock == 0)
	{
		g_lock = 1;
		ret = ft_calloc(nmemb, size);
		g_lock = 0;
		return (ret);
	}
	else
		return (NULL);
}
