/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outils1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samoreno <samoreno@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 17:29:38 by samoreno          #+#    #+#             */
/*   Updated: 2022/08/05 12:39:46 by samoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_is_exact(const char *src, const char *search, size_t n, int comm)
{
	size_t	iter;

	iter = 0;
	if (comm == 1)
	{
		if (ft_strlen(src) > n)
			n = ft_strlen(src);
	}
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

static int	count_checker(char *red, int *quoted)
{
	int		i[2];
	char	q;

	i[0] = 0;
	i[1] = 0;
	while (red[i[0]])
	{
		if (red[i[0]] && (red[i[0]] == '"' || red[i[0]] == '\''))
		{
			*quoted += 1;
			q = red[i[0]++];
			while (red[i[0]] && red[i[0]++] != q)
				i[1]++;
		}
		if (red[i[0]] && red[i[0]] != '"' && red[i[0]] != '\'')
		{
			while (red[i[0]] && red[i[0]] != '"' && red[i[0]] != '\'')
			{
				i[1]++;
				i[0]++;
			}
		}
	}
	return (i[1]);
}

static void	fill_checker(char *red, char *ret)
{
	int		i[2];
	char	q;

	i[0] = 0;
	i[1] = 0;
	while (red[i[0]])
	{
		if (red[i[0]] && (red[i[0]] == '"' || red[i[0]] == '\''))
		{
			q = red[i[0]++];
			while (red[i[0]] && red[i[0]] != q)
				ret[i[1]++] = red[i[0]++];
			i[0]++;
		}
		if (red[i[0]] && red[i[0]] != '"' && red[i[0]] != '\'')
		{
			while (red[i[0]] && red[i[0]] != '"' && red[i[0]] != '\'')
				ret[i[1]++] = red[i[0]++];
		}
	}
	ret[i[1]] = 0;
}

char	*checkered(char *red, int *quoted, t_list *env, t_element *element)
{
	char	*ret;

	ret = malloc(sizeof(char) * (count_checker(red, quoted) + 1));
	if (!ret)
		cleanexit(env, element);
	fill_checker(red, ret);
	return (ret);
}

int	is_equal_unset(char *str)
{
	int	i;

	i = 0;
	while (str[i] && ft_strchr(&str[i], '=') != 0)
	{
		while (str[i] && str[i] != '=')
			i++;
		if (str[i] == '=')
			i++;
	}
	if (i == 0 && ft_strchr(&str[i], '=') == 0 && str[i] != '=')
		return (ft_strlen(str));
	return (i);
}
