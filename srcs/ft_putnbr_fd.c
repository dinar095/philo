#include "../headers/philo.h"

void	ft_putchar_fd(char c, int fd)
{
	if (fd != -1)
		write(fd, &c, sizeof(char));
}

void	ft_putnbr_fd(long long int n, int fd)
{
	int i;

	i = n % 10 < 0 ? -1 : 1;
	if (fd == -1)
		return ;
	if (n / 10)
		ft_putnbr_fd(n / 10, fd);
	else if (n < 0)
		ft_putchar_fd('-', fd);
	ft_putchar_fd((n % 10) * i + '0', fd);
}
