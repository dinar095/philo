#include "headers/philo.h"

void str_error(char *str)
{
	ft_putstr_fd(str, 1);
}
int	is_num(char **argv)
{
	int i;
	int j;

	i = 0;

	while (*argv)
	{
		j = -1;
		while (argv[i][++j])
			if (!(ft_isdigit(argv[i][j])))
				return (0);
		argv++;
	}
	return (1);
}
int	parse_args(int argc, char **argv)
{
	int i;

	i = 0;

	if (!(is_num(argv)))
		return (0);
	while (i++ < argc)
		printf("%s\n", argv[i]);
	return (0);
}
int main(int argc, char **argv)
{
	if (argc < 5 || argc > 6)
		str_error("Error arguments\n");
	if (!(parse_args(argc, argv)))
		str_error("Error arguments\n");
	return 0;
}
