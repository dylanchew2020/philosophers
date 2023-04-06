/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchew <lchew@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 14:23:16 by lchew             #+#    #+#             */
/*   Updated: 2023/04/06 14:40:33 by lchew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>	// INT_MIN
# include <string.h>	// memset
# include <stdio.h>		// printf
# include <stdlib.h>	// malloc, free, (exit)
# include <unistd.h>	// write, usleep, (fork)
# include <sys/time.h>	// gettimeofday
# include <pthread.h>	// pthread_create, pthread_detach, pthread_join, 
						// pthread_mutex_init, pthread_mutex_destroy, 
						// pthread_mutex_lock, pthread_mutex_unlock

/* BONUS */
# include <signal.h>	// kill
# include <sys/wait.h>	// waitpid
# include <semaphore.h>	// sem_open, sem_close, sem_post, sem_wait, sem_unlink

typedef struct s_philo
{
	int				id;
	int				num_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_must_eat;
	int				*num_must_eat_array;
	int				is_dead;
	pthread_mutex_t	*fork;
	long long		start_time;
	long long		*last_eat;
	int				num_full_philo;
	pthread_mutex_t	message;
	pthread_mutex_t	time;
}				t_philo;

/* INITIALISE */
void		init_philo(t_philo *philo, int argc, char *argv[]);
void		init_mutex(t_philo *philo);
void		init_eat(t_philo *philo, int num_must_eat);

/* THREAD */
int			create_philo(t_philo *philo);
void		*philo_routine(void *arg);
int			philo_eat(t_philo *philo, int id);
void		philo_is_dead(t_philo *philo);
int			timer(t_philo *philo, int time);

/* ERROR */

int			error_check(t_philo *philo, int argc, char **argv);
int			check_input(t_philo *philo, int argc, char **argv);
int			check_fork(t_philo *philo);

/* UTILS */

void		write_message(t_philo *philo, int id, char *message);
long		ft_atoi(const char *str);
void		*ft_calloc(size_t nmemb, size_t size);
void		ft_bzero(void *s, size_t n);
size_t		ft_strlen(const char *s);
long long	ft_gettime(void);
char		*ft_itoa(int nbr);
int			ft_isdigit_str(char *str);

#endif