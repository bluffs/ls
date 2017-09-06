/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyakdi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/09 11:00:52 by jyakdi            #+#    #+#             */
/*   Updated: 2016/11/09 11:15:07 by jyakdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

char	*ft_strnstr(const char *s1, const char *s2, size_t len)
{
	int		i;
	int		j;

	if (*s2 == 0)
		return ((char *)s1);
	while (*s1 && len--)
	{
		i = 0;
		j = 0;
		while (s1[i] == s2[j] && (len - j + 1 > 0))
		{
			j++;
			i++;
			if (!(s2[j]))
				return ((char *)s1);
		}
		s1++;
	}
	return (NULL);
}
