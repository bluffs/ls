/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tools.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyakdi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/06 15:15:27 by jyakdi            #+#    #+#             */
/*   Updated: 2017/10/10 08:53:12 by jyakdi           ###   ########.fr       */
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

void	ft_print_user(t_elem *node, t_padding *pad)
{
	struct passwd	*user;
	struct group	*group;
	struct stat		buf;
	char			*tmp;
	t_padding		*new;

	if (!(new = ft_memalloc(sizeof(t_padding))))
		ft_error(1, NULL);
	tmp = ft_dir_name(node, 0);
	if (lstat(tmp, &buf) == -1)
		exit(1);
	ft_strdel(&tmp);
	user = getpwuid(buf.st_uid);
	new->user_len = ft_strlen(user->pw_name);
	ft_putstr(user->pw_name);
	while (new->user_len++ < pad->user_len)
		ft_putchar(' ');
	ft_putstr("  ");
	group = getgrgid(buf.st_gid);
	new->grp_len = ft_strlen(group->gr_name);
	ft_putstr(group->gr_name);
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

void	ft_print_name(t_elem *node, t_flag *flag, t_padding *pad)
{
	char			*str;
	struct stat		buf;

	str = ft_dir_name(node, 0);
	if (flag->l)
		ft_print_line(node, pad, flag);
	else if (lstat(str, &buf) != -1)
	{
		if (flag->color)
		{
			if (S_ISDIR(buf.st_mode))
				ft_putstr("\033[1;36m");
			else if (S_ISLNK(buf.st_mode))
				ft_putstr("\033[0;35m");
			ft_putendl(node->name);
			ft_putstr("\033[0;m");
		}
		else
		{
			ft_putendl(node->name);
		}
	}
	ft_strdel(&str);
}

void	ft_error(int n, char *str)
{
	if (n == 1)
	{
		ft_putendl_fd("malloc error", 2);
		exit(1);
	}
	if (n == 2)
	{
		ft_putstr_fd("ls: ", 2);
		ft_putstr_fd(str, 2);
		ft_putendl_fd(": No such file or directory", 2);
	}
	if (n == 3)
	{
		ft_putendl_fd("ls: fts_open: No such file or directory", 2);
		exit(1);
	}
	if (n == 4)
	{
		ft_putstr_fd("ls: ", 2);
		ft_putstr_fd(str, 2);
		ft_putendl_fd(": Permission denied", 2);
	}
}
