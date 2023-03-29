/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_thread.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchew <lchew@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 10:52:31 by lchew             #+#    #+#             */
/*   Updated: 2023/03/29 22:34:23 by lchew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	create_philo(t_philo *philo)
{
	pthread_t	*thread;
	int			i;

	i = 0;
	thread = ft_calloc(philo->num_philo, sizeof(pthread_t));
	while (i < philo->num_philo)
	{
		philo->id = i;
		pthread_create(&thread[i++], NULL, &philo_routine, philo);
		usleep(5);
	}
	i = 0;
	while (i < philo->num_philo)
		pthread_join(thread[i++], NULL);
}

void	*philo_routine(void *arg)
{
	t_philo			*philo;
	int				id;

	philo = (t_philo *)arg;
	id = philo->id;
	write_message(philo, id + 1, "check");
	while (1)
	{
		if (philo_eat(philo, id) == 0)
			return (NULL);
		write_message(philo, id + 1, "is sleeping");
		usleep(philo->time_to_sleep * 1000);
		write_message(philo, id + 1, "is thinking");
		if (philo->num_must_eat[id] == 0)
			return (NULL);
	}
	return (NULL);
}

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
	if (philo_is_dead(philo, id) == 0)
	{
		write_message(philo, id + 1, "has taken a fork");
		write_message(philo, id + 1, "has taken a fork");
		write_message(philo, id + 1, "is eating");
		usleep(philo->time_to_eat * 1000);
		if (philo_is_dead(philo, id) == 0)
		{
			philo->last_eat[id] = ft_gettime();
			--philo->num_must_eat[id];
			i = 1;
		}
	}
	pthread_mutex_unlock(&philo->fork[left]);
	pthread_mutex_unlock(&philo->fork[right]);
	return (i);
}

int	philo_is_dead(t_philo *philo, int id)
{
	int	i;

	pthread_mutex_lock(&philo->time);
	if (ft_gettime() - philo->last_eat[id] > philo->time_to_die)
		philo->is_dead[id] = 1;
	i = 0;
	while (i < philo->num_philo)
	{
		if (philo->is_dead[i] == 1)
		{
			if (i == id)
				write_message(philo, i + 1, "died");
			pthread_mutex_unlock(&philo->time);
			return (1);
		}
		++i;
	}
	pthread_mutex_unlock(&philo->time);
	return (0);
}

void	write_message(t_philo *philo, int id, char *message)
{
	char	*time;
	char	*philo_id;
	char	*tmp;

	pthread_mutex_lock(&philo->message);
	time = ft_itoa(ft_gettime() - philo->last_eat[id - 1]);
	philo_id = ft_itoa(id);
	tmp = ft_itoa(philo->num_must_eat[id - 1]);
	write(1, time, ft_strlen(time));
	write(1, "ms ", 3);
	write(1, philo_id, ft_strlen(philo_id));
	write(1, " ", 1);
	write(1, message, ft_strlen(message));
	write(1, "\n", 1);
	pthread_mutex_unlock(&philo->message);
}
