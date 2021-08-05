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
	int i;

	i = 0;

	if (!(is_num(argv)))
		return (0);
//	while (i++ < argc-1)
//		printf("%s\n", argv[i]);
	init_table(table, argv);
	return (1);
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
//	i = -1;
//	while(++i < table->philos)
//	{
//		printf("===========");
//		printf("philo id: %d\n", philo[i].id);
//		printf("philo left	f: %d\n", philo[i].left);
//		printf("philo rigth	f: %d\n", philo[i].right);
//		printf("===========");
//	}

}

void *eat(void *alls)
{
	t_table *table;
	t_philo	*philo;
	t_all	*all;

	all = (t_all *)alls;
	table = all->table;
	philo = all->philo;
	printf("philo %d started\n", philo->id);
	pthread_mutex_lock(&table->forks[philo->left]);
	usleep(500000);
	pthread_mutex_lock(&table->forks[philo->right]);
	printf("philo %d is eat\n", philo->id);
	printf("left h: %d\nright h: %d\n", philo->left, philo->right);
	pthread_mutex_unlock(&table->forks[philo->left]);
	pthread_mutex_unlock(&table->forks[philo->right]);
	printf("philo %d is stop\n", philo->id);

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
	while (++i < table.philos)
		pthread_create(&threads[i], NULL, eat, &all[i]);
	while (--i)
		pthread_join(threads[i], NULL);
	return 0;
}
