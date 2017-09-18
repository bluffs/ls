/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_binary_tree.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyakdi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/08 09:44:52 by jyakdi            #+#    #+#             */
/*   Updated: 2017/09/18 16:30:58 by jyakdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ls.h"

t_elem	*ft_create_node(char *src, char *name)
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
				ft_print_name(node);//ft_putendl(node->name);
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
				ft_print_name(node);//ft_putendl(node->name);
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

t_elem	*ft_register_tree(t_elem *begin, t_elem *new)
{
	t_elem	*tmp;
	t_elem	*tmp2;

	//ft_putendl("placing elem");
	if (!begin)
	{
		//ft_putendl("first elem");
		return (new);
	}
	//ft_putendl("not first elem");
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

void	ft_register(t_all **all, char *name/*, char *path*/)
{
	struct stat		buf;
	//struct stat		buf2;
	char			src[PATH_MAX];

	/*if (!(src = ft_memalloc(sizeof(char) * (ft_strlen(name) + ft_strlen(path) + 1))))
		exit(1);
	src = ft_strjoin(path, "/");
	src = ft_strjoin(src, name);*/
	//ft_putstr("registering = ");
	//ft_putendl(name);
	//if (!(*all)->file)
	//	ft_putendl("file is NULL");
	/*if ((*all)->flag->a = 0 && name[0] == '.')
		return ;*/
	if (stat(name, &buf) != -1)
	{
		/*ft_putstr("buf = ");
		ft_putnbr(buf.st_mode);
		ft_putendl("");*/
		//src = ft_memalloc(sizeof(char) * buf.st_size + 1);
		/*if (S_ISLNK(buf.st_mode))
		{
			//src = ft_link(name, &buf);
			ft_putstr("src is a symbolic link = ");
			ft_putendl(name);
			if ((readlink(name, src, PATH_MAX) != -1))
			{
				ft_putstr("link = ");
				ft_putendl(src);
			}
			//ft_putendl(strerror(errno));
			ft_putstr("src = ");
			ft_putendl(src);
		}*/
		/*if (!(stat(src, &buf)))
			ft_putendl("2nd lsts fail");
		ft_putstr("buf2 after lstat = ");
		 || flag->aft_putnbr(buf.st_mode);
		ft_putendl("");*/
		/*if (S_ISLNK(buf.st_mode))
		{
			ft_putstr("src is a symbolic link = ");
			ft_putendl(src);
		}*/
		if (S_ISREG(buf.st_mode))
		{
			//ft_putstr("adding ");
			//ft_putstr(src);
			//ft_putendl(" to files");
			(*all)->file = ft_register_tree((*all)->file, ft_create_node(NULL, name));
		}
		else if (S_ISDIR(buf.st_mode))
		{
			//ft_putstr("adding ");
			//ft_putstr(src);
			//ft_putendl(" to dir");
			(*all)->dir = ft_register_tree((*all)->dir, ft_create_node(NULL, name));
		}
	}
	else
	{
		if (!(ft_strcmp(name, "")))
			ft_error(3, NULL);
		(*all)->trash = ft_register_tree((*all)->trash, ft_create_node(NULL, name));
	}
	//ft_putendl("end registering");
}

//void	ft_open_dir(/*t_elem *trash, t_elem *files, t_elem *dir, */char *src)
/*{*/
	/*//ft_putstr("opening dir : ");*/
	/*//ft_putendl(src);*/
	/*DIR				*dirp;*/
	/*struct dirent	*dp;*/
	/*t_elem			*trash;*/
	/*t_elem			*files;*/
	/*t_elem			*dir;*/

	/*files = NULL;*/
	/*trash = NULL;*/
	/*dir = NULL;*/
	/*if ((dirp = opendir(src)))*/
	/*{*/
		/*while ((dp = readdir(dirp)))*/
		/*{*/
			/*//ft_register(&trash, &files, &dir, dp->d_name, src);*/
		/*}*/
		/*if (closedir(dirp) == -1)*/
			/*ft_putendl_fd("Error on close", 2);*/
	/*}*/
	/*else*/
		/*ft_error(4, src);*/
	/*//ft_putendl("end dir\nread trash");*/
	/*ft_read_trash(trash);*/
	/*//ft_putendl("read files");*/
	/*//ft_read_tree(files, 1);*/
	/*//ft_putendl("read dir");*/
	/*ft_putendl("");*/
	/*ft_read_dir(dir, 1, src);*/
/*}*/

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
