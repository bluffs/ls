/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyakdi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/08 15:58:34 by jyakdi            #+#    #+#             */
/*   Updated: 2016/11/09 09:40:23 by jyakdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

size_t		ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	dest_end;

	i = 0;
	while (dest[i] && i < size)
		i++;
	dest_end = i;
	while (src[i - dest_end] && i < size - 1)
	{
		dest[i] = src[i - dest_end];
		i++;
	}
	if (dest_end < size)
		dest[i] = 0;
	return (dest_end + ft_strlen(src));
}
