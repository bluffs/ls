/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyakdi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/06 11:17:28 by jyakdi            #+#    #+#             */
/*   Updated: 2017/09/06 15:55:42 by jyakdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		main(int argc, char **argv)
{
	DIR				*dirp;
	struct dirent	*dp;
	t_flag			*flag;
	int				i;

	i = ft_set_flag(flag, argc, argv);
	/*ft_putstr("src at i = ");
	ft_putnbr(i);
	ft_putendl("");*/
	while (++i < argc)
	{
		if ((dirp = opendir(argv[i])))
		{
			//ft_putendl("open OK");
			while ((dp = readdir(dirp)))
			{
				ft_putendl(dp->d_name);
			}
			if (closedir(dirp) == -1)
				ft_putendl_fd("Error on close", 2);
		}
		else
		{
			ft_putendl_fd("Error on open", 2);
		}
	}
	return (0);
}
