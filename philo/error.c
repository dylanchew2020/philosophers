/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchew <lchew@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 11:01:56 by lchew             #+#    #+#             */
/*   Updated: 2023/04/04 21:35:40 by lchew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*  */
int	error_check(t_philo *philo, int argc)
{
	if (check_input(philo, argc) == 1)
	{
		write(2, "Error\n", 7);
		return (1);
	}
	if (check_fork(philo) == 1)
		return (1);
	return (0);
}

/*  */
int	check_input(t_philo *philo, int argc)
{
	if (philo->num_philo < 1 || philo->num_philo > 200)
		return (1);
	if (philo->time_to_die < 60)
		return (1);
	if (philo->time_to_eat < 60)
		return (1);
	if (philo->time_to_sleep < 60)
		return (1);
	if (argc == 6 && philo->num_must_eat < 0)
			return (1);
	return (0);
}

/*  */
int	check_fork(t_philo *philo)
{
	if (philo->num_philo < 2)
	{
		write_message(philo, philo->id + 1, "died");
		return (1);
	}
	return(0);
}
	