/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tools.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyakdi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/06 15:15:27 by jyakdi            #+#    #+#             */
/*   Updated: 2017/09/27 09:55:02 by jyakdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../inc/ft_ls.h"

void	ft_print_file(t_elem *node)
{
	char			str[PATH_MAX];
	int				nb;
	struct stat		buf;

	lstat(ft_dir_name(node, 0), &buf);
	//ft_putstr("name  = ");
	//ft_putendl(ft_dir_name(node, 0));
	if (S_ISDIR(buf.st_mode))
	{
		//ft_putstr("color blue");
		ft_putstr("\033[1;36m");
	}
	else if (S_ISLNK(buf.st_mode))
		ft_putstr("\033[0;35m");
	ft_putstr(node->name);
	ft_putstr("\033[0;m");
	if (S_ISLNK(buf.st_mode))
	{
		nb = readlink(ft_dir_name(node, 0), str, PATH_MAX);
		ft_putstr(" -> ");
		write(1, str, nb);
	}
	ft_putendl("");
}

void	ft_putnstr(char *str, int start)
{
	int		end;

	end = ft_strlen(str) - 9;
	while (start < end)
	{
		ft_putchar(str[start]);
		start++;
	}
}

void	ft_print_user(t_elem *node, t_padding *pad)
{
	struct passwd	*user;
	struct group	*group;
	char			*date;
	struct stat		buf;
	int				blocks_len;
	int				user_len;
	int				grp_len;

	lstat(ft_dir_name(node, 0), &buf);
	user = getpwuid(buf.st_uid);
	user_len = ft_strlen(user->pw_name);
	ft_putstr(user->pw_name);
	while (user_len++ < pad->user_len)
		ft_putchar(' ');
	ft_putstr("  ");
	group = getgrgid(buf.st_gid);
	grp_len = ft_strlen(group->gr_name);
	ft_putstr(group->gr_name);
	while (grp_len++ < pad->grp_len)
		ft_putchar(' ');
	ft_putstr("  ");
	blocks_len = ft_strlen(ft_itoa(buf.st_size));
	while (blocks_len++ < pad->blocks_len)
		ft_putchar(' ');
	ft_putnbr(buf.st_size);
	ft_putchar(' ');
	date = ctime(&buf.st_mtime);
	ft_putnstr(date, 4);
	ft_putchar(' ');
}

void	ft_print_line(t_elem *node, t_padding *pad)
{
	struct stat		buf;
	int				link_len;

	ft_print_rights(node);
	lstat(ft_dir_name(node, 0), &buf);
	//ft_putendl("\ntest0");
	link_len = ft_strlen(ft_itoa(buf.st_nlink));
	//ft_putstr("test1 pad->link_len = ");
	//ft_putnbr(pad->link_len);
	//ft_putendl("");
	while (link_len++ < pad->link_len)
		ft_putchar(' ');
	//ft_putendl("test2");
	ft_putnbr(buf.st_nlink);
	ft_putstr(" ");
	ft_print_user(node, pad);
	ft_print_file(node);
}

void	ft_print_name(t_elem *node, t_flag *flag, t_padding *pad)
{
	char			*str;
	struct stat		buf;

	//ft_putendl("starting print_name");
	str = ft_dir_name(node, 0);
	//ft_putstr("str = ");
	//ft_putendl(str);
	if (flag->l)
		ft_print_line(node, pad);
	else if (lstat(str, &buf) != -1)
	{
		if (S_ISDIR(buf.st_mode))
		{
			ft_putstr("\033[1;36m");
		}
		else if (S_ISLNK(buf.st_mode))
			ft_putstr("\033[0;35m");
		ft_putendl(node->name);
		ft_putstr("\033[0;m");
	}
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

void	ft_usage(char c)
{
	ft_putstr_fd("ls: illegal option -- ", 2);
	ft_putchar_fd(c, 2);
	ft_putendl_fd("\nusage: ls [-ABCFGHLOPRSTUWabcdefghiklmnopqrstuwx1]", 2);
	exit(1);
}

char	*ft_strlastchr(char *src, char c)
{
	int		i;

	i = 0;
	while (src[i])
		i++;
	i--;
	while (i >= 0)
	{
		if (c == src[i])
			return (&(src[i + 1]));
		i--;
	}
	return (src);
}
