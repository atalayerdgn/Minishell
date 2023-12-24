/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerdogan <aerdogan@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 19:01:35 by aerdogan          #+#    #+#             */
/*   Updated: 2023/11/28 23:11:36 by abulut           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../42lib/libft/libft.h"
#include <stdlib.h>

static size_t	split_rdrtokens(t_list *tokens, size_t i)
{
	t_list	*next;
	t_token	*new;
	t_list	*new_node;

	while (tokens != NULL)
	{
		next = tokens->next;
		if (((t_token *)(tokens->content))-> type > CMD_TOKEN)
		{
			i = is_splitable((t_token *)(tokens->content));
			if (i < ft_strlen(((t_token *)(tokens->content))->data))
			{
				new = split_rdrtoken((t_token *)(tokens->content), i);
				if (!new)
					return (EXIT_FAILURE);
				new_node = ft_lstnew(new);
				if (!new_node)
					return (free(new->data), free(new), EXIT_FAILURE);
				tokens->next = new_node;
				new_node->next = next;
			}
		}
		tokens = tokens->next;
	}
	return (EXIT_SUCCESS);
}

static void	init_token(t_list *tokens)
{
	t_token	*token;

	token = NULL;
	while (tokens != NULL)
	{
		token = tokens->content;
		if (ft_strchr(token->data, '\"') == NULL && \
				ft_strchr(token->data, '\'') == NULL && \
				(ft_strchr(token->data, '|') != NULL))
			token->type = PIPE_TOKEN;
		else if (ft_strchr(token->data, '\"') == NULL && \
				ft_strchr(token->data, '\'') == NULL && \
				((ft_strchr(token->data, '>') != NULL) || \
				(ft_strchr(token->data, '<') != NULL)) && \
				(ft_strncmp(token->data, "\\<", 3) != 0))
			token->type = RDR_TOKEN;
		else
			token->type = CMD_TOKEN;
		tokens = tokens->next;
	}
}

static size_t	make_tlist(const char **ui_array, t_list **tokens)
{
	t_list	*node;
	t_token	*token;
	char	*str;

	while (ui_array[0] != NULL)
	{
		str = (char *)*ui_array;
		token = new_token(str);
		if (token == NULL)
			return (1);
		node = ft_lstnew(token);
		if (node == NULL)
			return (free(token), 1);
		ft_lstadd_back(tokens, node);
		ui_array++;
	}
	return (0);
}

t_list	*tokenisation(const char *user_input)
{
	t_list	*tokens;
	char	**ui_array;

	tokens = NULL;
	ui_array = lexer_split(user_input);
	if (!ui_array)
		return (NULL);
	if (make_tlist((const char **) ui_array, &tokens) == 1)
	{
		ft_free_str_array(ui_array, NULL);
		free_tokenlst(&tokens, true);
		return (NULL);
	}
	free(ui_array);
	init_token(tokens);
	if (split_rdrtokens(tokens, 0) == EXIT_FAILURE)
		return (free_tokenlst(&tokens, true), NULL);
	return (tokens);
}
