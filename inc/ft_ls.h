/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyakdi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/06 12:25:23 by jyakdi            #+#    #+#             */
/*   Updated: 2017/10/10 16:50:35 by jyakdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __FT_LS_H

# define __FT_LS_H

# include <unistd.h>
# include <dirent.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <limits.h>
# include <errno.h>
# include <pwd.h>
# include <grp.h>
# include <time.h>
# include "../libft/libft.h"
# include <sys/types.h>

/*
** binary tree structure
*/

typedef struct		s_padding
{
	int				total;
	int				rights_len;
	int				link_len;
	int				user_len;
	int				grp_len;
	int				blocks_len;
}					t_padding;

typedef struct		s_elem
{
	char			*src;
	char			*name;
	struct stat		stat;
	struct s_elem	*left;
	struct s_elem	*right;
}					t_elem;

typedef struct		s_flag
{
	char			recursive;
	char			r;
	char			list;
	char			a;
	char			t;
	char			l;
	char			first;
	char			color;
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
void				ft_print_name(t_elem *node, t_flag *flag, t_padding *pad);
void				ft_print_rights(t_elem *node);
int					ft_get_padding(t_elem *elem, t_padding *pad);
void				ft_padding_tree(t_elem *begin, t_padding *pad);
void				ft_print_blocks(struct stat buf, t_padding *pad);
void				ft_print_hour(struct stat buf);
void				ft_print_file(t_elem *node, t_flag *flag);
void				ft_dir_format(t_flag *flag, char *dir_name);
void				ft_free_dir(char **name, char **dir_name,
									t_elem *begin, t_padding **pad);
int					ft_count_blocks(t_elem *elem, int *total);
void				ft_recursive_dir(t_elem *begin, t_flag *flag);

/*
**binary tree functions
*/

t_elem				*ft_register_tree(t_elem *begin, t_elem *n, t_flag *flag);
void				ft_read_tree(t_elem *node, t_flag *flag, t_padding *pad);
t_elem				*ft_register_time(t_elem *begin, t_elem *n,
										char *name, char *name2);
void				ft_del_tree(t_elem *node);
void				ft_read_trash(t_elem *node);
t_elem				*ft_create_node(char *src, char *name, struct stat stat);
void				ft_open_dir(t_elem *list, t_flag *flag, char *nam, char *n);
void				ft_register(t_all **all, char *name, t_flag *flag, char f);

#endif
