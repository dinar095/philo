/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   breadcrumbs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: desausag <desausag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/12 10:49:21 by desausag          #+#    #+#             */
/*   Updated: 2021/08/12 10:54:57 by desausag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

void	ft_putstr_fd(char *s, int fd)
{
	if (!s || fd == -1)
		return ;
	while (*s)
		ft_putchar_fd(*s++, fd);
}

unsigned int	ft_atoi(const char *str)
{
	int				i;
	int				minus;
	unsigned int	num;

	i = 0;
	minus = 1;
	num = 0;
	while (str[i] == '\t' || str[i] == '\n' || str[i] == '\v'
		|| str[i] == '\f' || str[i] == ' ' || str[i] == '\r')
		i++;
	if (str[i] == '-')
		minus = -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
		num = (num * 10) + str[i++] - '0';
	return (num * minus);
}

void	ft_putchar_fd(char c, int fd)
{
	if (fd != -1)
		write(fd, &c, sizeof(char));
}

void	ft_putnbr_fd(long long int n, int fd)
{
	int	i;

	i = 1;
	if (n % 10 < 0)
		i = -1;
	if (fd == -1)
		return ;
	if (n / 10)
		ft_putnbr_fd(n / 10, fd);
	else if (n < 0)
		ft_putchar_fd('-', fd);
	ft_putchar_fd((n % 10) * i + '0', fd);
}
