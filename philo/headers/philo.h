/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: desausag <desausag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/12 10:40:24 by desausag          #+#    #+#             */
/*   Updated: 2021/08/12 11:13:33 by desausag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>
# define ON 1
# define OFF 0

struct				s_table;

typedef struct s_philo
{
	long long		die;
	unsigned int	id;
	unsigned int	left;
	unsigned int	right;
	unsigned int	meals_eated;
	pthread_t		thread;
	struct s_table	*table;
}					t_philo;

typedef struct s_table
{
	int	philos;
	unsigned int	die;
	unsigned int	eat;
	unsigned int	sleep;
	int				must_eat;
	int				stop;
	int				full;
	pthread_t		killer;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print;
	t_philo			*philosophers;
	long long		start;
}					t_table;

unsigned int		ft_atoi(const char *str);
void				ft_putstr_fd(char *s, int fd);
long long			get_time(void);
void				philo_state(t_philo *ph, char *str, unsigned int time);
void				ft_putnbr_fd(long long int n, int fd);
void				ft_putchar_fd(char c, int fd);
void				my_usleep(unsigned int time);
int					is_num(char **argv);
int					ft_isdigit(int ch);
int					str_error(char *str, int ret);
void				clear_all(t_table *table);
int					stop_simulation(t_table *table);
int					simulation(t_table *table);
int					run_simulation(t_table *table);
void				*supervisor(void *arg);
int					print_stop(t_philo *philo, char *str);
int					ft_strncmp(const char *s1, const char *s2, size_t c);
void				unlock_all(t_table *table);
void				*carefree_life(void *arg);
void				on_off_fork(unsigned int frk1, unsigned int frk2,
						t_philo *ph, int lock);
int					init_philosophers(t_table *table);
int					init_table(char **argv, t_table *table);
int					parse_args(char **argv, t_table *table);
int					check_table(t_table *table);
void				f_printf(long long time, unsigned int philo, char *str);
#endif
