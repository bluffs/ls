/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyakdi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/09 10:41:08 by jyakdi            #+#    #+#             */
/*   Updated: 2016/11/09 10:56:27 by jyakdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

char	*ft_strstr(const char *s1, const char *s2)
{
	int		i;
	int		j;

	if (*s2 == 0)
		return ((char *)s1);
	while (*s1)
	{
		i = 0;
		j = 0;
		while (s1[i] == s2[j])
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
