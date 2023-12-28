/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerdogan <aerdogan@student.42kocaeli.com.  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 14:24:16 by aerdogan          #+#    #+#             */
/*   Updated: 2023/07/06 14:33:46 by aerdogan         ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*new2;

	new2 = (t_list *)malloc(sizeof(t_list));
	if (!new2)
		return (NULL);
	if (new2)
	{
		new2 -> content = content;
		new2 -> next = NULL;
	}
	return (new2);
}
