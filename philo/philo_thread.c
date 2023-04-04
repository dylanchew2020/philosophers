/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_thread.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchew <lchew@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 10:52:31 by lchew             #+#    #+#             */
/*   Updated: 2023/04/04 21:35:52 by lchew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*  */
int	create_philo(t_philo *philo)
{
	pthread_t	*thread;
	int			i;

	i = 0;
	thread = ft_calloc(philo->num_philo, sizeof(pthread_t));
	while (i < philo->num_philo)
	{
		philo->id = i;
		if (pthread_create(&thread[i++], NULL, &philo_routine, philo))
			return (1);
		usleep(10);
	}
	philo_is_dead(philo);
	i = 0;
	while (i < philo->num_philo)
		pthread_join(thread[i++], NULL);
	return (0);
}

/*  */
void	*philo_routine(void *arg)
{
	t_philo			*philo;
	int				id;

	philo = (t_philo *)arg;
	id = philo->id;
	while (philo->is_dead == -1 && philo->num_must_eat_array[id] != 0)
	{
		if (philo_eat(philo, id) == 0)
			break ;
		write_message(philo, id + 1, "is sleeping");
		if (timer(philo, philo->time_to_sleep) == 0)
			break ;
		write_message(philo, id + 1, "is thinking");
	}
	return (NULL);
}

/* 
	
	return 1 if philo is alive and successfully eaten.
	return 0 if philo is dead.
 */
int	philo_eat(t_philo *philo, int id)
{
	int	i;
	int	left;
	int	right;

	i = 0;
	left = id;
	right = (id + 1) % philo->num_philo;
	pthread_mutex_lock(&philo->fork[left]);
	pthread_mutex_lock(&philo->fork[right]);
	if (philo->is_dead == -1)
	{
		write_message(philo, id + 1, "has taken a fork");
		write_message(philo, id + 1, "has taken a fork");
		pthread_mutex_lock(&philo->time);
		write_message(philo, id + 1, "is eating");
		philo->last_eat[id] = ft_gettime();
		pthread_mutex_unlock(&philo->time);
		i = timer(philo, philo->time_to_eat);
		--philo->num_must_eat_array[id];
	}
	pthread_mutex_unlock(&philo->fork[left]);
	pthread_mutex_unlock(&philo->fork[right]);
	return (i);
}

/*  */
void	philo_is_dead(t_philo *philo)
{
	int	id;

	while (philo->num_full_philo != philo->num_philo)
	{
		id = 0;
		philo->num_full_philo = 0;
		while (id < philo->num_philo)
		{
			pthread_mutex_lock(&philo->time);
			if (ft_gettime() - philo->last_eat[id] > philo->time_to_die)
			{
				philo->is_dead = id;
				write_message(philo, id + 1, "died");
			}
			pthread_mutex_unlock(&philo->time);
			if (philo->is_dead != -1)
				return ;
			if (philo->num_must_eat_array[id] == 0)
				++philo->num_full_philo;
			++id;
		}
	}
}

/*  */
int	timer(t_philo *philo, int time)
{
	long long	init_time;

	init_time = ft_gettime();
	while (philo->is_dead == -1)
	{
		if (ft_gettime() - init_time >= time)
			return (1);
		usleep(100);
	}
	return (0);
}
