/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_binary_tree.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyakdi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/08 09:44:52 by jyakdi            #+#    #+#             */
/*   Updated: 2017/09/12 15:12:41 by jyakdi           ###   ########.fr       */
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

void	ft_read_dir(t_elem *node, char n, char *src)
{
	char *path;

	if (!(path = ft_memalloc(sizeof(char) * (ft_strlen(src) + ft_strlen(node->name)))))
		exit(0);
	ft_putstr(src);
	ft_putstr(" + ");
	ft_putendl(node->name);
	path = ft_strjoin(src, node->name);
	if (n == 1)
	{
		if (node)
		{
			if (node->left)
				ft_read_dir(node->left, 1, src);
			ft_putstr(node->name);
			ft_putendl(":");
			ft_open_dir(path);
			if (node->right)
				ft_read_dir(node->right, 1, src);
		}
	}
	else
	{
		if (node)
		{
			if (node->left)
				ft_read_dir(node->right, 2, src);
			ft_putstr(node->name);
			ft_putendl(":");
			ft_open_dir(ft_strjoin(src, node->name));
			if (node->right)
				ft_read_dir(node->left, 2, src);
		}
	}
}

void	ft_register(t_elem **trash, t_elem **files, t_elem **dir, char *src)
{
	struct stat		buf;

	if (src[0] == '.')
		return ;
	if (lstat(src, &buf) != -1)
	{
		if (S_ISREG(buf.st_mode))
		{
			//ft_putstr("adding ");
			//ft_putstr(src);
			//ft_putendl(" to files");
			*files = ft_register_tree(*files, ft_create_node(NULL, src));
		}
		else if (S_ISDIR(buf.st_mode))
		{
			//ft_putstr("adding ");
			//ft_putstr(src);
			//ft_putendl(" to dir");
			*dir = ft_register_tree(*dir, ft_create_node(NULL, src));
		}
	}
	else
	{
		if (!(ft_strcmp(src, "")))
			ft_error(3, NULL);
		*trash = ft_register_tree(*trash, ft_create_node(NULL, src));
	}
}

void	ft_open_dir(/*t_elem *trash, t_elem *files, t_elem *dir, */char *src)
{
	ft_putstr("opening dir : ");
	ft_putendl(src);
	DIR				*dirp;
	struct dirent	*dp;
	t_elem			*trash;
	t_elem			*files;
	t_elem			*dir;

	files = NULL;
	trash = NULL;
	dir = NULL;
	if ((dirp = opendir(src)))
	{
		while ((dp = readdir(dirp)))
			ft_register(&trash, &files, &dir, dp->d_name);
		if (closedir(dirp) == -1)
			ft_putendl_fd("Error on close", 2);
	}
	else
		ft_error(4, src);
	ft_putendl("end dir");
	ft_read_trash(trash);
	ft_putendl("read files");
	ft_read_tree(files, 1);
	ft_putendl("read dir");
	ft_putendl("");
	ft_read_dir(dir, 1, src);
}

/*t_elem	*ft_open_dir(char *dir)*/
/*{*/
/*DIR				*dirp;*/
/*struct dirent	*dp;*/
/*t_elem			*begin;*/

/*begin = NULL;*/
/*if ((dirp = opendir(dir)))*/
/*{*/
/*while ((dp = readdir(dirp)))*/
/*begin = ft_register_tree(begin, ft_create_node(dp, dir));*/
/*if (closedir(dirp) == -1)*/
/*ft_putendl_fd("Error on close", 2);*/
/*}*/
/*else*/
/*ft_error(4, dir);*/
/*return (begin);*/
/*}*/
