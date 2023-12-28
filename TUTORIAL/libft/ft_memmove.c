/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerdogan <aerdogan@student.42kocaeli.com.  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 14:33:36 by aerdogan          #+#    #+#             */
/*   Updated: 2023/07/05 02:29:33 by aerdogan         ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t	i;
	char	*dest;
	char	*sr;

	i = len;
	dest = (char *)dst;
	sr = (char *)src;
	if (dst == src)
		return (dst);
	if (dest > sr)
	{
		while (i > 0)
		{
			i--;
			dest[i] = sr[i];
		}
	}
	else
		ft_memcpy(dst, src, len);
	return (dest);
}
