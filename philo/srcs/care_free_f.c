/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   care_free_f.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: desausag <desausag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/12 10:27:26 by desausag          #+#    #+#             */
/*   Updated: 2021/08/12 10:27:26 by desausag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

void	on_off_fork(unsigned int frk1, unsigned int frk2, t_philo *ph, int lock)
{
	if (lock)
	{
		pthread_mutex_lock(&ph->table->forks[frk1]);
		philo_state(ph, "has taken a fork\n", 0);
		pthread_mutex_lock(&ph->table->forks[frk2]);
		philo_state(ph, "has taken a fork\n", 0);
	}
	else
	{
		pthread_mutex_unlock(&ph->table->forks[frk1]);
		pthread_mutex_unlock(&ph->table->forks[frk2]);
	}
}

void	f_printf(long long time, unsigned int philo, char *str)
{
	ft_putnbr_fd(time, 1);
	if (philo)
	{
		ft_putstr_fd("\t", 1);
		ft_putnbr_fd(philo, 1);
		ft_putstr_fd(" ", 1);
	}
	ft_putstr_fd(str, 1);
}

void	philo_state(t_philo *ph, char *str, unsigned int time)
{
	long long	curr;

	curr = get_time() - ph->table->start;
	if (ph->table->stop)
		return ;
	pthread_mutex_lock(&ph->table->print);
	if (ph->table->stop)
		return ;
	f_printf(curr, ph->id, str);
	pthread_mutex_unlock(&ph->table->print);
	if (time)
		my_usleep(time);
}

void	my_usleep(unsigned int time)
{
	long long	count;

	count = get_time() + (long long)time;
	while (get_time() < count)
		usleep(100);
}
