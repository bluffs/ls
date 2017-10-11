/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tools4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyakdi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/11 17:42:06 by jyakdi            #+#    #+#             */
/*   Updated: 2017/10/11 17:46:05 by jyakdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ls.h"

void	ft_print_name(t_elem *node, t_flag *flag, t_padding *pad)
{
	char			*str;
	struct stat		buf;

	str = ft_dir_name(node, 0);
	if (flag->l)
		ft_print_line(node, pad, flag);
	else if (lstat(str, &buf) != -1)
	{
		if (flag->color)
		{
			if (S_ISDIR(buf.st_mode))
				ft_putstr("\033[1;36m");
			else if (S_ISLNK(buf.st_mode))
				ft_putstr("\033[0;35m");
			ft_putendl(node->name);
			ft_putstr("\033[0;m");
		}
		else
		{
			ft_putendl(node->name);
		}
	}
	ft_strdel(&str);
}

void	ft_error(int n, char *str)
{
	if (n == 1)
	{
		ft_putendl_fd("malloc error", 2);
		exit(1);
	}
	if (n == 2)
	{
		ft_putstr_fd("ls: ", 2);
		ft_putstr_fd(str, 2);
		ft_putendl_fd(": No such file or directory", 2);
	}
	if (n == 3)
	{
		ft_putendl_fd("ls: fts_open: No such file or directory", 2);
		exit(1);
	}
	if (n == 4)
	{
		ft_putstr_fd("ls: ", 2);
		ft_putstr_fd(str, 2);
		ft_putendl_fd(": Permission denied", 2);
	}
}
