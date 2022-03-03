/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samoreno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 11:15:21 by samoreno          #+#    #+#             */
/*   Updated: 2021/11/15 11:15:23 by samoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_count_dig(int n);
static void		ft_fill_itoa(int n, char *str);
static size_t	ft_add_zeroes(int n);

char	*ft_itoa(int n)
{
	char	*itoaed;
	size_t	num_len;

	num_len = ft_count_dig(n);
	itoaed = malloc(sizeof(char) * (num_len + 1));
	if (!itoaed)
		return (NULL);
	ft_fill_itoa(n, itoaed);
	return (itoaed);
}

static size_t	ft_count_dig(int n)
{
	size_t	count;

	count = 0;
	if (n == -2147483648)
	{
		count += 2;
		n = 147483648;
	}
	if (n < 0)
		count++;
	if (!n)
		count++;
	else
	{
		while (n)
		{
			count++;
			n /= 10;
		}
	}
	return (count);
}

static void	ft_fill_itoa(int n, char *str)
{
	int		i;
	size_t	zeroes;

	i = 0;
	zeroes = ft_add_zeroes(n);
	if (n < 0)
	{
		str[i++] = '-';
		if (n == -2147483648)
		{
			str[i++] = '2';
			n = 147483648;
		}
		else
			n *= -1;
	}
	while (zeroes)
	{
		str[i++] = (n / zeroes) + '0';
		n %= zeroes;
		zeroes /= 10;
	}
	str[i] = 0;
}

static size_t	ft_add_zeroes(int n)
{
	size_t	divisor;

	divisor = 1;
	if (n < 0)
	{
		if (n == -2147483648)
			n = 147483648;
		else
			n *= -1;
	}
	while (n / 10 != 0)
	{
		divisor *= 10;
		n /= 10;
	}
	return (divisor);
}
