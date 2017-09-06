/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyakdi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/21 08:58:36 by jyakdi            #+#    #+#             */
/*   Updated: 2017/03/23 11:57:06 by jyakdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H

# define GET_NEXT_LINE_H
# define BUFF_SIZE 20

# include <sys/types.h>
# include <sys/stat.h>
# include <sys/uio.h>
# include <unistd.h>
# include <fcntl.h>
# include "libft.h"
# include "stdlib.h"

typedef struct			s_read
{
	int					fd;
	char				*str;
	struct s_read		*next;
}						t_read;

int						get_next_line(const int fd, char **line);
t_read					*create_elem(int fd, char *str, t_read *begin);
int						read_file(int fd, char **str);
int						ft_get_elem(int fd, t_read **elem, t_read **begin);
void					ft_elemdel(t_read **elem);
int						ft_readone(char **str, char **line, int fd);

#endif
