/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyakdi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/14 09:33:33 by jyakdi            #+#    #+#             */
/*   Updated: 2017/10/10 16:49:56 by jyakdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ls.h"

t_all	*ft_init_all(void)
{
	t_all	*all;
	t_flag	*flag;

	if (!(all = ft_memalloc(sizeof(t_all))))
		ft_error(1, NULL);
	if (!(flag = ft_memalloc(sizeof(t_flag))))
		ft_error(1, NULL);
	all->flag = flag;
	return (all);
}
