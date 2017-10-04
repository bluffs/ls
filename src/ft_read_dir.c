/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_dir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyakdi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/14 11:11:15 by jyakdi            #+#    #+#             */
/*   Updated: 2017/10/04 16:54:21 by jyakdi           ###   ########.fr       */
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
	if (n && name[ft_strlen(name) - 1] != '/')
		name = ft_strcat(name, "/");
	return (name);
}

void	ft_recursive_dir(t_elem *begin, t_flag *flag)
{
	struct stat		buf;
	char			*src;
	int				(*fct)(const char *, struct stat *);

	fct = (flag->l) ? lstat : stat;
	src = ft_dir_name(begin, 0);
	if (begin->left)
		ft_recursive_dir(begin->left, flag);
	if (fct(src, &buf) != 1)
	{
		//ft_putstr("src ");
		//ft_putendl(src);
		if (S_ISDIR(buf.st_mode))
		{
			//ft_putstr(src);
			//ft_putendl(" is a dir");
			if (ft_strcmp(begin->name, ".") && ft_strcmp(begin->name, "..") &&
					((!flag->a && begin->name[0] != '.') || flag->a))
				ft_open_dir(begin, flag);
		}
	}
	if (begin->right)
		ft_recursive_dir(begin->right, flag);
	ft_strdel(&src);
}

/*
** we have a dir to open and print all elements of it
*/

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

void	ft_dir_format(t_flag *flag, char *dir_name)
{
	if (flag->first & 1)
		flag->first -= 1;
	else
		ft_putendl("");
	if (flag->first & 10)
		flag->first -= 10;
	else
	{
		ft_putstr(dir_name);
		ft_putendl(":");
	}
}

void	ft_free_dir(char **name, char **dir_name, t_elem *begin, t_padding **pad)
{
	ft_strdel(name);
	ft_strdel(dir_name);
	if (begin)
		ft_del_tree(begin);
	if (pad)
		ft_memdel((void **)pad);
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
	char			*name;

	name = ft_dir_name(dir, 0);
	ft_putendl("-------opening dir-------");
	sleep(3);
	total = 0;
	fct = (flag->l) ? lstat : stat;
	fct(name, &buf);
	ft_strdel(&name);
	//ft_putstr("name = ");
	//ft_putendl(ft_dir_name(dir, 0));
	if (flag->l && !(S_ISDIR(buf.st_mode)))
	{
		ft_print_name(dir, flag, pad);
		return ;
	}
	pad = NULL;
	if (flag->l)
		if (!(pad = ft_memalloc(sizeof(t_padding))))
			ft_error(1, NULL);
	begin = NULL;
	dir_name = ft_dir_name(dir, 0);
	ft_dir_format(flag, dir_name);
	//ft_putendl("before while");
	//sleep(3);
	name = ft_dir_name(dir, 1);
	if ((dirp = opendir(dir_name)))
	{
		while ((dp = readdir(dirp)))
		{
			//ft_putendl("begin while");
			//sleep(3);
			if ((flag->a == 0 && dp->d_name[0] != '.') || flag->a)
			{
				//ft_putendl("in while if");
				//sleep(3);
				elem = ft_create_node(name, dp->d_name, buf);
				//ft_putstr("name = ");
				//ft_putendl(name);
				//ft_strdel(&name);
				//ft_putendl("in while if 2");
				//sleep(3);
				if (flag->l)
				{
					//ft_putendl("test1");
					//ft_putendl("before padding");
					//sleep(3);
					if (ft_get_padding(elem, pad) == -1)
					{
						ft_free_dir(&name, &dir_name, begin, &pad);
						ft_del_tree(elem);
						//ft_strdel(&name);
						//ft_strdel(&dir_name);
						/*if (begin)
							ft_del_tree(begin);
						if (pad)
							ft_memdel((void **)&pad);*/
						ft_putendl("-1 returned");
						sleep(3);
						return ;
					}
					//ft_putendl("after padding");
					//sleep(3);
					//ft_putendl("test2");
					//ft_putendl("before count");
					//sleep(3);
					if (ft_count_blocks(elem, &total) == -1)
					{
						ft_putendl("-1 has been returned");
						ft_free_dir(&name, &dir_name, begin, &pad);
						return ;
					}
					//ft_putendl("after count");
					//sleep(3);
					//ft_putendl("test2");
				}
				begin = ft_register_tree(begin, elem, flag);
			}
		}
		//ft_putendl("test0.11");
		//sleep(3);
		if (begin && flag->l)
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
	ft_strdel(&name);
	ft_strdel(&dir_name);
	ft_read_tree(begin, flag, pad);
	if (begin && flag->recursive)
		ft_recursive_dir(begin, flag);
	if (begin)
		ft_del_tree(begin);
	if (pad)
		ft_memdel((void **)&pad);
	ft_putendl("end open dir");
	sleep(5);
}
