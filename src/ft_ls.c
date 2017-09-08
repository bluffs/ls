/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyakdi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/06 11:17:28 by jyakdi            #+#    #+#             */
/*   Updated: 2017/09/08 14:43:03 by jyakdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		main(int argc, char **argv)
{
	DIR				*dirp;
	struct dirent	*dp;
	t_flag			*flag;
	int				i;
	t_elem			*begin;
	t_elem			*node;

	i = ft_set_flag(flag, argc, argv);
	while (++i < argc)
	{
		if ((dirp = opendir(argv[i])))
		{
			//ft_putendl("open OK");
			while ((dp = readdir(dirp)))
			{
				//ft_putendl(dp->d_name);
				//node = ft_create_node(dp);
				//ft_putendl(node->dp->d_name);
				//ft_putendl("calling register");
				begin = ft_register_tree(begin, ft_create_node(dp));
				//ft_putendl("end register");
			}
			if (closedir(dirp) == -1)
				ft_putendl_fd("Error on close", 2);
		}
		else
		{
			ft_putendl_fd("Error on open", 2);
		}
	}
	ft_read_tree_asc(begin);
	return (0);
}
