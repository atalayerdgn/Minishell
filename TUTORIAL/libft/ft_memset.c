/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerdogan <aerdogan@student.42kocaeli.com.  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 19:28:24 by aerdogan          #+#    #+#             */
/*   Updated: 2023/07/06 14:16:05 by aerdogan         ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	char	*dest;
	size_t	i;

	i = 0;
	dest = b;
	while (i < len)
	{
		dest[i] = (char)c;
		i++;
	}
	return (b);
}
