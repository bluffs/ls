/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_rights.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyakdi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/19 16:53:03 by jyakdi            #+#    #+#             */
/*   Updated: 2017/09/27 12:08:53 by jyakdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ls.h"

// set a buffer for all the putchar

void	ft_other_rights(struct stat buf)
{
	if (S_IROTH & buf.st_mode)
		ft_putchar('r');
	else
		ft_putchar('-');
	if (S_IWOTH & buf.st_mode)
		ft_putchar('w');
	else
		ft_putchar('-');
	if (S_IXOTH & buf.st_mode)
		ft_putchar('x');
	else
		ft_putchar('-');
	ft_putstr("  ");
}

void	ft_group_rights(struct stat buf)
{
	if (S_IRGRP & buf.st_mode)
		ft_putchar('r');
	else
		ft_putchar('-');
	if (S_IWGRP & buf.st_mode)
		ft_putchar('w');
	else
		ft_putchar('-');
	if (S_IXGRP & buf.st_mode)
		ft_putchar('x');
	else
		ft_putchar('-');
}

void	ft_user_rights(struct stat buf)
{
	if (S_IRUSR & buf.st_mode)
		ft_putchar('r');
	else
		ft_putchar('-');
	if (S_IWUSR & buf.st_mode)
		ft_putchar('w');
	else
		ft_putchar('-');
	if (S_IXUSR & buf.st_mode)
		ft_putchar('x');
	else
		ft_putchar('-');
}

void	ft_print_rights(t_elem *node)
{
	struct stat		buf;
	char			*src;

	src = ft_dir_name(node, 0);
	if ((lstat(src, &buf)) == -1)
		exit(1);
	if (S_ISDIR(buf.st_mode))
		ft_putchar('d');
	else if (S_ISLNK(buf.st_mode))
		ft_putchar('l');
	else
		ft_putchar('-');
	ft_user_rights(buf);
	ft_group_rights(buf);
	ft_other_rights(buf);
}
