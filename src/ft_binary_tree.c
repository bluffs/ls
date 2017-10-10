/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_binary_tree.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyakdi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/08 09:44:52 by jyakdi            #+#    #+#             */
/*   Updated: 2017/10/10 16:49:51 by jyakdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ls.h"

t_elem	*ft_create_node(char *src, char *name, struct stat stat)
{
	t_elem	*node;

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
