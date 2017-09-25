/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_dir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyakdi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/14 11:11:15 by jyakdi            #+#    #+#             */
/*   Updated: 2017/09/25 15:20:22 by jyakdi           ###   ########.fr       */
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

char	*ft_dir_name(t_elem *dir, char n)
{
	char	*name;

	/*ft_putstr("dir->src = ");
	ft_putendl(dir->src);
	ft_putnbr(ft_strlen(dir->src));
	ft_putstr("dir->name = ");
	ft_putendl(dir->name);*/
	if (!(name = ft_memalloc(sizeof(char) *
					(ft_strlen(dir->src) + ft_strlen(dir->name) + 1 + n))))
		ft_error(1, NULL);
	name = ft_strcat(name, dir->src);
	name = ft_strcat(name, dir->name);
	if (n)
		name = ft_strcat(name, "/");
	return (name);
}

void	ft_recursive_dir(t_elem *begin, t_flag *flag)
{
	struct stat		buf;
	char			*src;
	int				(*fct)(const char *, struct stat *);

	fct = (flag->l) ? lstat : stat;
	src = ft_dir_name(begin, 1);
	if (begin->left)
		ft_recursive_dir(begin->left, flag);
	if (fct(src, &buf) != 1)
	{
		//ft_putstr("src ");
		//ft_putendl(src);
		if (S_ISDIR(buf.st_mode))
		{
			if (ft_strcmp(begin->name, ".") && ft_strcmp(begin->name, "..") &&
					((!flag->a && begin->name[0] != '.') || flag->a))
				ft_open_dir(begin, flag);
		}
	}
	if (begin->right)
		ft_recursive_dir(begin->right, flag);
}

/*
** we have a dir to open and print all elements of it
*/

int		ft_count_blocks(t_elem *elem)
{
	struct stat		buf;

	lstat(ft_dir_name(elem, 0), &buf);
	return (buf.st_blocks);
}

void	ft_open_dir(t_elem *dir, t_flag *flag)
{
	DIR				*dirp;
	struct dirent	*dp;
	char			*dir_name;
	t_elem			*begin;
	t_elem			*elem;
	struct stat		buf;
	int				(*fct)(const char *, struct stat *);
	int				total;
	t_padding		*pad;

	total = 0;
	fct = (flag->l) ? lstat : stat;
	fct(ft_dir_name(dir, 0), &buf);
	//ft_putstr("name = ");
	//ft_putendl(ft_dir_name(dir, 0));
	if (flag->l && !(S_ISDIR(buf.st_mode)))
	{
		ft_print_name(dir, flag);
		return ;
	}
	if (!(pad = ft_memalloc(sizeof(t_padding))))
		ft_error(1, NULL);
	begin = NULL;
	dir_name = ft_dir_name(dir, 0);
	ft_putendl("");
	ft_putstr(dir_name);
	ft_putendl(":");
	if ((dirp = opendir(dir_name)))
	{
		while ((dp = readdir(dirp)))
		{
			if ((flag->a == 0 && dp->d_name[0] != '.') || flag->a)
			{
				elem = ft_create_node(ft_dir_name(dir, 1), dp->d_name, buf);
				if (flag->l)
				{
					ft_get_padding(elem, pad);
					total += ft_count_blocks(elem);
				}
				begin = ft_register_tree(begin, elem, flag);
			}
		}
		if (elem && flag->l)
		{
			ft_putstr("total ");
			ft_putnbr(total);
			ft_putendl("");
		}
		if (closedir(dirp) == -1)
		{
			ft_putendl_fd("Error on close", 2);
			exit(1);
		}
	}
	else
		ft_error(4, ft_strlastchr(dir->name, '/'));
	ft_read_tree(begin, flag);
	if (begin && flag->recursive)
		ft_recursive_dir(begin, flag);
}
