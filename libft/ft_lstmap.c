/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyakdi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/12 09:17:22 by jyakdi            #+#    #+#             */
/*   Updated: 2016/11/12 11:09:01 by jyakdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*begin_list;
	t_list	*tmp1;
	t_list	*tmp2;

	begin_list = (*f)(lst);
	tmp2 = begin_list;
	while (lst->next)
	{
		lst = lst->next;
		tmp1 = (*f)(lst);
		tmp2->next = ft_lstnew(tmp1->content, tmp1->content_size);
		tmp2 = tmp2->next;
	}
	return (begin_list);
}
