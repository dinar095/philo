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
	unsigned int i;

	i = -1;
	table->philos = ft_atoi(argv[1]);
	//check for - and 0
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
	if (i--)
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
	if (all->table->stop) {
		return ;
	}
//	if(all->philo->id == 1)
//	{
//		ft_putstr_fd("   \n", 1);
//		ft_putnbr_fd(all->philo->left, 1);
//		ft_putstr_fd("   HHHHHHHHHHHHHHHHHH\n", 1);
//	}
	pthread_mutex_lock(&all->table->forks[all->philo->left]);
//	if(all->philo->id == 1)
//		printf("\n/////////////////\n");
	if (all->table->stop)
		return ;
	print_proc(all, "has taken a fork\n", 0);
	if (all->table->stop)
		return ;
	pthread_mutex_lock(&all->table->forks[all->philo->right]);
	if (all->table->stop)
		return ;
	print_proc(all, "has taken a fork\n", 0);
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
		usleep(100);
}
void *eat(void *alls)
{
	t_table *table;
	t_philo	*philo;
	t_all	*all;

	all = (t_all *)alls;
	table = all->table;
	philo = all->philo;
	if (philo->id % 2) {
		usleep(80);
	}

	while (!table->stop)
	{
		lock_fork(all);
//		if (philo->id == 1)
//			printf("left %d rigth : %d\n", philo->left, philo->right);
		philo->die = get_time() + table->die;//update philo die time
		print_proc(all, "is eating\n", table->eat);
		unlock_fork(table, philo);
		print_proc(all, "is sleeping\n", table->sleep);
		print_proc(all, "is thinking\n", 0);
		philo->must_eat++;
	}
}

void	f_printf(long long int time, unsigned int philo, char *str)
{
	ft_putnbr_fd(time, 1);
	ft_putstr_fd("\t", 1);
	ft_putnbr_fd(philo, 1);
	ft_putstr_fd(" ", 1);
	ft_putstr_fd(str, 1);
}

void print_proc(t_all *alls, char *str, unsigned int time)
{
	if (alls->table->stop)
		return ;
	alls->philo->cur_time = get_time() - alls->table->start;
//	if(alls->philo->id == 1)
//		write(1, "111111111111\n", 14);
	pthread_mutex_lock(&alls->table->print);
//	if(alls->philo->id == 1)
//		write(1, "2222222222222\n", 14);
	if (alls->table->stop)
		return ;
	f_printf(alls->philo->cur_time, alls->philo->id, str);
//	if(alls->philo->id == 1)
//		write(1, "3333333333333\n", 14);
	pthread_mutex_unlock(&alls->table->print);
	if (time)
		my_usleep(time);
}

void *check_philos(void *alls)
{
	t_table *table;
	t_philo	*philo;
	t_all	*all;
	unsigned int i;
	long long curr;

	all = (t_all *)alls;
	table = all[0].table;
	while (!table->stop)
	{
		i = -1;
		table->full = 0;
		curr = get_time();
		while (++i < table->philos)
		{
			philo = all[i].philo;
			philo->cur_time = curr - table->start;
			if (curr >= philo->die)
			{
				table->stop = 1;
				pthread_mutex_lock(&table->print);
				f_printf(philo->cur_time, philo->id, "is died\n");
				unlock_fork(table, philo);
				break ;
			}
			if (philo->must_eat >= table->et_conunt) {
				table->full++;
			}
			if (table->full == table->philos && !table->stop)
			{
				table->stop = 1;
				pthread_mutex_lock(&table->print);
				f_printf(philo->cur_time, philo->id, "all philos is eat\n");
				unlock_fork(table, philo);
				break ;
			}
		}
	}
	i =-1;
	my_usleep(500);
	while (++i < table->philos)
	{
		pthread_mutex_unlock(&table->forks[i]);
//		printf("%d\n", all[i].philo->id);
//		my_usleep(1000);
//		ft_putnbr_fd(i, 1);
//		printf("%d\n", i);
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
	i = -1;
	while (++i < table.philos)
	{
		if ((pthread_mutex_init(&table.forks[i], NULL)))
			printf("No\n");

	}
	pthread_create(&killer, NULL, check_philos, all);
	i = -1;
	while (++i < table.philos)
		pthread_join(threads[i], NULL);
	pthread_join(killer, NULL);
	return 0;
}
