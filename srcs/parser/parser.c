/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: desausag <desausag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/11 13:56:24 by desausag          #+#    #+#             */
/*   Updated: 2021/08/11 13:56:24 by desausag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/philo.h"

int check_table(t_table *table)
{
	if (table->philos < 1 || table->die < 60 || table->sleep < 0)
		return (EXIT_FAILURE);
	if (table->philos > 200 || table->must_eat < -2 || table->eat < 0)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int parse_args(char **argv, t_table *table)
{
	if (!(is_num(argv)))
		return (EXIT_FAILURE);
	table->philos = ft_atoi(argv[1]);
	table->die = ft_atoi(argv[2]);
	table->eat = ft_atoi(argv[3]);
	table->sleep = ft_atoi(argv[4]);
	if (argv[5])
		table->must_eat = (int)ft_atoi(argv[5]);
	else
		table->must_eat = -1;
	return (EXIT_SUCCESS);
}

int init_table(char **argv, t_table *table)
{
	int i;

	i = -1;
	if (parse_args(argv, table))
		return (EXIT_FAILURE);
	table->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * table->philos);
	if (!(table->forks))
		return (EXIT_FAILURE);
	while (++i < table->philos)
	{
		if (pthread_mutex_init(&table->forks[i], NULL))
			return (EXIT_FAILURE);
	}
	if (pthread_mutex_init(&table->print, NULL))
		return (EXIT_FAILURE);
	table->stop = 0;
	table->full = 0;
	table->start = get_time();
	if (check_table(table))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int init_philosophers(t_table *table)
{
	int i;
	t_philo *phil;

	i = -1;
	phil = (t_philo *) malloc(sizeof(t_philo) * table->philos);
	if (!(phil))
		return (EXIT_FAILURE);
	while (++i < table->philos)
	{
		phil[i].id = i + 1;
		phil[i].right = i;
		phil[i].left = i + 1;
		phil[i].meals_eated = 0;
		phil[i].die = get_time() + table->die;
		phil[i].table = table;
	}
	phil[table->philos - 1].left = 0;
	table->philosophers = phil;
	return (EXIT_SUCCESS);
}
