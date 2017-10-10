/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tools3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyakdi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/06 14:33:12 by jyakdi            #+#    #+#             */
/*   Updated: 2017/10/10 11:25:25 by jyakdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ls.h"

void	ft_dir_format(t_flag *flag, char *dir_name)
{
	if (flag->first & 1)
		flag->first -= 1;
	else
		ft_putendl("");
	if (flag->first & 2)
		flag->first -= 2;
	else
	{
		ft_putstr(dir_name);
		ft_putendl(":");
	}
}

void	ft_free_dir(char **name, char **dir_nam, t_elem *begin, t_padding **pad)
{
	ft_strdel(name);
	ft_strdel(dir_nam);
	if (begin)
		ft_del_tree(begin);
	if (pad)
		ft_memdel((void **)pad);
}

char	*ft_dir_name(t_elem *dir, char n)
{
	char	*name;

	if (!(name = ft_memalloc(sizeof(char) *
					(ft_strlen(dir->src) + ft_strlen(dir->name) + 1 + n))))
		ft_error(1, NULL);
	name = ft_strcat(name, dir->src);
	name = ft_strcat(name, dir->name);
	if (n && name[ft_strlen(name) - 1] != '/')
		name = ft_strcat(name, "/");
	return (name);
}

void	ft_usage(char c)
{
	ft_putstr_fd("ls: illegal option -- ", 2);
	ft_putchar_fd(c, 2);
	ft_putendl_fd(
		"\nusage: ls [-ABCFGHLOPRSTUWabcdefghiklmnopqrstuwx1] [file ...]", 2);
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
