/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_rights.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyakdi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/19 16:53:03 by jyakdi            #+#    #+#             */
/*   Updated: 2017/10/06 15:24:29 by jyakdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ls.h"

void	ft_other_rights(struct stat buf)
{
	char	rights[3];

	if (S_IROTH & buf.st_mode)
		rights[0] = 'r';
	else
		rights[0] = '-';
	if (S_IWOTH & buf.st_mode)
		rights[1] = 'w';
	else
		rights[1] = '-';
	if (S_IXOTH & buf.st_mode)
	{
		if (S_ISVTX & buf.st_mode)
			rights[2] = 't';
		else
			rights[2] = 'x';
	}
	else
	{
		if (S_ISVTX & buf.st_mode)
			rights[2] = 'T';
		else
			rights[2] = '-';
	}
	ft_putnstr(rights, 3);
}

void	ft_group_rights(struct stat buf)
{
	char	rights[3];

	if (S_IRGRP & buf.st_mode)
		rights[0] = 'r';
	else
		rights[0] = '-';
	if (S_IWGRP & buf.st_mode)
		rights[1] = 'w';
	else
		rights[1] = '-';
	if (S_IXGRP & buf.st_mode)
	{
		if (S_ISGID & buf.st_mode)
			rights[2] = 's';
		else
			rights[2] = 'x';
	}
	else
	{
		if (S_ISGID & buf.st_mode)
			rights[2] = 'S';
		else
			rights[2] = '-';
	}
	ft_putnstr(rights, 3);
}

void	ft_user_rights(struct stat buf)
{
	char	rights[3];

	if (S_IRUSR & buf.st_mode)
		rights[0] = 'r';
	else
		rights[0] = '-';
	if (S_IWUSR & buf.st_mode)
		rights[1] = 'w';
	else
		rights[1] = '-';
	if (S_IXUSR & buf.st_mode)
	{
		if (S_ISUID & buf.st_mode)
			rights[2] = 's';
		else
			rights[2] = 'x';
	}
	else
	{
		if (S_ISUID & buf.st_mode)
			rights[2] = 'S';
		else
			rights[2] = '-';
	}
	ft_putnstr(rights, 3);
}

void	ft_print_rights(t_elem *node)
{
	struct stat		buf;
	char			*src;

	src = ft_dir_name(node, 0);
	if ((lstat(src, &buf)) == -1)
		exit(1);
	ft_strdel(&src);
	if (S_ISDIR(buf.st_mode))
		ft_putchar('d');
	else if (S_ISLNK(buf.st_mode))
		ft_putchar('l');
	else if (S_ISCHR(buf.st_mode))
		ft_putchar('c');
	else if (S_ISBLK(buf.st_mode))
		ft_putchar('b');
	else if (S_ISFIFO(buf.st_mode))
		ft_putchar('p');
	else if (S_ISSOCK(buf.st_mode))
		ft_putchar('s');
	else
		ft_putchar('-');
	ft_user_rights(buf);
	ft_group_rights(buf);
	ft_other_rights(buf);
	ft_putstr("  ");
}
