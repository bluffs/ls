/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_padding.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyakdi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/25 14:02:38 by jyakdi            #+#    #+#             */
/*   Updated: 2017/10/10 10:41:54 by jyakdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ls.h"

void		ft_get_padding2(t_padding *new, t_padding *pad, struct stat buf)
{
	struct passwd	*user;
	struct group	*group;
	char			*tmp;

	tmp = ft_itoa(buf.st_nlink);
	new->link_len = ft_strlen(tmp);
	ft_strdel(&tmp);
	if (new->link_len > pad->link_len)
		pad->link_len = new->link_len;
	user = getpwuid(buf.st_uid);
	new->user_len = ft_strlen(user->pw_name);
	if (new->user_len > pad->user_len)
		pad->user_len = new->user_len;
	group = getgrgid(buf.st_gid);
	new->grp_len = ft_strlen(group->gr_name);
	if (new->grp_len > pad->grp_len)
		pad->grp_len = new->grp_len;
	if (S_ISCHR(buf.st_mode) || S_ISBLK(buf.st_mode))
		new->blocks_len = 8;
	else
	{
		tmp = ft_itoa(buf.st_size);
		new->blocks_len = ft_strlen(tmp);
		ft_strdel(&tmp);
	}
}

int			ft_get_padding(t_elem *elem, t_padding *pad)
{
	struct stat		buf;
	char			*tmp;
	t_padding		*new;

	if (!(new = ft_memalloc(sizeof(t_padding))))
		ft_error(1, NULL);
	tmp = ft_dir_name(elem, 0);
	if (lstat(tmp, &buf) == -1)
	{
		ft_strdel(&tmp);
		return (-1);
	}
	ft_strdel(&tmp);
	ft_get_padding2(new, pad, buf);
	if (new->blocks_len > pad->blocks_len)
		pad->blocks_len = new->blocks_len;
	ft_memdel((void **)&new);
	return (1);
}

void		ft_padding_tree(t_elem *begin, t_padding *pad)
{
	t_elem		*tmp;

	if (!begin)
		return ;
	tmp = begin;
	ft_get_padding(tmp, pad);
	if (tmp->left)
		ft_padding_tree(tmp->left, pad);
	if (tmp->right)
		ft_padding_tree(tmp->right, pad);
}
