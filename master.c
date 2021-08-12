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
			if (philo->meals_eated >= table->must_eat)
				table->full++;
			if (table->full == table->philos && !table->stop
				&& print_stop(philo, "\tall philos is eat\n"))
				break ;
		}
	}
	unlock_all(table);
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

void	clear_all(t_table *table)
{
	free(table->forks);
	free(table->philosophers);
}

int	simulation(t_table *table)
{
	if (run_simulation(table))
		return (EXIT_FAILURE);
	if (stop_simulation(table))
		return (EXIT_FAILURE);
	if (pthread_mutex_unlock(&table->print))
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
