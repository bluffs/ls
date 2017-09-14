/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyakdi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/06 11:17:28 by jyakdi            #+#    #+#             */
/*   Updated: 2017/09/14 11:40:32 by jyakdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ls.h"

/*int		main(int argc, char **argv)
{
	struct dirent	*dp;
	t_flag			*flag;
	int				i;
	t_elem			*dir;
	struct stat		buf;
	t_elem			*trash;
	t_elem			*files;

	files = NULL;
	trash = NULL;
	dir = NULL;
	i = ft_set_flag(flag, argc, argv);
	while (++i < argc)
	{
		if (argv[i][0] && argv[i][1] != '.')
			ft_register(&trash, &files, &dir, argv[i], ".");
	}
	ft_read_trash(trash);
	ft_read_tree(files, 1);
	ft_putendl("");
	ft_read_dir(dir, 1, ".");
	return (0);
}*/

void	ft_read_dir_arg(t_elem	*list, t_flag *flag)
{
	if (!list)
		return ;
	if (flag->r == 0)
	{
		ft_read_dir_arg(list->left, flag);
		ft_putstr(list->src);
		ft_putstr(list->name);
		ft_putendl(":");
		ft_open_dir(list, flag);
		ft_read_dir_arg(list->right, flag);
	}
	else
	{
		ft_read_dir_arg(list->right, flag);
		ft_putstr(list->src);
		ft_putstr(list->name);
		ft_putendl(":");
		ft_open_dir(list, flag);
		ft_read_dir_arg(list->left, flag);
	}
}

int		main(int argc, char **argv)
{
	t_all	*all;
	int		i;
	
	all = ft_init_all();
	i = ft_set_flag(all->flag, argc, argv);
	while (++i < argc)
		ft_register(&all, argv[i]);
	ft_read_trash(all->trash);
	ft_read_tree(all->file, all->flag);
	ft_putendl("");
	ft_read_dir_arg(all->dir, all->flag);
	return (0);
}
