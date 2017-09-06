/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyakdi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/09 13:49:12 by jyakdi            #+#    #+#             */
/*   Updated: 2016/11/09 14:07:32 by jyakdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>

char	*ft_strmap(char const *s, char (*f)(char))
{
	char	*mem;
	int		i;

	i = 0;
	if (s == NULL)
		return (NULL);
	if (!(mem = ft_memalloc(ft_strlen(s) + 1)))
		return (NULL);
	while (*s)
		mem[i++] = (*f)(*s++);
	return (mem);
}
