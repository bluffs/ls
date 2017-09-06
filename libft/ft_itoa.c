/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyakdi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/10 14:17:58 by jyakdi            #+#    #+#             */
/*   Updated: 2016/11/10 15:52:37 by jyakdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

char	*ft_itoa(int n)
{
	int long	nb;
	int			size;
	char		*mem;
	int			neg;

	nb = (int long)n;
	neg = (n < 0) ? 1 : 0;
	size = neg + 1;
	nb = (neg) ? -nb : nb;
	while (n /= 10)
		size++;
	if (!(mem = (char *)ft_memalloc(sizeof(*mem) * (size + 1))))
		return (NULL);
	size--;
	while (nb)
	{
		mem[size--] = nb % 10 + '0';
		nb /= 10;
	}
	if (neg)
		mem[size--] = '-';
	if (size == 0)
		mem[size] = '0';
	return (mem);
}
