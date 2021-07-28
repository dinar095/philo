#include "headers/philo.h"

void str_error(char *str, int err)
{
	ft_putstr_fd(str, 1);
	exit(err);
}
int	parse_args(char **argv, int argc)
{
	int i;

	i = 0;

	while (i++ < argc)
		printf("%s\n", argv[i]);
	return (0);
}
int main(int argc, char **argv)
{
	if (argc < 5 || argc > 6)
		str_error("Error arguments\n", 1);
	if (parse_args(argv, argc))
		str_error("Error arguments\n", 1);
	return 0;
}
