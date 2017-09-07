/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyakdi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 18:02:11 by jyakdi            #+#    #+#             */
/*   Updated: 2016/11/08 12:31:37 by jyakdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned int	i;

	i = -1;
	if (src < dest)
		while (n--)
			((unsigned char *)dest)[n] = ((unsigned char *)src)[n];
	else
		while (++i < n)
			((unsigned char *)dest)[i] = ((unsigned char *)src)[i];
	return (dest);
}
