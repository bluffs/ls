/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_register_tree.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyakdi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/09 15:22:49 by jyakdi            #+#    #+#             */
/*   Updated: 2017/10/12 11:18:09 by jyakdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ls.h"

t_elem	*ft_register_tree(t_elem *begin, t_elem *new, t_flag *flag)
{
	t_elem	*tmp;
	t_elem	*tmp2;

	if (!begin)
		return (new);
	if (flag->t)
		return (ft_register_time(begin, new, NULL, NULL));
	tmp = begin;
	while (tmp)
	{
		tmp2 = tmp;
		if (ft_strcmp(tmp->name, new->name) < 0)
			tmp = tmp->right;
		else
			tmp = tmp->left;
	}
	if (ft_strcmp(tmp2->name, new->name) < 0)
		tmp2->right = new;
	else
		tmp2->left = new;
	return (begin);
}

void	ft_register2(t_all **all, struct stat buf, char *name, t_flag *flag)
{
	if (S_ISREG(buf.st_mode) || S_ISBLK(buf.st_mode)
			|| S_ISCHR(buf.st_mode) || S_ISLNK(buf.st_mode)
			|| S_ISFIFO(buf.st_mode) || S_ISSOCK(buf.st_mode))
		(*all)->file = ft_register_tree((*all)->file,
				ft_create_node(NULL, name, buf), flag);
	else if (S_ISDIR(buf.st_mode))
		(*all)->dir = ft_register_tree((*all)->dir,
				ft_create_node(NULL, name, buf), flag);
}

void	ft_register(t_all **all, char *name, t_flag *flag, char fonc)
{
	struct stat		buf;
	int				(*fct)(const char *, struct stat *);

	fct = (flag->l || fonc) ? lstat : stat;
	if (fct(name, &buf) != -1)
	{
		ft_register2(all, buf, name, flag);
	}
	else
	{
		if (fct == stat)
		{
			ft_register(all, name, flag, 1);
			return ;
		}
		if (!(ft_strcmp(name, "")))
			ft_error(3, NULL);
		(*all)->trash = ft_register_tree((*all)->trash,
				ft_create_node(NULL, name, buf), flag);
	}
}
