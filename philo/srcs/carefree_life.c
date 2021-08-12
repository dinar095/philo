/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   carefree_life.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: desausag <desausag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/12 10:52:20 by desausag          #+#    #+#             */
/*   Updated: 2021/08/12 10:52:20 by desausag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

void	*carefree_life(void *arg)
{
	t_philo			*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2)
		my_usleep(50);
	while (!philo->table->stop)
	{
		on_off_fork(philo->right, philo->left, philo, ON);
		philo->die = get_time() + philo->table->die;
		philo_state(philo, "is eating\n", philo->table->eat);
		on_off_fork(philo->right, philo->left, philo, OFF);
		philo_state(philo, "is sleeping\n", philo->table->sleep);
		philo_state(philo, "is thinking\n", 0);
		philo->meals_eated++;
	}
	return (EXIT_SUCCESS);
}
