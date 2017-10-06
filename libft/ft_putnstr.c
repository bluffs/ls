/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyakdi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/06 14:59:32 by jyakdi            #+#    #+#             */
/*   Updated: 2017/10/06 15:09:36 by jyakdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

void	ft_putnstr(char *str, int n)
{
	int		len = ft_strlen(str);
	n = (n > len) ? len : n;
	if (str)
		write(1, str, n);
}
