#include "../headers/philo.h"

int		ft_isdigit(int ch)
{
	int r;

	r = 1;
	if (!(ch >= 48 && ch <= 57))
		r = 0;
	return (r);
}
