/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: desausag <desausag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/12 10:35:10 by desausag          #+#    #+#             */
/*   Updated: 2021/08/12 10:35:10 by desausag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/philo.h"

int	parse(int argc, char **argv, t_table *table)
{
	(void)argc;
	if (init_table(argv, table))
		return (EXIT_FAILURE);
	if (init_philosophers(table))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	run_simulation(t_table *table)
{
	int	i;

	i = -1;
	table->start = get_time();
	while (++i < table->philos)
	{
		if (pthread_create(&table->philosophers[i].thread, NULL,
				carefree_life, (void *)(&table->philosophers[i])))
			return (EXIT_FAILURE);
	}
	if (pthread_create(&table->killer, NULL, supervisor, (void *)table))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	stop_simulation(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->philos)
	{
		if (pthread_join(table->philosophers[i].thread, NULL))
			return (EXIT_FAILURE);
	}
	if (pthread_join(table->killer, NULL))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	simulation(t_table *table)
{
	if (run_simulation(table))
		return (EXIT_FAILURE);
	if (stop_simulation(table))
		return (EXIT_FAILURE);
	clear_all(table);
	return (EXIT_SUCCESS);
}

int	main(int argc, char **argv)
{
	t_table	table;

	if (argc < 5 || argc > 6)
		return (str_error("Error arguments\n", 1));
	if (parse(argc, argv, &table))
		return (str_error("Error arguments\n", 1));
	if (simulation(&table))
		return (str_error("Simulation error\n", 1));
	return (0);
}
