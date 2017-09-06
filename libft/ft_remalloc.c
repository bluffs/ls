/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_remalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyakdi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/21 11:16:13 by jyakdi            #+#    #+#             */
/*   Updated: 2016/11/25 11:54:46 by jyakdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	*ft_remalloc(void **mem, void *mem2)
{
	void	*new;

	new = ft_strjoin((char *)*mem, (char *)mem2);
	free(*mem);
	return (new);
}
