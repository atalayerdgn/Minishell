/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerdogan <aerdogan@student.42kocaeli.com.  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 17:06:39 by aerdogan          #+#    #+#             */
/*   Updated: 2023/07/04 17:54:48 by aerdogan         ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	char	*buffer;
	size_t	i;

	i = 0;
	buffer = (char *)s;
	while (i < n)
	{
		if (*buffer == (char)c)
			return (buffer);
		buffer++;
		i++;
	}
	return (NULL);
}
