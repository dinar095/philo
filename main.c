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
void parse_table(t_philo *, char **argv)
int	parse(int argc, char **argv, t_table *table, t_philo *philo)
{
	int i;

	i = 0;

	if (!(is_num(argv)))
		return (0);
	while (i++ < argc)
		printf("%s\n", argv[i]);
	table->philos = ft_atoi(argv[1]);
	table->die = ft_atoi(argv[2]);
	table->eat = ft_atoi(argv[3]);
	table->eat = ft_atoi(argv[3]);




	return (1);
}
int main(int argc, char **argv)
{
	t_table table;
	t_philo philo;

	if (argc < 5 || argc > 6)
		str_error("Error arguments\n");
	if (!(parse(argc, argv, &table, &philo)))
		str_error("Error arguments\n");
	return 0;
}
