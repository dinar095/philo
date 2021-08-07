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
	if (argv[4])
		table->et_conunt = ft_atoi(argv[5]);
	else
		table->et_conunt = -1;
	table->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * table->philos);
	while (++i < table->philos)
		pthread_mutex_init(&table->forks[i], NULL);
}

int	parse(int argc, char **argv, t_table *table)
{
	if (!(is_num(argv)))
		return (0);
	init_table(table, argv);
	return (1);
}

uint64_t	get_time(void)
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
	pthread_mutex_lock(&all->table->forks[all->philo->right]);
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

	all = (t_all *)alls;
	table = all->table;
	philo = all->philo;
	if(philo->id % 2)
		usleep(5000);
//
	lock_fork(all);
	print_proc(all, 1, table->eat);
	unlock_fork(table, philo);
//	update die time
//	prinf sleep
//	usleep for sleep
	printf("philo %d is stop\n", philo->id);
}

void print_proc(t_all *alls, int flag, unsigned int time)
{
	alls->philo->cur_time = get_time() - alls->table->start;
//	mutex for print
	if (flag == 0)
		printf("%llu %d has taken a fork\n", alls->philo->cur_time, alls->philo->id);
	if (flag == 1)
		printf("%llu %d is eating\n", alls->philo->cur_time, alls->philo->id);
	if (time)
		my_usleep(time);
}

int main(int argc, char **argv)
{
	t_table		table;
	t_philo		*philo;
	t_all		*all;
	pthread_t	*threads;
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
	pthread_create()
	while (--i)
		pthread_join(threads[i], NULL);
	//destroy mutex----------
	while (++i < table.philos)
		pthread_mutex_init(&table.forks[i], NULL);
	//-----------------------
	return 0;
}
