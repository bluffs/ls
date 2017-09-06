/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyakdi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/09 11:50:51 by jyakdi            #+#    #+#             */
/*   Updated: 2016/11/21 11:15:53 by jyakdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	*ft_memalloc(size_t size)
{
	unsigned char	*mem;
	size_t			nb;

	nb = 0;
	if (!(mem = (unsigned char *)malloc(sizeof(unsigned char) * size)))
		return (NULL);
	while (nb < size)
		mem[nb++] = 0;
	return ((void *)mem);
}
