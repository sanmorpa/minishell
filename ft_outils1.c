/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_outils1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samoreno <samoreno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 17:29:38 by samoreno          #+#    #+#             */
/*   Updated: 2022/03/02 14:38:24 by samoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_is_exact(const char *src, const char *search, size_t n)
{
	size_t	iter;

	iter = 0;
	if ((n > ft_strlen(src) || n > ft_strlen(search))
		&& ft_strlen(src) != ft_strlen(search))
		return (1);
	while (src[iter] && search[iter] && iter < n)
	{
		if (src[iter] != search[iter])
			break ;
		iter++;
	}
	if (iter == ft_strlen(src) || iter == n)
		return (0);
	return (1);
}

void	ft_free(char **array, int words)
{
	int	iter;

	iter = 0;
	while (iter < words)
	{
		free(array[iter]);
		iter++;
	}
	free(array);
}

void	ft_exitfree(char **split, int status, t_list *env)
{
	if (split)
		ft_free(split, ft_count_split(split));
	ft_lstclear(&env, ft_delcontent);
	exit(status);
}

int	ft_count_split(char **split)
{
	int	iter;

	iter = 0;
	while (split[iter])
		iter++;
	return (iter);
}

int	ft_is_number(char *str)
{
	int	iter;

	iter = 0;
	while (str[iter])
	{
		if (ft_isdigit(str[iter]) == 0)
			return (1);
		iter++;
	}
	return (0);
}
