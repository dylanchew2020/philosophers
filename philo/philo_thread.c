/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_thread.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchew <lchew@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 10:52:31 by lchew             #+#    #+#             */
/*   Updated: 2023/04/18 17:36:40 by lchew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* 
**	Creates threads for each philosopher and waits for them to complete.
**	
**	Arguments:
**	- philo: a pointer to a t_philo struct
**	
**	Returns:
**	- 0 if all threads were created and joined successfully
**	- 1 if there was an error creating a thread
*/
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
	free(thread);
	return (0);
}

/*
**	Main routine for the philosopher threads. Continuously loops while 
**	the philosopher is not dead and has not reached the required number 
**	of meals. Calls the philo_eat function to allow the philosopher to eat, 
**	and waits for the specified amount of time using the timer function. 
**	Writes messages to indicate the philosopher's state.
**	
**	Arguments:
**	- arg: a void pointer that is cast to a t_philo pointer
**	
**	Returns:
**	- NULL
*/
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
**	Allows a philosopher to eat if they are not already dead. 
**	The philosopher must acquire two forks to eat, and will release them after
**	the specified time to eat has elapsed.
**
**	Arguments:
**	- philo: a pointer to a t_philo struct
**	- id: an integer representing the philosopher's ID
**
**	Returns:
**	- 1 if the philosopher successfully ate
**	- 0 if the philosopher died while attempting to eat
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

/*
** Checks if any philosopher has died due to starvation.
** 
** Iterates through each philo to check if the time from last ate is greater
** than the time to die. If so, the philo is marked as dead, and a message is 
** printed indicating that they have died. If the philo has reached the 
** required number of meals, they are counted as having eaten enough. 
** The function continues to iterate until all philos are full, then exit.
**
** Arguments:
** - philo: a pointer to a t_philo struct
**
** Returns: none
*/
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

/* 
**	Waits for a specified amount of time while checking if the is_dead flag 
**	in the t_philo struct is still set to -1.
**
**	Arguments:
**	- philo: a pointer to a t_philo struct
**	- time: an integer representing the amount of time to wait in ms
**
**	Returns:
**	- 1 if the timer has elapsed and the philo is still alive
**	- 0 if the philo is dead
*/
int	timer(t_philo *philo, int time)
{
	long long	init_time;

	init_time = ft_gettime();
	while (philo->is_dead == -1)
	{
		if (ft_gettime() - init_time >= time)
			return (1);
		usleep(50);
	}
	return (0);
}
