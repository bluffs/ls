/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyakdi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/24 14:09:12 by jyakdi            #+#    #+#             */
/*   Updated: 2017/03/23 11:56:49 by jyakdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_read		*create_elem(int fd, char *str, t_read *begin)
{
	t_read	*elem;
	t_read	*tmp;

	if (!(elem = ft_memalloc(sizeof(t_read))))
		return (NULL);
	elem->fd = fd;
	if (str != NULL)
		elem->str = str;
	elem->next = NULL;
	tmp = begin;
	if (tmp == NULL)
		return (elem);
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = elem;
	return (begin);
}

int			read_file(int fd, char **str)
{
	int		ret;
	char	*buf;
	char	*tmp;

	ret = 1;
	buf = ft_memalloc(BUFF_SIZE + 1);
	while (!*str || (!(ft_strchr(*str, '\n')) && ret))
	{
		ret = read(fd, buf, BUFF_SIZE);
		if (ret == -1)
			return (ret);
		buf[ret] = 0;
		if (!*str)
			*str = ft_strdup(buf);
		else
		{
			tmp = ft_strjoin(*str, buf);
			ft_strdel(str);
			*str = tmp;
		}
	}
	ft_strdel(&buf);
	if (**str == '\0')
		return (0);
	return (1);
}

char		*ft_register(int fd, char **str, t_read **elem, t_read **begin)
{
	int		i;
	char	*tmp;
	char	*line;

	i = 0;
	while (*(*str + i) && *(*str + i) != '\n')
		i++;
	line = ft_strsub(*str, 0, i);
	tmp = ft_strsub(*str, i + 1, ft_strlen(*str) - i);
	if (tmp)
	{
		if (*elem)
			(*elem)->str = ft_strdup(tmp);
		else
			*begin = create_elem(fd, ft_strdup(tmp), *begin);
	}
	else if (*elem)
		(*elem)->str = NULL;
	ft_strdel(str);
	ft_strdel(&tmp);
	return (line);
}

void		ft_listdel(t_read *begin, t_read *elem)
{
	t_read	*first;
	t_read	*second;

	if (ft_strcmp(elem->str, "\0") == 0)
	{
		if (begin->fd == elem->fd)
			begin = elem->next;
		else
		{
			first = begin;
			while (first && first->fd != elem->fd)
			{
				second = first;
				first = first->next;
			}
			second->next = first->next;
		}
		ft_strdel(&elem->str);
		free(elem);
	}
}

int			get_next_line(const int fd, char **line)
{
	static t_read	*begin = NULL;
	t_read			*elem;
	char			*str;
	int				end;

	end = 1;
	str = NULL;
	elem = begin;
	if (fd < 0 || !line)
		return (-1);
	while (elem && elem->fd != fd)
		elem = elem->next;
	if (elem)
		str = elem->str;
	end = read_file(fd, &str);
	if (end == -1)
		return (-1);
	*line = ft_register(fd, &str, &elem, &begin);
	if (end == 0 && elem)
		ft_listdel(begin, elem);
	return (end);
}
