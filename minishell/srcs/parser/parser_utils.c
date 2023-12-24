/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerdogan <aerdogan@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 13:01:41 by aerdogan          #+#    #+#             */
/*   Updated: 2023/12/22 21:01:42 by aerdogan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <stdlib.h>
#include "../42lib/libft/libft.h"
#include <stdbool.h>

static size_t	replace_data(t_token *token, size_t i, size_t j, bool in_single)
{
	char	*new_data;
	char	*temp;
	bool	in_double;

	temp = token->data;
	new_data = ft_calloc(ft_strlen(temp) + 1, sizeof(char));
	in_double = false;
	if (!new_data)
		return (EXIT_FAILURE);
	while (temp[j] != '\0')
	{
		if (temp[j] == '\\' && ft_strchr("<>|\'\"\\", temp[j + 1]) != NULL)
			new_data[i++] = temp[j + 1];
		else if (temp[j] == '\'' && in_double == false)
			in_single = !in_single;
		else if (temp[j] == '\"' && in_single == false)
			in_double = !in_double;
		else if ((ft_strchr("<>|\'\"\\", temp[j]) != NULL && (in_double == true \
			|| in_single == true)) || ft_strchr("<>|\'\"\\", temp[j]) == NULL)
			new_data[i++] = temp[j];
		j++;
	}
	temp = token->data;
	token->data = new_data;
	return (free(temp), EXIT_SUCCESS);
}

size_t	remove_quotes(t_list *tokens)
{
	t_token	*token;
	size_t	i;

	while (tokens)
	{
		token = tokens->content;
		i = 0;
		if (token->data != NULL)
		{
			if (ft_strnstr(token->data, "<<", 3) != NULL)
				tokens = tokens->next;
			else if (ft_strchr(token->data, '\'') != NULL \
			|| ft_strchr(token->data, '\"') != NULL \
			|| ft_strchr(token->data, '\\') != NULL)
			{
				if (replace_data(token, 0, 0, false) == EXIT_FAILURE)
					return (EXIT_FAILURE);
			}
		}
		if (tokens)
			tokens = tokens->next;
	}
	return (EXIT_SUCCESS);
}

size_t	count_cmdtokens(t_list **tokens)
{
	t_list	*current;
	t_token	*token;
	size_t	count;

	current = *tokens;
	token = current->content;
	count = 0;
	while (token->type != PIPE_TOKEN && current != NULL)
	{
		if (token->type == CMD_TOKEN)
			count++;
		else if (token->type == RDR_TOKEN)
			current = current->next;
		if (current != NULL)
			current = current->next;
		if (current != NULL)
			token = current->content;
	}
	return (count);
}

bool	is_builtin(t_list **tokens)
{
	t_list	*current;
	t_token	*token;
	char	*str;

	current = *tokens;
	token = current->content;
	str = token->data;
	if ((ft_strncmp(str, "echo", 5) == 0) || (ft_strncmp(str, "cd", 3) == 0) \
	|| (ft_strncmp(str, "pwd", 4) == 0) || (ft_strncmp(str, "export", 7) == 0) \
	|| (ft_strncmp(str, "unset", 6) == 0) || (ft_strncmp(str, "env", 4) == 0) \
	|| (ft_strncmp(str, "exit", 5) == 0))
		return (true);
	return (false);
}

t_list	*make_scmdlist(t_list *tokens, t_scmd_list **scmds, t_init *process)
{
	process->arg_count = 0;
	if (tokens != NULL && ((t_token *)(tokens->content))->type == PIPE_TOKEN)
	{
		ft_putendl_fd("minishell: syntax error near unexpected token", \
		STDERR_FILENO);
		return (NULL);
	}
	while (tokens != NULL && ((t_token *)(tokens->content))->type != PIPE_TOKEN)
	{
		tokens = scmdlist2(tokens, scmds, process);
		if (!tokens && process->must_exit == true)
			return (NULL);
	}
	return (tokens);
}
