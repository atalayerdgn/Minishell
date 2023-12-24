/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerdogan <aerdogan@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 21:02:40 by aerdogan          #+#    #+#             */
/*   Updated: 2023/11/05 01:32:41 by aerdogan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <stdlib.h>

t_scmd_list	*ft_lstnewscmd(void *data, t_struct_type type, t_init *process)
{
	t_scmd_list	*newnode;
	t_cmd		*cmd;

	cmd = data;
	newnode = malloc(sizeof(t_scmd_list));
	if (!newnode)
	{
		process->must_exit = true;
		if (type == CMD)
			free(cmd->arg);
		free(data);
		return (NULL);
	}
	newnode->data = data;
	newnode->type = type;
	newnode->next = NULL;
	return (newnode);
}

void	scmdlst_add_back(t_scmd_list **scmds, t_scmd_list *new)
{
	t_scmd_list	*temp;

	if (!new)
		return ;
	if (!*scmds)
	{
		*scmds = new;
		return ;
	}
	temp = *scmds;
	while (temp != NULL && temp -> next != NULL)
		temp = temp -> next;
	temp -> next = new;
}
