/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tools.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyakdi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/06 15:15:27 by jyakdi            #+#    #+#             */
/*   Updated: 2017/09/08 10:28:03 by jyakdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "ft_ls.h"

void	ft_error(int n)
{
	if (n == 1)
	{
		ft_putendl_fd("malloc error", 2);
		exit(1);
	}
}

void	ft_usage(char c)
{
	ft_putstr_fd("ls: illegal option -- ", 2);
	ft_putchar_fd(c, 2);
	ft_putendl_fd("\nusage: ls [-ABCFGHLOPRSTUWabcdefghiklmnopqrstuwx1]", 2);
	exit(1);
}
