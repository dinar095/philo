#include <pthread.h>#include <stdio.h>#include <stdlib.h>#include <unistd.h>#include "libft/libft.h"#define wait() scanf("1")#define PHT_SIZE 5typedef struct	philosopher_tag{	const char *name;	unsigned left_fork;	unsigned right_fork;}				philosopher_t;typedef struct	table_tag{	pthread_mutex_t forks[PHT_SIZE];}				table_t;typedef struct	philosopher_args_tag{	const philosopher_t *philosopher;	const table_t *table;}			philosopher_args_t;void	init_philosopher(philosopher_t *philosopher, const char *name, unsigned left_fork, unsigned right_fork){	philosopher->name = name;	philosopher->left_fork = left_fork;	philosopher->right_fork = right_fork;}void	init_table(table_t *table){	size_t	i;	i = - 1;	while (++i < PHT_SIZE)		pthread_mutex_init(&table->forks[i], NULL);}void	*eat(void *args){	philosopher_args_t	*arg;	const				philosopher_t *philosopher;	const				table_t *table;	unsigned rand;	pthread_mutex_t entry_point = PTHREAD_MUTEX_INITIALIZER;	arg = (philosopher_args_t *)args;	table = arg->table;	philosopher = arg->philosopher;	printf("%s started dinner\n", philosopher->name);	pthread_mutex_lock(&entry_point);	pthread_mutex_lock(&table->forks[philosopher->left_fork]);	rand_s(&rand);	sleep(rand);	pthread_mutex_lock(&table->forks[philosopher->right_fork]);	printf("%s is eating\n", philosopher->name);	pthread_mutex_unlock(&table->forks[philosopher->right_fork]);	pthread_mutex_unlock(&table->forks[philosopher->left_fork]);	pthread_mutex_unlock(&entry_point);	printf("%s finished dinner\n", philosopher->name);}void main(){	pthread_t			threads[PHT_SIZE];	philosopher_t		philosophers[PHT_SIZE];	philosopher_args_t	arguments[PHT_SIZE];	table_t 			table;	size_t				i;	i = -1;	init_table(&table);	init_philosopher(&philosophers[0], "Alice", 0,1);	init_philosopher(&philosophers[1], "Bob", 1,2);	init_philosopher(&philosophers[2], "Clark", 2,3);	init_philosopher(&philosophers[3], "Denis", 3,4);	init_philosopher(&philosophers[4], "Eugin", 4,0);	while (++i < PHT_SIZE)	{		arguments[i].philosopher = &philosophers[i];		arguments[i].table = &table;	}	i = -1;	ft_putstr_fd("i`m Here\n", 1);	while (++i < PHT_SIZE)		pthread_create(&threads[i], NULL, eat, &arguments[i]);	i = -1;	while (++i < PHT_SIZE)		pthread_join(threads[i], NULL);	wait();}