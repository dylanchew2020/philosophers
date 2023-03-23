/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchew <lchew@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 14:22:47 by lchew             #+#    #+#             */
/*   Updated: 2023/03/23 14:32:06 by lchew            ###   ########.fr       */
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
	create_philo(ft_atoi(argv[1]));
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
	philo->is_dead = malloc(sizeof(int) * philo->num_philo);
	philo->is_full = malloc(sizeof(int) * philo->num_philo);
	philo->forks = malloc(sizeof(int) * philo->num_philo);
	philo->last_eat = malloc(sizeof(int) * philo->num_philo);
	philo->print = malloc(sizeof(pthread_mutex_t) * philo->num_philo);
}

void	create_philo(int num_philo)
{
	pthread_t	*philo;
	int			i;

	i = 0;
	philo = malloc(sizeof(pthread_t) * num_philo);
	while (i < num_philo)
	{
		pthread_create(&philo[i++], NULL, &philo_routine, (void *)&i);
		usleep(50);
		pthread_join(philo[i], NULL);
		// pthread_detach(philo[i]);
	}
}

void	*philo_routine(void *arg)
{
	int	my_integer;

	my_integer = *((int *)arg);
	while (1)
	{
		printf("Hello World! %i\n", my_integer);
		usleep(1000);
	}
	return (NULL);
}

