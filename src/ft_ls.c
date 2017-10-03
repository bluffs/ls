/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyakdi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/06 11:17:28 by jyakdi            #+#    #+#             */
/*   Updated: 2017/10/03 17:17:35 by jyakdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ls.h"

void	ft_read_dir_arg(t_elem	*list, t_flag *flag)
{
	if (!list)
		return ;
	if (flag->r == 0)
	{
		ft_read_dir_arg(list->left, flag);
		ft_open_dir(list, flag);
		ft_read_dir_arg(list->right, flag);
	}
	else
	{
		ft_read_dir_arg(list->right, flag);
		ft_open_dir(list, flag);
		ft_read_dir_arg(list->left, flag);
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
		ft_register(&all, ".", all->flag);
	if (i + 1 >= argc - 1)
		all->flag->first += 10;
	while (++i < argc)
		ft_register(&all, argv[i], all->flag);
	ft_read_trash(all->trash);
	if (all->flag->l)
		ft_padding_tree(all->file, pad);
	ft_read_tree(all->file, all->flag, pad);
	if (all->trash == NULL && all->file == NULL)
		all->flag->first += 1;
	ft_read_dir_arg(all->dir, all->flag);
	ft_putendl("end");
	sleep(5);
	return (0);
}
