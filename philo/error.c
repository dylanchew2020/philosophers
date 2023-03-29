/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchew <lchew@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 11:01:56 by lchew             #+#    #+#             */
/*   Updated: 2023/03/29 11:14:59 by lchew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	error_check(t_philo *philo)
{
	if (check_fork(philo) == 1)
		return (1);
	return (0);
}

int	check_fork(t_philo *philo)
{
	if (philo->num_philo < 2)
	{
		write_message(philo, philo->id + 1, "died");
		return (1);
	}
	return(0);
}
	