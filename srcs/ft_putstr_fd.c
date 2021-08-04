#include "../headers/philo.h"

void	ft_putchar_fd(char c, int fd)
{
	if (fd != -1)
		write(fd, &c, sizeof(char));
}

void	ft_putstr_fd(char *s, int fd)
{
	if (!s || fd == -1)
		return ;
	while (*s)
		ft_putchar_fd(*s++, fd);
}
