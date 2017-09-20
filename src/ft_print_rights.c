/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_rights.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyakdi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/19 16:53:03 by jyakdi            #+#    #+#             */
/*   Updated: 2017/09/20 09:04:54 by jyakdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ls.h"

// set a buffer for all the putchar

void	ft_other_rights(t_elem *node)
{
	if (S_IROTH & node->stat.st_mode)
		ft_putchar('r');
	else
		ft_putchar('-');
	if (S_IWOTH & node->stat.st_mode)
		ft_putchar('w');
	else
		ft_putchar('-');
	if (S_IXOTH & node->stat.st_mode)
		ft_putchar('x');
	else
		ft_putchar('-');
	ft_putstr("  ");
}

void	ft_group_rights(t_elem *node)
{
	if (S_IRGRP & node->stat.st_mode)
		ft_putchar('r');
	else
		ft_putchar('-');
	if (S_IWGRP & node->stat.st_mode)
		ft_putchar('w');
	else
		ft_putchar('-');
	if (S_IXGRP & node->stat.st_mode)
		ft_putchar('x');
	else
		ft_putchar('-');
}

void	ft_user_rights(t_elem *node)
{
	if (S_IRUSR & node->stat.st_mode)
		ft_putchar('r');
	else
		ft_putchar('-');
	if (S_IWUSR & node->stat.st_mode)
		ft_putchar('w');
	else
		ft_putchar('-');
	if (S_IXUSR & node->stat.st_mode)
		ft_putchar('x');
	else
		ft_putchar('-');
}

void	ft_print_rights(t_elem *node)
{
	if (S_ISDIR(node->stat.st_mode))
		ft_putchar('d');
	else if (S_ISLNK(node->stat.st_mode))
		ft_putchar('l');
	else
		ft_putchar('-');
	ft_user_rights(node);
	ft_group_rights(node);
	ft_other_rights(node);
}
