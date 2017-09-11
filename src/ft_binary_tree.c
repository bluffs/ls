/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_binary_tree.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyakdi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/08 09:44:52 by jyakdi            #+#    #+#             */
/*   Updated: 2017/09/11 15:02:10 by jyakdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ls.h"

t_elem	*ft_create_node(struct dirent *dp, char *name)
{
	t_elem	*node;

	//ft_putendl("create node");
	if (!(node = ft_memalloc(sizeof(t_elem))))
		ft_error(1, NULL);
	node->name = ft_strdup(name);
	node->dp = dp;
	node->left = NULL;
	node->right = NULL;
	//ft_putendl("end create node");
	return (node);
}

void	ft_read_tree(t_elem *node, char n)
{
	if (n == 1)
	{
		if (node)
		{
			if (node->left)
				ft_read_tree(node->left, 1);
			ft_putendl(node->name);
			if (node->right)
				ft_read_tree(node->right, 1);
		}
	}
	else
	{
		if (node)
		{
			if (node->left)
				ft_read_tree(node->right, 2);
			ft_putstr_fd(node->name, 2);
			if (node->right)
				ft_read_tree(node->left, 2);
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

t_elem	*ft_register_tree(t_elem *begin, t_elem *new)
{
	t_elem	*tmp;
	t_elem	*tmp2;

	if (!begin)
		return (new);
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

void	ft_add_dir(t_elem *begin, char *file)
{
	DIR				*dirp;
	struct dirent	*dp;

	if ((dirp = opendir(file)))
	{
		while ((dp = readdir(dirp)))
			ft_register_tree(begin, ft_create_node(dp, file));
		if (closedir(dirp) == -1)
			ft_putendl_fd("Error on close", 2);
	}
	else
	{
		ft_register_tree(begin, ft_create_node(NULL, file));
	}
}
