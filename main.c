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
	table->philos = ft_atoi(argv[1]);
	table->die = ft_atoi(argv[2]);
	table->eat = ft_atoi(argv[3]);
	table->sleep = ft_atoi(argv[4]);
	if (argv[4])
		table->et_conunt = ft_atoi(argv[5]);
	else
		table->et_conunt = -1;
	table->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * table->philos);
}

int	parse(int argc, char **argv, t_table *table)
{
	int i;

	i = 0;

	if (!(is_num(argv)))
		return (0);
	while (i++ < argc)
		printf("%s\n", argv[i]);
	init_table(table, argv);
	return (1);
}
void init_philos(t_table *table, t_philo *philo)
{
	int i;
	int j;

	i = -1;
	j = 1;
	philo = (t_philo *)malloc(sizeof(t_philo) * table->philos);
	while (++i < table->philos)
	{
		philo[i].id = j++;
//		philo[i]//TODO

	}
}

int main(int argc, char **argv)
{
	t_table table;
	t_philo *philo;

	if (argc < 5 || argc > 6)
		str_error("Error arguments\n"); //add return
	if (!(parse(argc, argv, &table)))
		str_error("Error arguments\n"); //add return
	init_philos(&table, philo);
	return 0;
}
