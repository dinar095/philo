#include "headers/philo.h"

void str_error(char *str)
{
	ft_putstr_fd(str, 1);
//	free
}

int	is_num(char **argv)
{
	int j;

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

void init_table(t_table *table, char **argv)
{
	int i;

	i = -1;
	table->philos = ft_atoi(argv[1]);
	table->die = ft_atoi(argv[2]);
	table->eat = ft_atoi(argv[3]);
	table->sleep = ft_atoi(argv[4]);
	if (argv[5])
		table->et_conunt = ft_atoi(argv[5]);
	else
		table->et_conunt = -1;
	table->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * table->philos);
	while (++i < table->philos)
		pthread_mutex_init(&table->forks[i], NULL);
	pthread_mutex_init(&table->print, NULL);
	table->stop = 0;
}

int	parse(int argc, char **argv, t_table *table)
{
	if (!(is_num(argv)))
		return (0);
	init_table(table, argv);
	return (1);
}

u_int64_t 	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((((long long) tv.tv_sec) * 1000) + (tv.tv_usec / 1000));
}

void init_philos(t_table *table, t_philo **philo, t_all **all)
{
	int i;
	int j;

	i = -1;
	j = 1;
	*philo = (t_philo *)malloc(sizeof(t_philo) * table->philos);
	while (++i < table->philos)
	{
		(*philo)[i].id = j++;
		(*philo)[i].right = i;
		(*philo)[i].left = i + 1;
		(*philo)[i].must_eat = 0;
		(*philo)[i].die = get_time() + table->die;

	}
	if (i-- > 1)
		(*philo)[i].left = 0;
	*all = (t_all *) malloc(sizeof(t_all) * table->philos);
	i = -1;
	while (++i < table->philos)
	{
		(*all)[i].philo = &(*philo)[i];
		(*all)[i].table = table;
	}
}

void	lock_fork(t_all *all)
{
	pthread_mutex_lock(&all->table->forks[all->philo->left]);
	print_proc(all, 0, 0);
	pthread_mutex_lock(&all->table->forks[all->philo->right]);
	print_proc(all, 0, 0);
}

void 	unlock_fork(t_table *table, t_philo *philo)
{
	pthread_mutex_unlock(&table->forks[philo->left]);
	pthread_mutex_unlock(&table->forks[philo->right]);
}
void my_usleep(unsigned int time)
{
	long long count;

	count = get_time() + (long long)time;
	while (get_time() < count)
		usleep(500);
}
void *eat(void *alls)
{
	t_table *table;
	t_philo	*philo;
	t_all	*all;
	long long count;

	all = (t_all *)alls;
	table = all->table;
	philo = all->philo;
	if(philo->id % 2)
		usleep(500);
//
	while (!table->stop)
	{
		lock_fork(all);
		philo->die = get_time() + table->die;//update philo die time
		print_proc(all, 1, table->eat);
		unlock_fork(table, philo);
		print_proc(all, 2, table->sleep);
		print_proc(all, 3, 0);
		philo->must_eat++;
	}
}

void print_proc(t_all *alls, int flag, unsigned int time)
{
	alls->philo->cur_time = get_time() - alls->table->start;
	if (!alls->table->stop)
	{
		pthread_mutex_lock(&alls->table->print);
		if (flag == 0)
			printf("%llu %d has taken a fork\n", alls->philo->cur_time, alls->philo->id);
		if (flag == 1)
			printf("%llu %d is eating\n", alls->philo->cur_time, alls->philo->id);
		if (flag == 2)
			printf("%llu %d is sleeping\n", alls->philo->cur_time, alls->philo->id);
		pthread_mutex_unlock(&alls->table->print);
		if (time)
			my_usleep(time);
	}

}

void *check_philos(void *alls)
{
	t_table *table;
	t_philo	*philo;
	t_all	*all;
	unsigned i;

	all = (t_all *)alls;
	table = all[0].table;
	while (!table->stop)
	{
		i = -1;
		while (++i < table->philos)
		{
			philo = all[i].philo;
			if (get_time() > philo->die)
			{
				philo->cur_time = get_time() - table->start;
				pthread_mutex_lock(&table->print);
				printf("%llu %d is died\n", philo->cur_time, philo->id);
				table->stop = 1;
			}
			if (philo->must_eat == table->et_conunt)//TODO

		}
	}
}

int main(int argc, char **argv)
{
	t_table		table;
	t_philo		*philo;
	t_all		*all;
	pthread_t	*threads;
	pthread_t 	killer;
	int 	i;

	i = -1;
	if (argc < 5 || argc > 6)
		str_error("Error arguments\n"); //add return
	if (!(parse(argc, argv, &table)))
		str_error("Error arguments\n"); //add return
	init_philos(&table, &philo, &all);
	threads = (pthread_t *)malloc(sizeof(pthread_t) * table.philos);
	table.start = get_time();
	while (++i < table.philos)
		pthread_create(&threads[i], NULL, eat, &all[i]);
	while (++i < table.philos)
		pthread_mutex_init(&table.forks[i], NULL);
	pthread_create(&killer, NULL, check_philos, all);
	while (--i)
		pthread_join(threads[i], NULL);
	return 0;
}
