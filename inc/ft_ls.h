/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyakdi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/06 12:25:23 by jyakdi            #+#    #+#             */
/*   Updated: 2017/09/12 14:39:22 by jyakdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __FT_LS_H

# define __FT_LS_H

#include <dirent.h>
#include <stdlib.h>
#include <sys/stat.h>
#include "../libft/libft.h"

/*
** binary tree structure
*/

typedef struct		s_elem
{
	char			*name;
	struct dirent	*dp;
	struct s_elem	*left;
	struct s_elem	*right;
	struct s_elem	*file;
	struct s_elem	*dir;
}					t_elem;

typedef struct		s_flag
{
	char	recursive;
	char	list;
}					t_flag;

int					ft_set_flag(t_flag *flag, int argc, char **argv);
void				ft_usage(char c);
void				ft_error(int n, char *str);

/*
**binary tree functions
*/

t_elem				*ft_register_tree(t_elem *begin, t_elem *n);
void				ft_read_tree(t_elem *node, char n);
void				ft_read_trash(t_elem *node);
t_elem				*ft_create_node(struct dirent *dp, char *name);
void				ft_open_dir(/*t_elem *trash, t_elem *files, t_elem *dir, */char *src);
void				ft_read_dir(t_elem *begin, char n, char *src);
void				ft_register(t_elem **trash, t_elem **files, t_elem **dir, char *src);

#endif
