/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_outils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samoreno <samoreno@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 10:45:47 by samoreno          #+#    #+#             */
/*   Updated: 2022/07/06 09:33:42 by samoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_delcontent(void *content)
{
	t_dict	*dict;

	dict = content;
	free(dict->key);
	free(dict->value);
	free(dict);
	return ;
}

void	ft_delcopy(void *content)
{
	(void)content;
}

void	ft_printenv(void *env)
{
	t_dict	*el;

	el = env;
	if (el->value[0] != 0 && ft_is_exact(el->key, "?", ft_strlen(el->key) != 0))
		printf("%s=%s\n", el->key, el->value);
}

void	*ft_placeholder(void *content)
{
	return (content);
}
