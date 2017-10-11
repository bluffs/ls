/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_open_dir2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyakdi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/11 13:33:40 by jyakdi            #+#    #+#             */
/*   Updated: 2017/10/11 17:49:27 by jyakdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ls.h"

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
