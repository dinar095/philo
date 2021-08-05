#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <stdlib.h>
typedef struct	s_start
{
	int num_of_philo;
	int	time_to_die;
	int time_to_eat;
	int time_to_sleep;
	int must_eat;
	int num_of_finish_of_filo;
	int finish;
	
}				t_start;

typedef struct		s_philo
{
	unsigned int 	id;
	unsigned int	left;
	unsigned int	right;
}					t_philo;

typedef struct		s_table
{
	pthread_mutex_t	*forks;
	unsigned int	philos;
	unsigned int 	die;
	unsigned int	eat;
	unsigned int	sleep;
	unsigned int 	et_conunt;

}					t_table;

typedef struct	s_all
{
	t_philo *philo;
	t_table *table;
}				t_all;

unsigned int		ft_atoi(const char *str);
int					ft_isdigit(int ch);
void				ft_putstr_fd(char *s, int fd);
#endif
