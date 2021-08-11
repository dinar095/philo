#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>
# define STOP 1
# define ON 1
# define OFF 0


struct s_table;

typedef struct		s_philo
{

	long long 		die;
	unsigned int 	id;
	unsigned int	left;
	unsigned int	right;
	unsigned int	meals_eated;
	pthread_t 		thread;
	struct s_table	*table;
}					t_philo;

typedef struct		s_table
{
	unsigned int	philos;
	unsigned int 	die;
	unsigned int	eat;
	unsigned int	sleep;
	int 	must_eat;
	int 			stop;
	int 			full;
	pthread_t 		killer;
	pthread_mutex_t	*forks;
	pthread_mutex_t print;
	t_philo			*philosophers;
	long long 		start;

}					t_table;

typedef struct	s_all
{
	t_philo *philo;
	t_table *table;
}				t_all;

unsigned int		ft_atoi(const char *str);
int					ft_isdigit(int ch);
void				ft_putstr_fd(char *s, int fd);
long long 			get_time(void);
void				philo_state(t_philo *ph, char *str, unsigned int time);
void				ft_putnbr_fd(long long int n, int fd);
void				ft_putchar_fd(char c, int fd);
void				my_usleep(unsigned int time);
int					is_num(char **argv);
int					ft_isdigit(int ch);
int 				str_error(char *str, int ret);
int					init_philosophers(t_table *table);
int 				init_table(char **argv, t_table *table);

void *carefree_life(void *table);
void *supervisor(void *table);
int stop_simulation();
void clear_all(t_table *table);
#endif
