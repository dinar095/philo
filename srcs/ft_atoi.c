#include "../headers/philo.h"


unsigned int ft_atoi(const char *str) {
	int i;
	int minus;
	unsigned int num;

	i = 0;
	minus = 1;
	num = 0;
	while (str[i] == '\t' || str[i] == '\n' || str[i] == '\v'
		   || str[i] == '\f' || str[i] == ' ' || str[i] == '\r')
		i++;
	if (str[i] == '-')
		minus = -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
		num = (num * 10) + str[i++] - '0';
	return (num * minus);
}
