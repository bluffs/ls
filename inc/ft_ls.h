/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyakdi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/06 12:25:23 by jyakdi            #+#    #+#             */
/*   Updated: 2017/09/06 15:32:01 by jyakdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __FT_LS_H

# define __FT_LS_H

#include <dirent.h>
#include <stdlib.h>
#include "../libft/libft.h"

typedef struct		s_elem
{
	struct t_dirent	*dirent;
	struct s_elem	*beg;
}					t_elem;

typedef struct		s_flag
{
	char	recursive;
	char	list;
}					t_flag;

int					ft_set_flag(t_flag *flag, int argc, char **argv);
void				ft_usage(char c);

#endif
