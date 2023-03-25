/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchew <lchew@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 16:22:28 by lchew             #+#    #+#             */
/*   Updated: 2023/03/25 22:01:33 by lchew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
	The ft_atoi() function converts the initial portion of the string pointed to 
	by str to int representation.
*/
long	ft_atoi(const char *str)
{
	long	res;
	int		sign;

	res = 0;
	sign = 1;
	while ((*str == ' ') || (*str >= 9 && *str <= 13))
		str++;
	if ((*str == '-') || (*str == '+'))
	{
		if (*str++ == '-')
			sign *= -1;
	}
	while (*str >= '0' && *str <= '9')
		res = (res * 10) + (*str++) - '0';
	return (res * sign);
}

/*
**	The ft_calloc() function allocates memory for an array of nmemb elements of
**	size bytes each and returns a pointer to the allocated  memory. The memory
**	is set to zero. If nmemb or size is 0, then calloc() returns NULL.
*/
void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*array;

	if ((nmemb > 65535 || size > 65535) && ((size_t)-1 / nmemb) < size)
		return (NULL);
	array = malloc(nmemb * size);
	if (!array)
		return (NULL);
	ft_bzero(array, (nmemb * size));
	return (array);
}

/*
**	The ft_bzero() function writes n zeroed bytes to the string s.  If n is zero, 
**	ft_bzero() does nothing.
*/

void	ft_bzero(void *s, size_t n)
{
	memset(s, 0, n);
}
