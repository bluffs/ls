/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_register_time.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyakdi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/10 11:00:27 by jyakdi            #+#    #+#             */
/*   Updated: 2017/10/11 14:54:10 by jyakdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ls.h"

void	ft_register_time3(struct stat buf, struct stat buf2, t_elem **tmp2,
							t_elem *new)
{
	if (buf2.st_mtime == buf.st_mtime)
	{
		if (ft_strcmp((*tmp2)->name, new->name) < 0)
			(*tmp2)->right = new;
		else
			(*tmp2)->left = new;
	}
	else
	{
		if (buf2.st_mtime > buf.st_mtime)
			(*tmp2)->right = new;
		else
			(*tmp2)->left = new;
	}
}

void	ft_register_time2(t_elem **tmp, t_elem *new, struct stat buf,
							struct stat buf2)
{
	if (buf2.st_mtime == buf.st_mtime)
	{
		if (ft_strcmp((*tmp)->name, new->name) < 0)
			*tmp = (*tmp)->right;
		else
			*tmp = (*tmp)->left;
	}
	else
	{
		if (buf2.st_mtime > buf.st_mtime)
			*tmp = (*tmp)->right;
		else
			*tmp = (*tmp)->left;
	}
}

t_elem	*ft_register_time(t_elem *begin, t_elem *new, char *name, char *name2)
{
	t_elem			*tmp;
	t_elem			*tmp2;
	struct stat		buf;
	struct stat		buf2;

	name = ft_dir_name(new, 0);
	if (lstat(name, &buf) == -1)
		exit(1);
	ft_strdel(&name);
	tmp = begin;
	while (tmp)
	{
		if (name2)
			ft_strdel(&name2);
		name2 = ft_dir_name(tmp, 0);
		if (lstat(name2, &buf2) == -1)
			exit(1);
		tmp2 = tmp;
		ft_register_time2(&tmp, new, buf, buf2);
	}
	ft_register_time3(buf, buf2, &tmp2, new);
	ft_strdel(&name2);
	return (begin);
}
