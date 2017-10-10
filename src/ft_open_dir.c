/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_open_dir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyakdi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/10 11:26:32 by jyakdi            #+#    #+#             */
/*   Updated: 2017/10/10 17:58:47 by jyakdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ls.h"

int			ft_get_buf(t_flag *flag, t_elem *dir, struct stat *buf)
{
	char			*name;

	name = ft_dir_name(dir, 0);
	if (flag->l)
	{
		if (lstat(name, buf) == -1)
		{
			ft_strdel(&name);
			return (-1);
		}
	}
	else
	{
		if (stat(name, buf) == -1)
		{
			ft_strdel(&name);
			return (-1);
		}
	}
	ft_strdel(&name);
	return (1);
}

void		ft_clean(char **name, char **dir_name, t_elem *beg, t_padding *pad)
{
	ft_strdel(name);
	ft_strdel(dir_name);
	if (beg)
		ft_del_tree(beg);
	if (pad)
		ft_memdel((void **)&pad);
}

void		ft_print_total(t_elem *begin, t_flag *flag, t_padding *pad)
{
	if (begin && flag->l)
	{
		ft_putstr("total ");
		ft_putnbr(pad->total);
		ft_putendl("");
	}
}

int			ft_print_extended(t_padding **pad, t_flag *flag,
								struct stat buf, t_elem *dir)
{
	*pad = NULL;
	if (flag->l)
		if (!(*pad = ft_memalloc(sizeof(t_padding))))
			ft_error(1, NULL);
	if (flag->l && !(S_ISDIR(buf.st_mode)))
	{
		ft_print_name(dir, flag, *pad);
		return (-1);
	}
	return (1);
}

void		ft_set_names(char **dir_nam, t_elem *dir, t_flag *flag, char **name)
{
	*dir_nam = ft_dir_name(dir, 0);
	ft_dir_format(flag, *dir_nam);
	*name = ft_dir_name(dir, 1);
}

int			ft_get_pad_blk(t_flag *flag, t_padding **pad, t_elem **begin,
							t_elem **dir)
{

	if (flag->l)
		if ((ft_get_padding(*dir, *pad) == -1) ||
				(ft_count_blocks(*dir, &(*pad)->total) == -1))
		{
			ft_del_tree(*dir);
			return (-1);
		}
	*begin = ft_register_tree(*begin, *dir, flag);
	return (1);
}

void		ft_end_open_dir(t_elem *begin, t_flag *flag, t_padding *pad)
{
	ft_read_tree(begin, flag, pad);
	if (begin && flag->recursive)
		ft_recursive_dir(begin, flag);
}

void		ft_open_dir(t_elem *dir, t_flag *flag, char *name, char *dir_name)
{
	DIR				*dirp;
	struct dirent	*dp;
	t_elem			*begin;
	struct stat		buf;
	t_padding		*pad;

	if ((ft_get_buf(flag, dir, &buf) == -1) ||
			(ft_print_extended(&pad, flag, buf, dir) == -1))
		return ;
	begin = NULL;
	ft_set_names(&dir_name, dir, flag, &name);
	if ((dirp = opendir(dir_name)))
	{
		while ((dp = readdir(dirp)))
		{
			if ((flag->a == 0 && dp->d_name[0] != '.') || flag->a)
			{
				dir = ft_create_node(name, dp->d_name, buf);
				if (ft_get_pad_blk(flag, &pad, &begin, &dir) == -1)
				{
					ft_free_dir(&name, &dir_name, begin, &pad);
					return ;
				}
			}
		}
		ft_print_total(begin, flag, pad);
		if (closedir(dirp) == -1)
			exit(1);
	}
	else
		ft_error(4, ft_strlastchr(dir->name, '/'));
	ft_end_open_dir(begin, flag, pad);
	ft_clean(&name, &dir_name, begin, pad);
}
