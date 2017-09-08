/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_binary_tree.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyakdi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/08 09:44:52 by jyakdi            #+#    #+#             */
/*   Updated: 2017/09/08 14:44:22 by jyakdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_elem	*ft_create_node(struct dirent *dp)
{
	t_elem	*node;

	//ft_putendl("create node");
	if (!(node = ft_memalloc(sizeof(t_elem))))
		ft_error(1);
	node->dp = dp;
	node->left = NULL;
	node->right = NULL;
	//ft_putendl("end create node");
	return (node);
}

void	ft_read_tree_asc(t_elem *node)
{
	if (node->left)
		ft_read_tree_asc(node->left);
	ft_putendl(node->dp->d_name);
	if (node->right)
		ft_read_tree_asc(node->right);
}

t_elem	*ft_register_tree(t_elem *begin, t_elem *new)
{
	t_elem	*tmp;
	t_elem	*tmp2;

	//ft_putendl(new->dp->d_name);
	if (!begin)
		return (new);
	//ft_putendl("test1");
	tmp = begin;
	while (tmp)
	{
		//ft_putendl("test2");
		tmp2 = tmp;
		//ft_putendl("test3");
		if (strcmp(tmp->dp->d_name, new->dp->d_name) < 0)
		{
			//ft_putendl("test4");
			tmp = tmp->right;
		}
		else
		{
			//ft_putendl("test5");
			tmp = tmp->left;
		}
		//ft_putendl("6");
	}
	//ft_putendl("test7");
	if (strcmp(tmp2->dp->d_name, new->dp->d_name) < 0)
		tmp2->right = new;
	else
		tmp2->left = new;
	//ft_putendl("end register");
	return (begin);
}
