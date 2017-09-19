/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_binary_tree.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyakdi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/08 09:44:52 by jyakdi            #+#    #+#             */
/*   Updated: 2017/09/19 15:39:35 by jyakdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ls.h"

t_elem	*ft_create_node(char *src, char *name, struct stat stat)
{
	t_elem	*node;

	//ft_putendl("create node");
	if (!(node = ft_memalloc(sizeof(t_elem))))
		ft_error(1, NULL);
	node->name = ft_strdup(name);
	//node->dp = dp;
	node->src = src;
	node->left = NULL;
	node->right = NULL;
	node->stat = stat;
	//ft_putendl("end create node");
	return (node);
}

void	ft_read_tree(t_elem *node, t_flag *flag)
{
	if (flag->r == 0)
	{
		if (node)
		{
			if (node->left)
				ft_read_tree(node->left, flag);
			//ft_putstr("name = ");
			//ft_putendl(node->name);
			if ((flag->a) || (flag->a == 0 && node->name[0] != '.'))
				ft_print_name(node, flag);//ft_putendl(node->name);
			if (node->right)
				ft_read_tree(node->right, flag);
		}
	}
	else
	{
		if (node)
		{
			if (node->right)
				ft_read_tree(node->right, flag);
			if (node->name[0] != '.')
				ft_print_name(node, flag);//ft_putendl(node->name);
			if (node->left)
				ft_read_tree(node->left, flag);
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
	t_elem	*tmp;
	t_elem	*tmp2;

	tmp = begin;
	while (tmp)
	{
		tmp2 = tmp;
		//ft_putstr("time = ");
		//ft_putnbr(tmp->stat.st_mtime);
		if (tmp->stat.st_mtime > new->stat.st_mtime)
			tmp = tmp->right;
		else
			tmp = tmp->left;
	}
	if (tmp2->stat.st_mtime > new->stat.st_mtime)
		tmp2->right = new;
	else
		tmp2->left = new;
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

void	ft_register(t_all **all, char *name, t_flag *flag/*, char *path*/)
{
	struct stat		buf;
	//struct stat		buf2;
	char			src[PATH_MAX];
	int				(*fct)(const char *, struct stat *);

	fct = (flag->l) ? lstat : stat;
	if (fct(name, &buf) != -1)
	{
		if (S_ISREG(buf.st_mode))
		{
			//ft_putstr("adding ");
			//ft_putstr(src);
			//ft_putendl(" to files");
			(*all)->file = ft_register_tree((*all)->file, ft_create_node(NULL, name, buf), flag);
		}
		else if (S_ISDIR(buf.st_mode) || S_ISLNK(buf.st_mode))
		{
			//ft_putstr("adding ");
			//ft_putstr(src);
			//ft_putendl(" to dir");
			(*all)->dir = ft_register_tree((*all)->dir, ft_create_node(NULL, name, buf), flag);
		}
	}
	else
	{
		if (!(ft_strcmp(name, "")))
			ft_error(3, NULL);
		(*all)->trash = ft_register_tree((*all)->trash, ft_create_node(NULL, name, buf), flag);
	}
	//ft_putendl("end registering");
}
