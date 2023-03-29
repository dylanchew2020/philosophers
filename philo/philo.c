/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchew <lchew@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 14:22:47 by lchew             #+#    #+#             */
/*   Updated: 2023/03/29 11:28:55 by lchew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* 
	Takes in 5 arguments:
	1. Number of philosophers
	2. Time to die
	3. Time to eat
	4. Time to sleep
	5. Number of times each philosopher must eat (optional)
 */
int	main(int argc, char *argv[])
{	
	t_philo	philo;

	if (argc < 5 || argc > 6)
		return (0);
	init_philo(&philo, argc, argv);
	if (error_check(&philo) == 1)
		return (0);
	create_philo(&philo);
	return (0);
}

void	init_philo(t_philo *philo, int argc, char *argv[])
{
	philo->num_philo = ft_atoi(argv[1]);
	philo->time_to_die = ft_atoi(argv[2]);
	philo->time_to_eat = ft_atoi(argv[3]);
	philo->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		philo->num_must_eat = ft_calloc(philo->num_philo, sizeof(int));
	else
		philo->num_must_eat = NULL;
	philo->id = 0;
	philo->is_dead = ft_calloc(philo->num_philo, sizeof(int));
	philo->is_full = ft_calloc(philo->num_philo, sizeof(int));
	philo->last_eat = ft_calloc(philo->num_philo, sizeof(int));
	init_last_eat(philo);
	philo->fork = ft_calloc(philo->num_philo, sizeof(pthread_mutex_t));
	init_mutex(philo);
}

void	init_mutex(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->num_philo)
		pthread_mutex_init(&philo->fork[i++], NULL);
	pthread_mutex_init(&philo->message, NULL);
	pthread_mutex_init(&philo->time, NULL);
}

void	init_eat(t_philo *philo, int num_must_eat)
{
	int				i;
	struct timeval	tv;

	i = 0;
	while (i < philo->num_philo)
	{
		philo->num_must_eat[i] = num_must_eat;
		gettimeofday(&tv, NULL);
		philo->last_eat[i++] = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	}
}

void	philo_free(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->num_philo)
		pthread_mutex_destroy(&philo->fork[i++]);
	pthread_mutex_destroy(&philo->message);
	pthread_mutex_destroy(&philo->time);
	free(philo->is_dead);
	free(philo->is_full);
	free(philo->fork);
	free(philo->last_eat);
}