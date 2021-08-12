/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   supervisor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: desausag <desausag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/12 10:33:03 by desausag          #+#    #+#             */
/*   Updated: 2021/08/12 11:20:06 by desausag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

void	unlock_all(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->philos)
	{
		my_usleep(2);
		pthread_mutex_unlock(&table->forks[i]);
		pthread_mutex_unlock(&table->print);
	}
}

int	print_stop(t_philo *philo, char *str)
{
	unsigned int	n;

	n = philo->id;
	if (!ft_strncmp(str, "\tall philos is eat\n", 20))
		n = 0;
	pthread_mutex_lock(&philo->table->print);
	philo->table->stop = 1;
	f_printf(get_time() - philo->table->start, n, str);
	pthread_mutex_unlock(&philo->table->print);
	return (1);
}

int	ft_strncmp(const char *s1, const char *s2, size_t c)
{
	size_t	i;
	int		r;

	i = 0;
	while ((s1[i] == s2[i]) && (i < c) && (s1[i] != '\0') && (s2[i] != '\0'))
		i++;
	if (i == c)
		return (0);
	r = (unsigned char)s1[i] - (unsigned char)s2[i];
	return (r);
}

void	*supervisor(void *arg)
{
	t_table	*table;
	t_philo	*philo;
	int		i;

	table = (t_table *)arg;
	while (!table->stop)
	{
		i = -1;
		table->full = 0;
		while (++i < table->philos)
		{
			philo = &(table->philosophers[i]);
			if (get_time() > philo->die && print_stop(philo, "is died\n"))
				break ;
			if ((int)philo->meals_eated >= table->must_eat
				&& table->must_eat != -1)
				table->full++;
			if (table->full == table->philos && !table->stop
				&& print_stop(philo, "\tall philos is eat\n"))
				break ;
		}
	}
	unlock_all(table);
	return (EXIT_SUCCESS);
}
