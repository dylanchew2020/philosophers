/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchew <lchew@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 14:23:16 by lchew             #+#    #+#             */
/*   Updated: 2023/03/23 14:23:54 by lchew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

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
	int				*is_dead;
	int				*is_full;
	int				*forks;
	int				*last_eat;
	pthread_mutex_t	*print;
}				t_philo;

void	init_philo(t_philo *philo, int argc, char *argv[]);
void	create_philo(int num_philo);
void	*philo_routine(void *arg);
long	ft_atoi(const char *str);

#endif