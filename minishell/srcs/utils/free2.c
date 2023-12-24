/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerdogan <aerdogan@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 01:02:36 by aerdogan          #+#    #+#             */
/*   Updated: 2023/12/23 01:02:37 by aerdogan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <stdlib.h>
#include "../42lib/libft/libft.h"

void	freestructs_nodata(t_scmd_list *temp)
{
	t_cmd	*tempcmd;

	tempcmd = temp->data;
	if (temp->type == CMD)
		free(tempcmd->arg);
	free(temp->data);
	temp->data = NULL;
}

void	freescmdlst_nodata(t_scmd_list **lst)
{
	t_scmd_list	*temp;
	t_scmd_list	*next;

	temp = *lst;
	while (temp)
	{
		next = temp->next;
		if (temp->data)
			freestructs_nodata(temp);
		free(temp);
		temp = next;
	}
	*lst = NULL;
}

void	freelst_nodata(t_list *lst)
{
	t_list	*temp;
	t_list	*next;

	if (!lst)
		return ;
	temp = lst;
	while (temp)
	{
		next = temp->next;
		freescmdlst_nodata((void *)&temp->content);
		free(temp);
		temp = next;
	}
	lst = NULL;
}
