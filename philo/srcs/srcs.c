/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   srcs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: desausag <desausag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/12 10:52:53 by desausag          #+#    #+#             */
/*   Updated: 2021/08/12 10:53:12 by desausag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

int	ft_isdigit(int ch)
{
	int	r;

	r = 1;
	if (!(ch >= 48 && ch <= 57))
		r = 0;
	return (r);
}

int	is_num(char **argv)
{
	int	j;

	argv++;
	while (*(++argv))
	{
		j = -1;
		while ((*argv)[++j])
			if (!(ft_isdigit((*argv)[j])))
				return (0);
	}
	return (1);
}

long long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((((long long) tv.tv_sec) * 1000) + (tv.tv_usec / 1000));
}

int	str_error(char *str, int ret)
{
	ft_putstr_fd(str, 1);
	return (ret);
}

void	clear_all(t_table *table)
{
	free(table->forks);
	free(table->philosophers);
}
