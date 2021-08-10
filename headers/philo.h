#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>



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
	u_int64_t 		eat;
	u_int64_t 		die;
	u_int64_t 		cur_time;
	unsigned int 	id;
	unsigned int	left;
	unsigned int	right;
	unsigned int	must_eat;
}					t_philo;

typedef struct		s_table
{
	pthread_mutex_t	*forks;
	unsigned int	philos;
	unsigned int 	die;
	unsigned int	eat;
	unsigned int	sleep;
	unsigned int 	et_conunt;
	int 			stop;
	int 			full;
	pthread_mutex_t print;
	u_int64_t 		start;

}					t_table;

typedef struct	s_all
{
	t_philo *philo;
	t_table *table;
}				t_all;

unsigned int		ft_atoi(const char *str);
int					ft_isdigit(int ch);
void				ft_putstr_fd(char *s, int fd);
u_int64_t 			get_time(void);
void				print_proc(t_all *alls, char *str, unsigned int time);
void				ft_putnbr_fd(long long int n, int fd);
void				ft_putchar_fd(char c, int fd);
#endif
