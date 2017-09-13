/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_binary_tree.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyakdi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/08 09:44:52 by jyakdi            #+#    #+#             */
/*   Updated: 2017/09/13 14:04:51 by jyakdi           ###   ########.fr       */
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

	//ft_putendl("reading dir");
	if (node)
	{
		/*if (!(path = ft_memalloc(sizeof(char) * (ft_strlen(src) + ft_strlen(node->name) + 1))))
			exit(0);
		path = ft_strjoin(src, "/");
		path = ft_strjoin(path, node->name);*/
	/*ft_putendl("malloc'd");
	ft_putstr(src);
	ft_putstr(" + ");
	ft_putendl(node->name);*/
	}
	if (n == 1)
	{
		if (node)
		{
			if (node->left)
				ft_read_dir(node->left, 1, src);
			ft_putstr(node->name);
			ft_putendl(":");
			ft_open_dir(node->name);
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
	//ft_putendl("end read_dir");
}

void	ft_register(t_elem **trash, t_elem **files, t_elem **dir, char *name, char *path)
{
	struct stat		buf;
	char			*src;

	if (!(src = ft_memalloc(sizeof(char) * (ft_strlen(name) + ft_strlen(path) + 1))))
		exit(1);
	src = ft_strjoin(path, "/");
	src = ft_strjoin(src, name);
	//ft_putstr("registering = ");
	//ft_putendl(src);
	if (name[0] == '.')
		return ;
	if (lstat(src, &buf) != -1)
	{
		if (S_ISREG(buf.st_mode))
		{
			//ft_putstr("adding ");
			//ft_putstr(src);
			//ft_putendl(" to files");
			*files = ft_register_tree(*files, ft_create_node(NULL, name));
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
		if (!(ft_strcmp(name, "")))
			ft_error(3, NULL);
		*trash = ft_register_tree(*trash, ft_create_node(NULL, name));
	}
}

void	ft_open_dir(/*t_elem *trash, t_elem *files, t_elem *dir, */char *src)
{
	//ft_putstr("opening dir : ");
	//ft_putendl(src);
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
		{
			ft_register(&trash, &files, &dir, dp->d_name, src);
		}
		if (closedir(dirp) == -1)
			ft_putendl_fd("Error on close", 2);
	}
	else
		ft_error(4, src);
	//ft_putendl("end dir\nread trash");
	ft_read_trash(trash);
	//ft_putendl("read files");
	ft_read_tree(files, 1);
	//ft_putendl("read dir");
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
