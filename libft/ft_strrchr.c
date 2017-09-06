/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyakdi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/09 10:00:08 by jyakdi            #+#    #+#             */
/*   Updated: 2016/11/09 10:40:47 by jyakdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

char	*ft_strrchr(const char *s, int c)
{
	size_t	len;

	len = 0;
	while (*s)
	{
		len++;
		s++;
	}
	len++;
	s++;
	while (len--)
	{
		s--;
		if (*s == c)
			return ((char *)s);
	}
	return (NULL);
}
