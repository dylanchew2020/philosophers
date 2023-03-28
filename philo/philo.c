/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchew <lchew@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 14:22:47 by lchew             #+#    #+#             */
/*   Updated: 2023/03/28 18:01:19 by lchew            ###   ########.fr       */
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
	philo->fork = ft_calloc(philo->num_philo, sizeof(pthread_mutex_t));
	philo->last_eat = ft_calloc(philo->num_philo, sizeof(int));
	init_last_eat(philo);
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

void	init_last_eat(t_philo *philo)
{
	int				i;
	struct timeval	tv;

	i = 0;
	while (i < philo->num_philo)
	{
		gettimeofday(&tv, NULL);
		philo->last_eat[i++] = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	}
}

void	create_philo(t_philo *philo)
{
	pthread_t	*thread;
	int			i;

	i = 0;
	thread = ft_calloc(philo->num_philo, sizeof(pthread_t));
	init_mutex(philo);
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
		pthread_mutex_destroy(&philo->fork[i++]);
	pthread_mutex_destroy(&philo->message);
	pthread_mutex_destroy(&philo->time);
}

void	*philo_routine(void *arg)
{
	t_philo			*philo;
	int				i;
	// pthread_mutex_t	*left_fork;
	// pthread_mutex_t	*right_fork;
	int				left;
	int				right;

	philo = (t_philo *)arg;
	i = philo->id;
	// *left_fork = philo->fork[i];
	// *right_fork = philo->fork[(i + 1) % philo->num_philo];
	left = i;
	right = (i + 1) % philo->num_philo;
	while (1)
	{
		pthread_mutex_lock(&philo->fork[left]);
		pthread_mutex_lock(&philo->fork[right]);
		// printf("Time since last eat: %lli", get_time(philo) - philo->last_eat[i]);
		if (get_time(philo) - philo->last_eat[i] > philo->time_to_die)
			philo->is_dead[i] = 1;
		if (check_philo_status(philo) == 1)
		{
			pthread_mutex_unlock(&philo->fork[left]);
			pthread_mutex_unlock(&philo->fork[right]);
			return (NULL);
		}
		write_message(philo, i + 1, "has taken a fork");
		write_message(philo, i + 1, "has taken a fork");
		write_message(philo, i + 1, "is eating");
		usleep(philo->time_to_eat * 1000);
		if (get_time(philo) - philo->last_eat[i] > philo->time_to_die)
			philo->is_dead[i] = 1;
		if (check_philo_status(philo) == 1)
		{
			pthread_mutex_unlock(&philo->fork[left]);
			pthread_mutex_unlock(&philo->fork[right]);
			return (NULL);
		}
		pthread_mutex_unlock(&philo->fork[left]);
		pthread_mutex_unlock(&philo->fork[right]);
		philo->last_eat[i] = get_time(philo);
		write_message(philo, i + 1, "is sleeping");
		usleep(philo->time_to_sleep * 1000);
		write_message(philo, i + 1, "is thinking");
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
		{
			write_message(philo, i + 1, "died");
			return (1);
		}
		i++;
	}
	return (0);
}

void	write_message(t_philo *philo, int id, char *message)
{
	char	*time;
	char	*philo_id;

	pthread_mutex_lock(&philo->message);
	time = ft_itoa(get_time(philo));
	philo_id = ft_itoa(id);
	write(1, time, ft_strlen(time));
	write(1, " ", 1);
	write(1, philo_id, ft_strlen(philo_id));
	write(1, " ", 1);
	write(1, message, ft_strlen(message));
	write(1, "\n", 1);
	pthread_mutex_unlock(&philo->message);
}

int	get_time(t_philo *philo)
{
	struct timeval	tv;
	long long		timestamp_ms;

	pthread_mutex_lock(&philo->time);
	gettimeofday(&tv, NULL);
	timestamp_ms = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	pthread_mutex_unlock(&philo->time);
	return (timestamp_ms);
}