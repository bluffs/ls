/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_dir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyakdi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/14 11:11:15 by jyakdi            #+#    #+#             */
/*   Updated: 2017/10/10 16:51:50 by jyakdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ls.h"

void	ft_is_open(struct stat buf, t_elem *begin, t_flag *flag)
{
	if (S_ISDIR(buf.st_mode))
		if (ft_strcmp(begin->name, ".") && ft_strcmp(begin->name, "..") &&
				((!flag->a && begin->name[0] != '.') || flag->a))
			ft_open_dir(begin, flag, NULL, NULL);
}

void	ft_recursive_dir(t_elem *begin, t_flag *flag)
{
	struct stat		buf;
	char			*src;
	int				(*fct)(const char *, struct stat *);

	fct = (flag->l) ? lstat : stat;
	src = ft_dir_name(begin, 0);
	if (flag->r == 0)
	{
		if (begin->left)
			ft_recursive_dir(begin->left, flag);
		if (fct(src, &buf) != 1)
			ft_is_open(buf, begin, flag);
		if (begin->right)
			ft_recursive_dir(begin->right, flag);
	}
	else
	{
		if (begin->right)
			ft_recursive_dir(begin->right, flag);
		if (fct(src, &buf) != 1)
			ft_is_open(buf, begin, flag);
		if (begin->left)
			ft_recursive_dir(begin->left, flag);
	}
	ft_strdel(&src);
}

int		ft_count_blocks(t_elem *elem, int *total)
{
	struct stat		buf;
	char			*name;

	name = ft_dir_name(elem, 0);
	if (lstat(name, &buf) != -1)
	{
		ft_strdel(&name);
		*total += buf.st_blocks;
		return (1);
	}
	ft_strdel(&name);
	return (-1);
}
