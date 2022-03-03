/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samoreno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 13:19:27 by samoreno          #+#    #+#             */
/*   Updated: 2021/11/12 13:19:28 by samoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*copy_ret;
	t_list	*new_lst;

	if (!lst || !f)
		return (NULL);
	new_lst = ft_lstnew(f((*lst).content));
	if (!new_lst)
		return (NULL);
	copy_ret = new_lst;
	lst = (*lst).next;
	while (lst)
	{
		(*new_lst).next = ft_lstnew(f((*lst).content));
		if (!(*new_lst).next)
		{
			ft_lstclear(&copy_ret, del);
			return (NULL);
		}
		new_lst = (*new_lst).next;
		lst = (*lst).next;
	}
	(*new_lst).next = NULL;
	return (copy_ret);
}
