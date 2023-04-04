/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchew <lchew@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 16:22:28 by lchew             #+#    #+#             */
/*   Updated: 2023/04/04 21:36:33 by lchew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	write_message(t_philo *philo, int id, char *message)
{
	pthread_mutex_lock(&philo->message);
	printf("%lli %i %s\n", ft_gettime() - philo->start_time, id, message);
	pthread_mutex_unlock(&philo->message);
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

/*
**	The ft_strlen() function computes the length of the string s.
**
**	The ft_strlen() function returns the number of characters that precede the 
**	terminating NUL character.
*/
size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
		++i;
	return (i);
}

long long	ft_gettime(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}
