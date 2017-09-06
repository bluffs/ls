/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyakdi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/11 10:41:58 by jyakdi            #+#    #+#             */
/*   Updated: 2016/11/11 10:54:38 by jyakdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memdup(void const *content, size_t size)
{
	void	*str;

	if (!content)
		return (NULL);
	if (!(str = (void *)ft_memalloc(size)))
		return (NULL);
	ft_memcpy(str, content, size);
	return (str);
}
