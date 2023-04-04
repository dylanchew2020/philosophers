/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchew <lchew@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 15:25:56 by lchew             #+#    #+#             */
/*   Updated: 2023/04/04 21:34:09 by lchew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	countlen(int n)
{
	unsigned int	len;

	len = 1;
	if (n < 0)
	{
		if (n == INT_MIN)
			++n;
		++len;
		n *= -1;
	}
	while (n > 9)
	{
		++len;
		n /= 10;
	}
	return (len);
}

static char	*putnbr(char *result, int nbr)
{
	if (nbr < 0)
	{
		*result = '-';
		result++;
		if (nbr == INT_MIN)
		{
			*result++ = '2';
			nbr += 2000000000;
		}
		nbr *= -1;
	}
	while (nbr > 9)
	{
		result = putnbr(result, (nbr / 10));
		*result++ = (nbr % 10) + '0';
		nbr = -1;
	}
	if (nbr < 10 && nbr >= 0)
		*result++ = nbr + '0';
	return (result);
}

/*
**	Allocates (with malloc(3)) and converts the integer received as an argument
**	into a string. Negative numbers must be handled.
**	
**	The ft_itoa() returns a string of the integer. 
**	Returns NULL if the allocation fails.
*/
char	*ft_itoa(int nbr)
{
	char	*result;
	char	*r;

	result = ft_calloc((countlen(nbr) + 1), sizeof(char));
	if (!result)
		return (NULL);
	r = result;
	result = putnbr(result, nbr);
	*result = '\0';
	return (r);
}

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
