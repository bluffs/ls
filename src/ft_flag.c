/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flag.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyakdi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/06 14:19:10 by jyakdi            #+#    #+#             */
/*   Updated: 2017/09/14 10:53:53 by jyakdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ls.h"

void	ft_register_flag(t_flag *flag, char c)
{
	//ft_putstr("gonna register flag = ");
	//ft_putchar(c);
	//ft_putendl("");
	if (c == 'r')
		flag->r = 1;
	if (c == 'R')
		flag->recursive = 1;
}

void	ft_check_flag(char *str, t_flag *flag)
{
	int		i;
	char	*list;
	int		j;

	list = "ABCFGHLOPRSTUWabcdefghiklmnopqrstuwx1";
	i = 1;
	while (str[i])
	{
		j = 0;
		while (j < 38)
		{
			if (str[i] == list[j])
				break ;
			j++;
		}
		if (j != 38)
			ft_register_flag(flag, str[i]);
		else
			ft_usage(str[i]);
		i++;
	}
}

int		ft_set_flag(t_flag *flag, int argc, char **argv)
{
	int		i;

	i = 1;
	while (i < argc)
	{
		if (!ft_strcmp(argv[i], "--"))
			return (i);
		if (argv[i][0] == '-' && argv[i][1])
			ft_check_flag(argv[i], flag);
		else
			return (i - 1);
		i++;
	}
	return (i);
}
