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
	ft_putstr_fd("\t", 1);
	ft_putnbr_fd(philo, 1);
	ft_putstr_fd(" ", 1);
	ft_putstr_fd(str, 1);
}

void philo_state(t_philo *ph, char *str, unsigned int time)
{
	long long curr;
	curr = get_time() - ph->table->start;
	pthread_mutex_lock(&ph->table->print);
	if (ph->table->stop)
		return ;
	f_printf(curr, ph->id, str);
	pthread_mutex_unlock(&ph->table->print);
	if (time)
		my_usleep(time);
}

void my_usleep(unsigned int time)
{
	long long count;

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

void *carefree_life(void *arg)
{
	t_philo *philo;
	unsigned int		fork1;
	unsigned int		fork2;

	philo = (t_philo *)arg;
	if (philo->id % 2)
	{
		fork1 = philo->right;
		fork2 = philo->left;
	}
	else
	{
		fork1 = philo->left;
		fork2 = philo->right;
	}

	while (!(philo->table->stop))
	{
		on_off_fork(fork1, fork2, philo, ON);
		philo->die = get_time() + philo->table->die;
		philo_state(philo, "is eating\n", philo->table->eat);
		on_off_fork(fork1, fork2, philo, OFF);
		philo_state(philo, "is sleeping\n", philo->table->sleep);
		philo_state(philo, "is thinking\n", 0);
		philo->meals_eated++;
	}
	printf("%d was exit\n", philo->id);
	return (EXIT_SUCCESS);

}

void *supervisor(void *table);

int	run_simulation(t_table *table)
{
	int i;

	i = -1;
	table->start = get_time();
	while (++i < table->philos)
	{
		if (pthread_create(&table->philosophers[i].thread, NULL, carefree_life, (void *)(&table->philosophers[i])))
			return (EXIT_FAILURE);
	}
//	if (pthread_create(&table->killer, NULL, supervisor, (void *)table))
//		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int stop_simulation(t_table *table)
{
	int i;

	i = -1;
	while (++i < table->philos)
	{
		if (pthread_join(table->philosophers[i].thread, NULL))
			return (EXIT_FAILURE);
	}
}
//void clear_all(t_table *table);
int simulation(t_table *table)
{
	if (run_simulation(table))
		return (EXIT_FAILURE);
	if (stop_simulation(table))
		return (EXIT_FAILURE);
	if (pthread_mutex_unlock(&table->print))
		return (EXIT_FAILURE);
//	clear_all(table);
	return (EXIT_SUCCESS);
}


int main(int argc, char **argv)
{
	t_table table;


	if (argc < 5 || argc > 6)
		return(str_error("Error arguments\n", 1));
	if (parse(argc, argv, &table))
		return (str_error("Error arguments\n", 1));
	if	(simulation(&table))
		return (str_error("Simulation error\n", 1));
	return (0);
}
