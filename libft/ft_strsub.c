/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyakdi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/09 14:52:44 by jyakdi            #+#    #+#             */
/*   Updated: 2016/11/25 11:55:56 by jyakdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*str;

	if (s)
	{
		if (!(str = ft_strnew(len)))
			return (NULL);
		while (len--)
			*(str + len) = *(s + start + len);
		return (str);
	}
	return (NULL);
}
