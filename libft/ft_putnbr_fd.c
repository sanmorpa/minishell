/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samoreno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 13:32:56 by samoreno          #+#    #+#             */
/*   Updated: 2021/11/11 13:32:58 by samoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	write_number(int fd, int div, int number);

void	ft_putnbr_fd(int n, int fd)
{
	int		neg;
	int		divisor;
	int		nb_c;

	neg = 0;
	divisor = 1;
	if (n == -2147483648)
	{
		write(fd, "-2", 2);
		n = 147483648;
	}
	nb_c = n;
	if (n < 0)
	{
		n *= -1;
		neg = 1;
	}
	while (nb_c / 10 != 0)
	{
		divisor *= 10;
		nb_c /= 10;
	}
	if (neg == 1)
		write(fd, "-", 1);
	write_number(fd, divisor, n);
}

static void	write_number(int fd, int div, int number)
{
	char	to_write;

	while (div != 0)
	{
		to_write = (number / div) + '0';
		write(fd, &to_write, 1);
		number = number % div;
		div /= 10;
	}
}
