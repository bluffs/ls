/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyakdi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/09 15:28:46 by jyakdi            #+#    #+#             */
/*   Updated: 2016/11/10 09:04:05 by jyakdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

char	*ft_strtrim(char const *s)
{
	char			*mem;
	unsigned int	nb;
	int				i;
	int				j;

	j = 0;
	i = -1;
	nb = 0;
	if (s == NULL)
		return (NULL);
	while (*s == ' ' || *s == '\n' || *s == '\t')
		s++;
	while (s[++i])
		nb = (s[i] == ' ' || s[i] == '\n' || s[i] == '\t') ? nb + 1 : 0;
	if (!(mem = ft_memalloc(i - nb + 1)))
		return (NULL);
	while (i-- - nb)
		mem[j++] = *s++;
	mem[j] = 0;
	return (mem);
}
