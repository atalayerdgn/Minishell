/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerdogan <aerdogan@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 21:32:11 by aerdogan          #+#    #+#             */
/*   Updated: 2023/12/23 11:12:32 by aerdogan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <stdlib.h>
#include "../42lib/libft/libft.h"
#include <stdbool.h>

void	ft_free_str_array(char **arr, char *str)
{
	size_t	i;

	i = 0;
	if (arr)
	{
		while (arr[i])
		{
			free(arr[i]);
			arr[i] = NULL;
			i++;
		}
		free(arr);
		arr = NULL;
	}
	if (str)
	{
		free(str);
		str = NULL;
	}
}

static void	ft_free_structs(t_scmd_list **smcd_list)
{
	t_rdr		*rdr;
	t_cmd		*cmd;
	t_scmd_list	*temp;

	temp = *smcd_list;
	if (temp->type == RDR)
	{
		rdr = temp->data;
		if (rdr->data)
		{
			free(rdr->data);
			rdr->data = NULL;
		}
		free(rdr);
		rdr = NULL;
	}
	else if (temp->type == CMD)
	{
		cmd = temp->data;
		ft_free_str_array(cmd->arg, cmd->path);
		free(cmd);
		cmd = NULL;
	}
}

void	freescmdlst(t_scmd_list **lst)
{
	t_scmd_list	*temp;
	t_scmd_list	*next;

	temp = *lst;
	while (temp)
	{
		next = temp->next;
		ft_free_structs(&temp);
		free(temp);
		temp = next;
	}
	*lst = NULL;
}

void	ft_freelst(t_list *lst)
{
	t_list	*temp;
	t_list	*next;

	if (!lst)
		return ;
	temp = lst;
	while (temp)
	{
		next = temp->next;
		freescmdlst((void *)&temp->content);
		free(temp);
		temp = next;
	}
	lst = NULL;
}

void	free_tokenlst(t_list **tokens, bool	free_data)
{
	t_list	*temp;
	t_list	*next;
	t_token	*token;

	if (!tokens)
		return ;
	temp = *tokens;
	while (temp)
	{
		next = temp->next;
		token = temp->content;
		if (token)
		{
			if (token->type != CMD_TOKEN && token->data)
				free(token->data);
			else if (free_data == true && token->data)
				free(token->data);
			free(token);
		}
		free(temp);
		temp = next;
	}
	tokens = NULL;
}
