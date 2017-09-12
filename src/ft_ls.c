/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyakdi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/06 11:17:28 by jyakdi            #+#    #+#             */
/*   Updated: 2017/09/12 14:42:52 by jyakdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ls.h"

int		main(int argc, char **argv)
{
	//DIR				*dirp;
	struct dirent	*dp;
	t_flag			*flag;
	int				i;
	t_elem			*dir;
	struct stat		buf;
	t_elem			*trash;
	t_elem			*files;

	files = NULL;
	trash = NULL;
	dir = NULL;
	i = ft_set_flag(flag, argc, argv);
	/*ft_putstr("i = ");*/
	/*ft_putnbr(i + 1);*/
	/*ft_putstr("\nOpening ");*/
	/*ft_putendl(argv[i + 1]);*/
	/*//ft_putstr("nb = ");*/
	/*//stat(argv[i + 1], &buf);*/
	/*//ft_putnbr(buf.st_mode);*/
	while (++i < argc)
	{
		if (argv[i][0] && argv[i][1] != '.')
		{
			//ft_putstr("reading ");
			//ft_putendl(argv[i]);
			//ft_putstr("nb = ");
			//lstat(argv[i], &buf);
			//ft_putnbr(buf.st_mode);
			//ft_putendl("");
			ft_register(&trash, &files, &dir, argv[i]);
		   /* if (lstat(argv[i], &buf) != -1)*/
			/*{*/
				/*if (S_ISREG(buf.st_mode))*/
					/*files = ft_register_tree(files, ft_create_node(NULL, argv[i]));*/
					/*//ft_add_file(argv[i], );*/
				/*else if (S_ISDIR(buf.st_mode))*/
				/*{*/
					/*[>ft_add_dir(begin, argv[i]);<]*/
					/*//if ((dp = ft_open(argv[i])))*/
						/*begin = ft_register_tree(begin, ft_create_node(NULL, argv[i]));*/
				/*}*/
				/*//ft_add_dir(argv[i]);*/
			/*}*/
			/*else*/
			/*{*/
				/*if (!(ft_strcmp(argv[i], "")))*/
					/*ft_error(3, NULL);*/
				/*//ft_putendl("adding to trash");*/
				/*trash = ft_register_tree(trash, ft_create_node(NULL, argv[i]));*/
		   /* }*/
		}
		//ft_add_trash(argv[i]);
	}
	//ft_putendl("gonna read trash");
	ft_read_trash(trash);
	ft_read_tree(files, 1);
	ft_putendl("");
	ft_read_dir(dir, 1, "./");
		/*if ((dirp = opendir(argv[i])))*/
		/*{*/
			/*ft_putendl("open OK");*/
			/*while ((dp = readdir(dirp)))*/
			/*{*/
				/*ft_putendl(dp->d_name);*/
				/*node = ft_create_node(dp);*/
				/*ft_putendl(node->dp->d_name);*/
				/*ft_putendl("calling register");*/
				/*begin = ft_register_tree(begin, ft_create_node(dp));*/
				/*ft_putendl("end register");*/
			/*}*/
			/*if (closedir(dirp) == -1)*/
				/*ft_putendl_fd("Error on close", 2);*/
		/*}*/
		/*else*/
		/*{*/
			/*ft_error(2, argv[i]);*/
		/*}*/
	/*}*/
	/*ft_read_tree_asc(begin);*/
	return (0);
}
