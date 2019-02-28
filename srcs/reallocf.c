/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reallocf.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrucker <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 18:34:13 by nbrucker          #+#    #+#             */
/*   Updated: 2019/02/28 18:34:13 by nbrucker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	*ft_reallocf(void *ptr, size_t size)
{
	void *ret;

	if (!(ret = ft_realloc(ptr, size)))
	{
		ft_free(ptr);
		return (NULL);
	}
	return (ret);
}

void	*reallocf(void *ptr, size_t size)
{
	void	*ret;

	if (g_lock == 0)
	{
		g_lock = 1;
		ret = ft_reallocf(ptr, size);
		g_lock = 0;
		return (ret);
	}
	else
		return (NULL);
}
