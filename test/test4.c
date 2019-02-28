/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test5.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrucker <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/06 13:47:49 by nbrucker          #+#    #+#             */
/*   Updated: 2019/02/06 13:47:50 by nbrucker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>

#define M (1024*1024)

void	print(char *s)
{
	write(1, s, strlen(s));
}

int		main(void)
{
	char	*addr;

	addr = malloc(16);
	free(NULL);
	free((void*)addr + 5);
	if (realloc((void*)addr + 5, 10) == NULL)
		print("Bonjours\n");
	return (0);
}
