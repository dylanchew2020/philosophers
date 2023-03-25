/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchew <lchew@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 14:22:47 by lchew             #+#    #+#             */
/*   Updated: 2023/03/25 23:38:10 by lchew            ###   ########.fr       */
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
	printf("%i\n", philo.num_must_eat);
	create_philo(&philo);
	return (0);
}

void	init_philo(t_philo *philo, int argc, char *argv[])
{
	struct timeval	tv;

	philo->num_philo = ft_atoi(argv[1]);
	philo->time_to_die = ft_atoi(argv[2]);
	philo->time_to_eat = ft_atoi(argv[3]);
	philo->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		philo->num_must_eat = ft_atoi(argv[5]);
	else
		philo->num_must_eat = -1;
	philo->id = 0;
	philo->is_dead = ft_calloc(philo->num_philo, sizeof(int));
	philo->is_full = ft_calloc(philo->num_philo, sizeof(int));
	philo->fork = ft_calloc(philo->num_philo, sizeof(int));
	gettimeofday(&tv, NULL);
	philo->start_time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	philo->last_eat = ft_calloc(philo->num_philo, sizeof(int));
	philo->print = ft_calloc(philo->num_philo, sizeof(pthread_mutex_t));
}

void	create_philo(t_philo *philo)
{
	pthread_t	*thread;
	int			i;

	i = 0;
	thread = ft_calloc(philo->num_philo, sizeof(pthread_t));
	while (i < philo->num_philo)
		pthread_mutex_init(&philo->print[i++], NULL);
	i = 0;
	while (i < philo->num_philo)
	{
		philo->id = i;
		pthread_create(&thread[i++], NULL, &philo_routine, philo);
		usleep(5);
	}
	i = 0;
	while (i < philo->num_philo)
		pthread_join(thread[i++], NULL);
	i = 0;
	while (i < philo->num_philo)
		pthread_mutex_destroy(&philo->print[i++]);
}

void	*philo_routine(void *arg)
{
	t_philo			*philo;
	int				i;

	philo = (t_philo *)arg;
	i = philo->id;
	while (1)
	{
		if (get_timestamp_ms(philo->start_time) - philo->last_eat[i] > philo->time_to_die)
			philo->is_dead[i] = 1;
		if (check_philo_status(philo) == 1)
		{
			printf("Philosopher %i is dead\n", i + 1);
			return (NULL);
		}
		pthread_mutex_lock(&philo->print[i]);
		printf("%llims %i is thinking\n", get_timestamp_ms(philo->start_time), i + 1);
		pthread_mutex_unlock(&philo->print[i]);
		if (philo->fork[i] == 0 && philo->fork[(i + 1) % philo->num_philo] == 0)
		{
			pthread_mutex_lock(&philo->print[i]);
			philo->fork[i] = 1;
			printf("%llims %i has taken a fork\n", get_timestamp_ms(philo->start_time), i + 1);
			philo->fork[(i + 1) % philo->num_philo] = 1;
			printf("%llims %i has taken a fork\n", get_timestamp_ms(philo->start_time), i + 1);
			printf("%llims %i is eating\n", get_timestamp_ms(philo->start_time), i + 1);
			pthread_mutex_unlock(&philo->print[i]);
			usleep(philo->time_to_eat * 1000);
		}
		pthread_mutex_lock(&philo->print[i]);
		philo->fork[i] = 0;
		philo->fork[(i + 1) % philo->num_philo] = 0;
		philo->last_eat[i] = get_timestamp_ms(philo->start_time);
		printf("%llims %i is sleeping\n", get_timestamp_ms(philo->start_time), i + 1);
		pthread_mutex_unlock(&philo->print[i]);
		usleep(philo->time_to_sleep * 1000);
	}
	return (NULL);
}

int	check_philo_status(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->num_philo)
	{
		if (philo->is_dead[i] == 1)
			return (1);
		i++;
	}
	return (0);
}

long long	get_timestamp_ms(long long start_time)
{
	struct timeval	tv;
	long long		timestamp_ms;

	gettimeofday(&tv, NULL);
	timestamp_ms = (tv.tv_sec * 1000) + (tv.tv_usec / 1000) - start_time;
	timestamp_ms = timestamp_ms - timestamp_ms % 10;
	return (timestamp_ms);
}