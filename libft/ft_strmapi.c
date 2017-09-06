/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyakdi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/09 14:07:41 by jyakdi            #+#    #+#             */
/*   Updated: 2016/11/09 14:22:15 by jyakdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char				*mem;
	unsigned int		i;

	i = 0;
	if (s == NULL)
		return (NULL);
	if (!(mem = ft_memalloc(ft_strlen(s) + 1)))
		return (NULL);
	while (*s)
		*mem++ = (*f)(i++, *s++);
	return (mem - i);
}
