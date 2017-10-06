/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tools2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyakdi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/06 13:34:28 by jyakdi            #+#    #+#             */
/*   Updated: 2017/10/06 14:54:11 by jyakdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ls.h"

void	ft_print_blocks(struct stat buf, t_padding *pad)
{
	char	*min;
	char	*maj;
	char	len;

	maj = ft_itoa(major(buf.st_rdev));
	min = ft_itoa(minor(buf.st_rdev));
	len = 0;
	while (pad->blocks_len - len > 9)
		len++;
	len = 0;
	while (ft_strlen(maj) + len++ < 3)
		ft_putchar(' ');
	len = 0;
	ft_putstr(maj);
	ft_putchar(',');
	while (ft_strlen(min) + len++ < 4)
		ft_putchar(' ');
	ft_putstr(min);
	ft_strdel(&maj);
	ft_strdel(&min);
}

void	ft_putstrn(char *str, int start, int year)
{
	int		end;

	end = ft_strlen(str) - 9 - 5 * year;
	while (start < end)
	{
		ft_putchar(str[start]);
		start++;
	}
}

void	ft_print_hour(struct stat buf)
{
	time_t		now;
	char		*date;
	int			year;

	now = time(NULL);
	date = ctime(&buf.st_mtime);
	year = ft_atoi(&date[20]);
	if (((int)now - (int)buf.st_mtime >= 15770000) ||
			((int)now - (int)buf.st_mtime <= -3600))
	{
		if (year >= 10000)
			ft_putstrn(date, 4, 2);
		else
			ft_putstrn(date, 4, 1);
		ft_putchar(' ');
		ft_putnbr(year);
	}
	else
		ft_putstrn(date, 4, 0);
	ft_putchar(' ');
}

void	ft_color(struct stat buf)
{
	if (S_ISDIR(buf.st_mode))
		ft_putstr("\33[1;36m");
	else if (S_ISLNK(buf.st_mode))
		ft_putstr("\33[0;35m");
	else if (S_ISFIFO(buf.st_mode))
		ft_putstr("\33[0;91m");
	else if (S_ISCHR(buf.st_mode))
		ft_putstr("\33[0;34;43m");
	else if (S_ISSOCK(buf.st_mode))
		ft_putstr("\33[0;92m");
	else if (S_ISBLK(buf.st_mode))
		ft_putstr("\33[0;34;106m");
}

void	ft_print_file(t_elem *node, t_flag *flag)
{
	char			str[PATH_MAX];
	int				nb;
	struct stat		buf;
	char			*name;

	name = ft_dir_name(node, 0);
	lstat(name, &buf);
	if (flag->color)
	{
		ft_color(buf);
		ft_putstr(node->name);
		ft_putstr("\033[0;m");
	}
	else
		ft_putstr(node->name);
	if (S_ISLNK(buf.st_mode))
	{
		nb = readlink(name, str, PATH_MAX);
		ft_putstr(" -> ");
		write(1, str, nb);
	}
	ft_putendl("");
	ft_strdel(&name);
}
