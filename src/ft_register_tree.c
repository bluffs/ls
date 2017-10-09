/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_register_tree.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyakdi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/09 15:22:49 by jyakdi            #+#    #+#             */
/*   Updated: 2017/10/09 17:21:32 by jyakdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ls.h"

void	ft_register_time3(struct stat buf, struct stat buf2, t_elem *tmp2,
							t_elem *new)
{
	if (buf2.st_mtime == buf.st_mtime)
	{
		if (ft_strcmp(tmp2->name, new->name) < 0)
			tmp2->right = new;
		else
			tmp2->left = new;
	}
	else
	{
		if (buf2.st_mtime > buf.st_mtime)
			tmp2->right = new;
		else
			tmp2->left = new;
	}
}

void	ft_register_time2(t_elem *tmp, t_elem *new, struct stat buf,
							struct stat buf2)
{
	if (buf2.st_mtime == buf.st_mtime)
	{
		if (ft_strcmp(tmp->name, new->name) < 0)
			tmp = tmp->right;
		else
			tmp = tmp->left;
	}
	else
	{
		if (buf2.st_mtime > buf.st_mtime)
			tmp = tmp->right;
		else
			tmp = tmp->left;
	}
}

t_elem	*ft_register_time(t_elem *begin, t_elem *new)
{
	t_elem			*tmp;
	t_elem			*tmp2;
	struct stat		buf;
	struct stat		buf2;
	char			*name;
	char			*name2;

	name2 = NULL;
	name = ft_dir_name(new, 0);
	if (lstat(name, &buf) == -1)
	{
		ft_strdel(&name);
		exit(1);
	}
	ft_strdel(&name);
	tmp = begin;
	while (tmp)
	{
		if (name2)
			ft_strdel(&name2);
		name2 = ft_dir_name(tmp, 0);
		if (lstat(name2, &buf2) == -1)
		{
			ft_strdel(&name2);
			exit(1);
		}
		tmp2 = tmp;
		//ft_register_time2(tmp, new, buf, buf2);
		if (buf2.st_mtime == buf.st_mtime)
		{
			if (ft_strcmp(tmp->name, new->name) < 0)
				tmp = tmp->right;
			else
				tmp = tmp->left;
		}
		else
		{
			if (buf2.st_mtime > buf.st_mtime)
				tmp = tmp->right;
			else
				tmp = tmp->left;
		}
	}
	//ft_register_time3(buf, buf2, tmp2, new);
	if (buf2.st_mtime == buf.st_mtime)
	{
		if (ft_strcmp(tmp2->name, new->name) < 0)
			tmp2->right = new;
		else
			tmp2->left = new;
	}
	else
	{
		if (buf2.st_mtime > buf.st_mtime)
			tmp2->right = new;
		else
			tmp2->left = new;
	}
	return (begin);
}

t_elem	*ft_register_tree(t_elem *begin, t_elem *new, t_flag *flag)
{
	t_elem	*tmp;
	t_elem	*tmp2;

	if (!begin)
		return (new);
	if (flag->t)
		return (ft_register_time(begin, new));
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
			|| S_ISCHR(buf.st_mode) || S_ISLNK(buf.st_mode))
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
