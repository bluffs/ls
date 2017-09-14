/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_dir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyakdi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/14 11:11:15 by jyakdi            #+#    #+#             */
/*   Updated: 2017/09/14 13:48:34 by jyakdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ls.h"

/*void	ft_read_dir(t_elem	*list, t_flag *flag)
{
	if (!list)
		return ;
	if (flag->r == 0)
	{
		ft_read_dir(list->left, flag);
		ft_putstr(list->src);
		ft_putstr(list->name);
		ft_putendl(":");
		ft_read_dir(list->right, flag);
	}
	else
	{
		ft_read_dir(list->right, flag);
		ft_putstr(list->src);
		ft_putstr(list->name);
		ft_putendl(":");
		ft_read_dir(list->left, flag);
	}
}*/

char	*ft_dir_name(t_elem *dir)
{
	char	*name;

	/*ft_putstr("dir->src = ");
	ft_putendl(dir->src);
	ft_putnbr(ft_strlen(dir->src));
	ft_putstr("dir->name = ");
	ft_putendl(dir->name);*/
	if (!(name = ft_memalloc(sizeof(char) *
					(ft_strlen(dir->src) + ft_strlen(dir->name) + 1))))
		ft_error(1, NULL);
	name = ft_strcat(name, dir->src);
	name = ft_strcat(name, dir->name);
	name = ft_strcat(name, "/");
	return (name);
}

/*
** we have a dir to open and print all elements of it
*/

void	ft_open_dir(t_elem *dir, t_flag *flag)
{
	DIR				*dirp;
	struct dirent	*dp;
	char			*dir_name;
	t_elem			*begin;
	t_elem			*elem;

	begin = NULL;
	dir_name = ft_dir_name(dir);
	if ((dirp = opendir(dir_name)))
	{
		while ((dp = readdir(dirp)))
		{
			elem = ft_create_node(dir_name, dp->d_name);
			begin = ft_register_tree(begin, elem);
		}
	}
	ft_read_tree(begin, flag);
}
