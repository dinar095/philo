/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: desausag <desausag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/14 14:32:23 by desausag          #+#    #+#             */
/*   Updated: 2020/11/19 14:06:19 by desausag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		arr_size(int n)
{
	int q;

	q = 0;
	if (n == 0)
		return (1);
	if (n < 0)
		q++;
	while (n)
	{
		n /= 10;
		q++;
	}
	return (q);
}

char	*ft_itoa(int n)
{
	int		i;
	char	*z;
	int		minus;

	i = arr_size(n);
	minus = 1;
	z = (char *)malloc(sizeof(char) * i + 1);
	z[i--] = '\0';
	z[0] = '0';
	if (n < 0)
	{
		z[0] = '-';
		minus = -1;
	}
	while (n)
	{
		z[i] = (n % 10) * minus + '0';
		n = n / 10;
		i--;
	}
	return (z);
}
