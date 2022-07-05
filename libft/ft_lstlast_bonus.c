/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samoreno <samoreno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 10:46:25 by samoreno          #+#    #+#             */
/*   Updated: 2022/02/28 11:31:27 by samoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*tempt_list;

	tempt_list = lst;
	while (tempt_list)
	{
		if (tempt_list->next)
		{
			tempt_list = tempt_list->next;
		}
		else
			return (tempt_list);
	}
	return (tempt_list);
}
