/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_padding.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyakdi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/25 14:02:38 by jyakdi            #+#    #+#             */
/*   Updated: 2017/09/27 11:58:16 by jyakdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ls.h"

void		ft_get_padding(t_elem *elem, t_padding *pad)
{
	// use t_pad to store all ints
	int				name_len;
	int				link_len;
	struct stat		buf;
	int				user_len;
	int				grp_len;
	int				blocks_len;
	struct passwd	*user;
	struct group	*group;

	lstat(ft_dir_name(elem, 0), &buf);
	link_len = ft_strlen(ft_itoa(buf.st_nlink));
	if (link_len > pad->link_len)
		pad->link_len = link_len;
	user = getpwuid(buf.st_uid);
	user_len = ft_strlen(user->pw_name);
	if (user_len > pad->user_len)
		pad->user_len = user_len;
	group = getgrgid(buf.st_gid);
	grp_len = ft_strlen(group->gr_name);
	if (grp_len > pad->grp_len)
		pad->grp_len = grp_len;
	blocks_len = ft_strlen(ft_itoa(buf.st_size));
	if (blocks_len > pad->blocks_len)
		pad->blocks_len = blocks_len;
}

void		ft_padding_tree(t_elem *begin, t_padding *pad)
{
	t_elem		*tmp;

	if (!begin)
		return ;
	//ft_putstr("Hi");
	//ft_putendl(begin->name);
	//ft_putendl("ok");
	tmp = begin;
	ft_get_padding(tmp, pad);
	if (tmp->left)
		ft_padding_tree(tmp->left, pad);
	if (tmp->right)
		ft_padding_tree(tmp->right, pad);
}
