/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchew <lchew@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 11:01:56 by lchew             #+#    #+#             */
/*   Updated: 2023/04/06 15:13:59 by lchew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* 
	Checks for errors in the input arguments and forks.
	
	Arguments:
	- philo: a pointer to a t_philo struct
	- argc: the number of arguments passed in the command line
	
	Returns:
	- 0 if there were no errors
	- 1 if there was an error in the input arguments or forks
*/
int	error_check(t_philo *philo, int argc, char **argv)
{
	if (check_input(philo, argc, argv) == 1)
	{
		write(2, "Error\n", 7);
		return (1);
	}
	if (check_fork(philo) == 1)
		return (1);
	return (0);
}

/* 
	Checks the input values for validity.
	
	Arguments:
	- philo: a pointer to a t_philo struct
	- argc: an integer representing the number of command-line arguments
	
	Returns:
	- 1 if an input value is invalid
	- 0 otherwise
*/
int	check_input(t_philo *philo, int argc, char **argv)
{
	while (argc > 1)
	{
		if (ft_isdigit_str(argv[argc - 1]) == 0)
			return (1);
		--argc;
	}
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

/* 
	Check if there are enough fork, since there can only exist one fork per philo. 
	If not, end the simulation and mark the first philosopher as dead.
	
	Arguments:
	- philo: a pointer to a t_philo struct
	
	Returns:
	- 1 if there is only one philosopher
	- 0 otherwise
*/
int	check_fork(t_philo *philo)
{
	if (philo->num_philo < 2)
	{
		write_message(philo, philo->id + 1, "died");
		return (1);
	}
	return (0);
}

/* 
	Checks if a string contains only digits.
	
	Arguments:
	- str: a pointer to a string
	
	Returns:
	- 1 if the string contains only digits
	- 0 otherwise
*/
int	ft_isdigit_str(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] >= '0' && str[i] <= '9')
			++i;
		else
			return (0);
	}
	return (1);
}
