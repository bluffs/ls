/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flag.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyakdi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/06 14:19:10 by jyakdi            #+#    #+#             */
/*   Updated: 2017/10/13 17:32:46 by jyakdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ls.h"

void	ft_register_flag(t_flag *flag, char c)
{
	if (c == 'r')
		flag->r = 1;
	if (c == 'R')
		flag->recursive = 1;
	if (c == 'a')
		flag->a = 1;
	if (c == 't')
		flag->t = 1;
	if (c == 'l' || c == 'o' || c == 'g')
		flag->l = 1;
	if (c == 'G')
		flag->color = 1;
	if (c == '1')
		flag->l = 0;
	if (c == 'o')
		flag->o = 1;
	if (c == 'd')
		flag->d = 1;
	if (c == 'g')
		flag->g = 1;
}

void	ft_check_flag(char *str, t_flag *flag)
{
	int		i;
	char	*list;
	int		j;

	list = "GRadglort1";
	i = 1;
	while (str[i])
	{
		j = 0;
		while (j < 10)
		{
			if (str[i] == list[j])
				break ;
			j++;
		}
		if (j != 10)
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
