/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerdogan <aerdogan@student.42kocaeli.com.  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 03:02:58 by aerdogan          #+#    #+#             */
/*   Updated: 2023/07/12 03:03:00 by aerdogan         ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_numlen(int num)
{
	int	i;

	if (num == 0)
		return (1);
	i = 0;
	while (num > 0 || num < 0)
	{
		num /= 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	int		len;
	char	*set;
	long	nbr;

	nbr = n;
	len = ft_numlen(nbr);
	if (n < 0)
	{
		len++;
		nbr = -nbr;
	}
	set = malloc(sizeof(char) * len + 1);
	if (!set)
		return (NULL);
	set[len] = '\0';
	while (nbr > 0)
	{
		set[--len] = nbr % 10 + 48;
		nbr /= 10;
	}
	if (n < 0)
		set[0] = '-';
	if (n == 0)
		set[0] = '0';
	return (set);
}
