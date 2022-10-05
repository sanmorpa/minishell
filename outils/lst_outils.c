/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_outils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josuna-t <josuna-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 10:45:47 by samoreno          #+#    #+#             */
/*   Updated: 2022/08/08 15:52:01 by josuna-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	delcontent(void *content)
{
	t_dict	*dict;

	dict = content;
	if (dict->key)
		free(dict->key);
	if (dict->value)
		free(dict->value);
	if (dict)
		free(dict);
}

void	ft_delcopy(void *content)
{
	(void)content;
}

void	ft_printenv(void *env)
{
	t_dict	*el;
	size_t	i;

	el = env;
	i = 0;
	if (el->value && ft_is_exact(el->key, "?", ft_strlen(el->key), 0)
		!= 0)
	{
		printf("%s=", el->key);
		if (ft_strchr(el->value, '$'))
				i++;
		while (el->value[i] || (ft_strchr(el->value, '$')
				&& i < ft_strlen(el->value) - 1))
		{
			if (el->value[i] == 1)
				printf("'");
			else if (el->value[i] == 2)
				printf("\"");
			else
				printf("%c", el->value[i]);
			i++;
		}
		printf("\n");
	}
}

char	**ft_lsttostring(t_list *lst)
{
	char	**list;
	int		index;
	t_dict	*el;
	char	*tempchar;

	index = 0;
	list = malloc(sizeof(lst) * (ft_lstsize(lst) + 1));
	while (lst)
	{
		el = lst->content;
		if (el->value != 0)
		{
			tempchar = ft_strjoin(el->key, "=");
			list[index] = ft_strjoin(tempchar, el->value);
			free(tempchar);
		}
		else
			list[index] = ft_strjoin(el->key, "");
		lst = lst->next;
		index++;
	}
	list[index] = 0;
	return (list);
}

void	*ft_placeholder(void *content)
{
	return (content);
}
