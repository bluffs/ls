/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_open_dir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyakdi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/10 11:26:32 by jyakdi            #+#    #+#             */
/*   Updated: 2017/10/11 17:48:31 by jyakdi           ###   ########.fr       */
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

void		ft_end_open_dir(t_elem *begin, t_flag *flag, t_padding *pad)
{
	ft_read_tree(begin, flag, pad);
	if (begin && flag->recursive)
		ft_recursive_dir(begin, flag);
}

void		ft_close_dir(t_elem *begin, t_flag *flag, t_padding *pad, DIR *dirp)
{
	ft_print_total(begin, flag, pad);
	if (closedir(dirp) == -1)
		exit(1);
}

t_elem		*ft_is_register(t_flag *flag, struct dirent *dp,
							char *name, struct stat buf)
{
	t_elem		*dir;

	dir = NULL;
	if ((flag->a == 0 && dp->d_name[0] != '.') || flag->a)
	{
		dir = ft_create_node(name, dp->d_name, buf);
	}
	return (dir);
}

void		ft_open_dir(t_elem *d, t_flag *f, char *name, char *dir_name)
{
	DIR				*dirp;
	struct dirent	*dp;
	t_elem			*begin;
	struct stat		b;
	t_padding		*p;

	if ((ft_get_buf(f, d, &b) == -1) || (ft_print_extended(&p, f, b, d) == -1))
		return ;
	begin = NULL;
	ft_set_names(&dir_name, d, f, &name);
	if ((dirp = opendir(dir_name)))
	{
		while ((dp = readdir(dirp)))
			if ((d = ft_is_register(f, dp, name, b)) != NULL)
				if (ft_get_pad_blk(f, &p, &begin, &d) == -1)
				{
					ft_free_dir(&name, &dir_name, begin, &p);
					return ;
				}
		ft_close_dir(begin, f, p, dirp);
	}
	else
		ft_error(4, ft_strlastchr(d->name, '/'));
	ft_end_open_dir(begin, f, p);
	ft_clean(&name, &dir_name, begin, p);
}
