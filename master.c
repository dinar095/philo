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

void my_usleep(unsigned int time)
{
	long long count;

	count = get_time() + (long long)time;
	while (get_time() < count)
		usleep(100);
}

void	on_off_fork(unsigned int frk1, unsigned int frk2, t_philo *ph, int lock)
{
	if (lock == 1)
	{
		pthread_mutex_lock(&ph->table->forks[frk1]);
		philo_state(ph, "has taken a fork\n", 0);
		pthread_mutex_lock(&ph->table->forks[frk2]);
		philo_state(ph, "has taken a fork\n", 0);
	}
	else if (lock == 0)
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
		my_usleep(100);
		fork1 = philo->right;
		fork2 = philo->left;
	}
	else
	{
		fork1 = philo->left;
		fork2 = philo->right;
	}

	while (philo->table->stop == 0)
	{
		on_off_fork(fork1, fork2, philo, ON);
		philo->die = get_time() + philo->table->die;
		philo_state(philo, "is eating\n", philo->table->eat);
		philo->meals_eated++;
		on_off_fork(fork1, fork2, philo, OFF);
		my_usleep(philo->table->sleep);
		philo_state(philo, "is sleeping\n", philo->table->sleep);
		philo_state(philo, "is thinking\n", 0);
	}
	return (EXIT_SUCCESS);
}
void unlock_all(t_table *table, int flag)
{
	int i;

	i = -1;
	while (++i < table->philos && flag)
	{
		pthread_mutex_unlock(&table->forks[i]);
	}
}
void *supervisor(void *arg)//TODO:
{
	t_table		*table;
	t_philo		*philo;
	long long	curr;
	int 		i;

	table = (t_table *)arg;
	while (!table->stop)
	{
		i = -1;
		table->full = 0;
		while (++i < table->philos)
		{
			philo = &(table->philosophers[i]);
			if (get_time() > philo->die)
			{
				table->stop = 1;
				pthread_mutex_lock(&table->print);
				f_printf(get_time() - table->start, philo->id, "is died\n");
				break ;
			}
			if (philo->meals_eated >= table->must_eat) {
				table->full++;
			}
			if (table->full == table->philos && !table->stop)
			{
				table->stop = 1;
				pthread_mutex_lock(&table->print);
				f_printf(get_time() - table->start, philo->id, "all philos is eat\n");
				break ;
			}
		}
	}
	unlock_all(table, 1);
	return (EXIT_SUCCESS);
}

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
	if (pthread_create(&table->killer, NULL, supervisor, (void *)table))
		return (EXIT_FAILURE);
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
	pthread_join(table->killer, NULL);
	return (EXIT_SUCCESS);
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
