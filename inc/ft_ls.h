/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyakdi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/06 12:25:23 by jyakdi            #+#    #+#             */
/*   Updated: 2017/09/18 16:04:02 by jyakdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __FT_LS_H

# define __FT_LS_H

#include <unistd.h>
#include <dirent.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <limits.h>
#include <errno.h>
#include "../libft/libft.h"

/*
** binary tree structure
*/

typedef struct		s_elem
{
	char			*src;
	char			*name;
	//struct dirent	*dp;
	struct s_elem	*left;
	struct s_elem	*right;
	//struct s_elem	*file;
	//struct s_elem	*dir;
}					t_elem;

typedef struct		s_flag
{
	char			recursive;
	char			r;
	char			list;
	char			a;
}					t_flag;

typedef struct		s_all
{
	char			*name;
	t_flag			*flag;
	t_elem			*trash;
	t_elem			*file;
	t_elem			*dir;
}					t_all;

t_all				*ft_init_all(void);
int					ft_set_flag(t_flag *flag, int argc, char **argv);
void				ft_usage(char c);
void				ft_error(int n, char *str);
char				*ft_strlastchr(char *src, char c);
char				*ft_dir_name(t_elem *dir, char n);
void				ft_print_name(t_elem *node);

/*
**binary tree functions
*/

t_elem				*ft_register_tree(t_elem *begin, t_elem *n);
void				ft_read_tree(t_elem *node, t_flag *flag);
void				ft_read_trash(t_elem *node);
t_elem				*ft_create_node(char *src, char *name);
void				ft_open_dir(t_elem *list, t_flag *flag);
//void				ft_read_dir(t_elem	*list, t_flag *flag);
void				ft_register(t_all **all, char *name/*, char *path*/);

#endif
