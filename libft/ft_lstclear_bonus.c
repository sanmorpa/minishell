/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samoreno <samoreno@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 12:53:07 by samoreno          #+#    #+#             */
/*   Updated: 2022/08/05 10:59:03 by samoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*temporal;

	if (lst && del)
	{
		while (*lst)
		{
			temporal = (**lst).next;
			del((**lst).content);
			free(*lst);
			*lst = temporal;
		}
	}
}
