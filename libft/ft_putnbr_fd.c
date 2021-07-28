/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: desausag <desausag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/14 19:31:09 by desausag          #+#    #+#             */
/*   Updated: 2020/11/14 20:21:42 by desausag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	int i;

	i = n % 10 < 0 ? -1 : 1;
	if (fd == -1)
		return ;
	if (n / 10)
		ft_putnbr_fd(n / 10, fd);
	else if (n < 0)
		ft_putchar_fd('-', fd);
	ft_putchar_fd((n % 10) * i + '0', fd);
}
