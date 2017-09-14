/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyakdi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/14 09:33:33 by jyakdi            #+#    #+#             */
/*   Updated: 2017/09/14 10:05:30 by jyakdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ls.h"

t_all	*ft_init_all()
{
	t_all	*all;
	t_flag	*flag;
	t_elem	*trash;
	t_elem	*file;
	t_elem	*dir;

	if (!(all = ft_memalloc(sizeof(t_all))))
		ft_error(1, NULL);
	if (!(flag = ft_memalloc(sizeof(t_flag))))
		ft_error(1, NULL);
	if (!(trash = ft_memalloc(sizeof(t_elem))))
		ft_error(1, NULL);
	if (!(file = ft_memalloc(sizeof(t_elem))))
		ft_error(1, NULL);
	if (!(dir = ft_memalloc(sizeof(t_elem))))
		ft_error(1, NULL);
	all->flag = flag;
	//all->trash = trash;
	//all->file = file;
	//all->dir = dir;
	return (all);
}
