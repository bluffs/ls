/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_binary_tree.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyakdi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/08 09:44:52 by jyakdi            #+#    #+#             */
/*   Updated: 2017/10/06 13:30:45 by jyakdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ls.h"

t_elem	*ft_create_node(char *src, char *name, struct stat stat)
{
	t_elem	*node;
	char	*new_src;

	if (!(node = ft_memalloc(sizeof(t_elem))))
		ft_error(1, NULL);
	node->name = ft_strdup(name);
	if (src)
		node->src = ft_strdup(src);
	node->left = NULL;
	node->right = NULL;
	node->stat = stat;
	return (node);
}

void	ft_read_tree(t_elem *node, t_flag *flag, t_padding *pad)
{
	if (flag->r == 0)
	{
		if (node)
		{
			if (node->left)
				ft_read_tree(node->left, flag, pad);
			if ((flag->a) || (flag->a == 0 && node->name[0] != '.'))
				ft_print_name(node, flag, pad);
			if (node->right)
				ft_read_tree(node->right, flag, pad);
		}
	}
	else
	{
		if (node)
		{
			if (node->right)
				ft_read_tree(node->right, flag, pad);
			if ((flag->a) || (flag->a == 0 && node->name[0] != '.'))
				ft_print_name(node, flag, pad);
			if (node->left)
				ft_read_tree(node->left, flag, pad);
		}
	}
}

void	ft_read_trash(t_elem *node)
{
	if (node)
	{
		if (node->left)
			ft_read_trash(node->left);
		ft_putstr_fd("ls: ", 2);
		ft_putstr_fd(node->name, 2);
		ft_putendl_fd(": No such file or directory", 2);
		if (node->right)
			ft_read_trash(node->right);
	}
}

t_elem	*ft_register_time(t_elem *begin, t_elem *new, t_flag *flag)
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
		exit(0);
	}
	tmp = begin;
	while (tmp)
	{
		if (name2)
			ft_strdel(&name2);
		name2 = ft_dir_name(tmp, 0);
		if (lstat(name2, &buf2) == -1)
		{
			ft_strdel(&name2);
			exit(0);
		}
		tmp2 = tmp;
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
	ft_strdel(&name);
	return (begin);
}

t_elem	*ft_register_tree(t_elem *begin, t_elem *new, t_flag *flag)
{
	t_elem	*tmp;
	t_elem	*tmp2;

	if (!begin)
		return (new);
	if (flag->t)
		return (ft_register_time(begin, new, flag));
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

void	ft_register(t_all **all, char *name, t_flag *flag, char fonc)
{
	struct stat		buf;
	int				(*fct)(const char *, struct stat *);

	fct = (flag->l || fonc) ? lstat : stat;
	if (fct(name, &buf) != -1)
	{
		if (S_ISREG(buf.st_mode) || S_ISBLK(buf.st_mode)
				|| S_ISCHR(buf.st_mode) || S_ISLNK(buf.st_mode))
			(*all)->file = ft_register_tree((*all)->file,
					ft_create_node(NULL, name, buf), flag);
		else if (S_ISDIR(buf.st_mode))
			(*all)->dir = ft_register_tree((*all)->dir,
					ft_create_node(NULL, name, buf), flag);
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

void	ft_del_tree(t_elem *node)
{
	if (node->left)
		ft_del_tree(node->left);
	if (node->right)
		ft_del_tree(node->right);
	if (node->name)
		ft_strdel(&node->name);
	if (node->src)
		ft_strdel(&node->src);
	ft_memdel((void **)&node);
}
