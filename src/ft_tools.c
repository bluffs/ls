/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tools.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyakdi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/06 15:15:27 by jyakdi            #+#    #+#             */
/*   Updated: 2017/09/19 16:57:55 by jyakdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../inc/ft_ls.h"

void	ft_print_line(t_elem *node)
{
	ft_print_rights(node);
	//ft_print_user(node);
	//ft_print_date(node);
	//ft_print_file(node);
}
void	ft_print_name(t_elem *node, t_flag *flag)
{
	char			*str;
	struct stat		buf;

	//ft_putendl("starting print_name");
	str = ft_dir_name(node, 0);
	//ft_putstr("str = ");
	//ft_putendl(str);
	if (lstat(str, &buf) != -1)
	{
		if (S_ISDIR(buf.st_mode))
			ft_putstr("\033[1;36m");
		else if (S_ISLNK(buf.st_mode))
			ft_putstr("\033[0;35m");
		if (flag->l)
			ft_print_line(node);
		else
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
