/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyakdi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/06 11:17:28 by jyakdi            #+#    #+#             */
/*   Updated: 2017/10/10 16:51:20 by jyakdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ls.h"

void	ft_read_dir_arg(t_elem *list, t_flag *flag)
{
	if (!list)
		return ;
	if (flag->r == 0)
	{
		ft_read_dir_arg(list->left, flag);
		ft_open_dir(list, flag, NULL, NULL);
		ft_read_dir_arg(list->right, flag);
	}
	else
	{
		ft_read_dir_arg(list->right, flag);
		ft_open_dir(list, flag, NULL, NULL);
		ft_read_dir_arg(list->left, flag);
	}
}

void	ft_read_file_arg(t_elem *node, t_flag *flag, t_padding *pad)
{
	if (flag->r == 0)
	{
		if (node)
		{
			if (node->left)
				ft_read_file_arg(node->left, flag, pad);
			ft_print_name(node, flag, pad);
			if (node->right)
				ft_read_file_arg(node->right, flag, pad);
		}
	}
	else
	{
		if (node)
		{
			if (node->right)
				ft_read_file_arg(node->right, flag, pad);
			ft_print_name(node, flag, pad);
			if (node->left)
				ft_read_file_arg(node->left, flag, pad);
		}
	}
}

int		main(int argc, char **argv)
{
	t_all		*all;
	int			i;
	t_padding	*pad;

	if (!(pad = ft_memalloc(sizeof(t_padding))))
		ft_error(1, NULL);
	all = ft_init_all();
	i = ft_set_flag(all->flag, argc, argv);
	if (i + 1 >= argc)
		ft_register(&all, ".", all->flag, 0);
	if (i + 1 >= argc - 1)
		all->flag->first += 2;
	while (++i < argc)
		ft_register(&all, argv[i], all->flag, 0);
	ft_read_trash(all->trash);
	if (all->flag->l)
		ft_padding_tree(all->file, pad);
	ft_read_file_arg(all->file, all->flag, pad);
	if (all->file == NULL)
		all->flag->first += 1;
	ft_read_dir_arg(all->dir, all->flag);
	return (0);
}
