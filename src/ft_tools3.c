/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tools3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyakdi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/06 14:33:12 by jyakdi            #+#    #+#             */
/*   Updated: 2017/10/06 14:41:29 by jyakdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ls.h"

void	ft_usage(char c)
{
	ft_putstr_fd("ls: illegal option -- ", 2);
	ft_putchar_fd(c, 2);
	ft_putendl_fd(
		"\nusage: ls [-ABCFGHLOPRSTUWabcdefghiklmnopqrstuwx1] [file ...]", 2);
	exit(1);
}

char	*ft_strlastchr(char *src, char c)
{
	int		i;

	i = 0;
	while (src[i])
		i++;
	i--;
	while (i >= 0)
	{
		if (c == src[i])
			return (&(src[i + 1]));
		i--;
	}
	return (src);
}
