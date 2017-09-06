/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyakdi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/10 13:57:24 by jyakdi            #+#    #+#             */
/*   Updated: 2017/01/02 12:04:37 by jyakdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char		**ft_2_strsplit(char const *s, char c, int *k)
{
	int		l;
	int		i;
	int		j;
	char	**tab;

	l = 0;
	i = -1;
	j = 0;
	*k = ft_strlen(s);
	while (*k - i++)
	{
		l = ((s[i] == c || s[i] == 0) && i != j) ? l + 1 : l;
		j = (s[i] == c) ? i + 1 : j;
	}
	if (!(tab = (char**)ft_memalloc(sizeof(char*) * (l + 1))))
		return (NULL);
	return (tab);
}

char			**ft_strsplit(char const *s, char c)
{
	int		l;
	int		i;
	int		j;
	int		k;
	char	**tab;

	if (s)
	{
		if (!(tab = ft_2_strsplit(s, c, &k)))
			return (NULL);
		i = -1;
		j = 0;
		l = 0;
		while (k - i++)
		{
			if ((s[i] == c || s[i] == 0) && i != j)
				if (!(tab[l++] = ft_strsub(s, j, i - j)))
					return (NULL);
			j = (s[i] == c || s[i] == 0) ? i + 1 : j;
		}
		return (tab);
	}
	return (NULL);
}
