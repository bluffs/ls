/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tools.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyakdi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/06 15:15:27 by jyakdi            #+#    #+#             */
/*   Updated: 2017/10/11 17:44:54 by jyakdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ls.h"

void	ft_print_user2(struct stat buf, t_padding *pad, t_padding *new)
{
	char	*tmp;

	ft_putstr("  ");
	if (S_ISCHR(buf.st_mode) || S_ISBLK(buf.st_mode))
		ft_print_blocks(buf, pad);
	else
	{
		tmp = ft_itoa(buf.st_size);
		new->blocks_len = ft_strlen(tmp);
		ft_strdel(&tmp);
		while (new->blocks_len++ < pad->blocks_len)
			ft_putchar(' ');
		ft_putnbr(buf.st_size);
	}
	ft_putchar(' ');
}

void	ft_print_usr(struct stat buf, t_padding *new)
{
	struct passwd	*user;
	char			*tmp;

	if ((user = getpwuid(buf.st_uid)))
	{
		new->user_len = ft_strlen(user->pw_name);
		ft_putstr(user->pw_name);
	}
	else
	{
		tmp = ft_itoa(buf.st_uid);
		new->user_len = ft_strlen(tmp);
		ft_strdel(&tmp);
		ft_putnbr(buf.st_uid);
	}
}

void	ft_print_grp(struct stat buf, t_padding *new)
{
	struct group	*group;
	char			*tmp;

	if ((group = getgrgid(buf.st_gid)))
	{
		new->grp_len = ft_strlen(group->gr_name);
		ft_putstr(group->gr_name);
	}
	else
	{
		tmp = ft_itoa(buf.st_gid);
		new->grp_len = ft_strlen(tmp);
		ft_strdel(&tmp);
		ft_putnbr(buf.st_gid);
	}
}

void	ft_print_user(t_elem *node, t_padding *pad)
{
	struct stat		buf;
	char			*tmp;
	t_padding		*new;

	if (!(new = ft_memalloc(sizeof(t_padding))))
		ft_error(1, NULL);
	tmp = ft_dir_name(node, 0);
	if (lstat(tmp, &buf) == -1)
		exit(1);
	ft_strdel(&tmp);
	ft_print_usr(buf, new);
	while (new->user_len++ < pad->user_len)
		ft_putchar(' ');
	ft_putstr("  ");
	ft_print_grp(buf, new);
	while (new->grp_len++ < pad->grp_len)
		ft_putchar(' ');
	ft_print_user2(buf, pad, new);
	ft_memdel((void **)&new);
}

void	ft_print_line(t_elem *node, t_padding *pad, t_flag *flag)
{
	struct stat		buf;
	int				link_len;
	char			*tmp;

	ft_print_rights(node);
	tmp = ft_dir_name(node, 0);
	lstat(tmp, &buf);
	ft_strdel(&tmp);
	tmp = ft_itoa(buf.st_nlink);
	link_len = ft_strlen(tmp);
	ft_strdel(&tmp);
	while (link_len++ < pad->link_len)
		ft_putchar(' ');
	ft_putnbr(buf.st_nlink);
	ft_putstr(" ");
	ft_print_user(node, pad);
	ft_print_hour(buf);
	ft_print_file(node, flag);
}
