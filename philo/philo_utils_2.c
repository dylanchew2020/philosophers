/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchew <lchew@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 15:25:56 by lchew             #+#    #+#             */
/*   Updated: 2023/03/26 15:28:45 by lchew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
**	Allocates (with malloc(3)) and converts the integer received as an argument
**	into a string. Negative numbers must be handled.
**	
**	The ft_itoa() returns a string of the integer. 
**	Returns NULL if the allocation fails.
*/
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