/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerdogan <aerdogan@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 04:40:26 by aerdogan          #+#    #+#             */
/*   Updated: 2023/12/23 11:41:27 by abulut           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <stdlib.h>
#include "../42lib/libft/libft.h"
#include <stdbool.h>

static char	*expanded_part(char *str, t_env *env, t_init *process)
{
	char	**env_array;
	char	*res;
	size_t	i;
	size_t	len;

	env_array = env->new_env;
	res = NULL;
	i = 0;
	if (str[0] == '?')
		return (free(str), ft_itoa(process->errorcode));
	while (env_array[i] != NULL)
	{
		len = ft_strlen(str);
		if (ft_strncmp(env_array[i], str, len) == 0 && env_array[i][len] == '=')
		{
			len = len + 1;
			res = ft_substr(env_array[i], len, ft_strlen(env_array[i]) - len);
			return (free(str), res);
		}
		i++;
	}
	return (free(str), ft_strjoin("", ""));
}

char	*expand_data(char *str, t_env *env, bool in_heredoc, t_init *process)
{
	char	*new_data;
	char	*temp;
	char	*beginning;
	char	*middle;
	char	*end;

	beginning = find_begin(str, in_heredoc);
	if (!beginning)
		return (NULL);
	end = find_end(str, beginning);
	if (!end)
		return (free(beginning), NULL);
	middle = find_middle(str, 0, 1);
	if (!middle)
		return (free(beginning), free(end), NULL);
	middle = expanded_part(middle, env, process);
	if (!middle)
		return (free(beginning), free(end), NULL);
	temp = ft_strjoin(beginning, middle);
	if (!temp)
		return (multi_free(beginning, middle, end, NULL), NULL);
	new_data = ft_strjoin(temp, end);
	if (!new_data)
		return (multi_free(beginning, middle, end, temp), NULL);
	return (multi_free(beginning, middle, end, temp), new_data);
}

static size_t	replace_token(t_token *token, t_env *env, t_init *process)
{
	char	*new_data;
	char	*temp;

	if (ft_strncmp(token->data, "~", 2) == 0)
		new_data = expand_data("$HOME", env, false, process);
	else if (ft_strncmp(token->data, "~/", 2) == 0)
	{
		temp = expand_data("$HOME", env, false, process);
		if (!temp)
			return (EXIT_FAILURE);
		new_data = ft_strjoin(temp, token->data + 1);
		free(temp);
	}
	else
		new_data = expand_data(token->data, env, false, process);
	if (!new_data)
		return (EXIT_FAILURE);
	temp = token->data;
	token->data = new_data;
	free(temp);
	return (EXIT_SUCCESS);
}

static bool	expand_check(char *str, size_t start)
{
	bool	res;
	size_t	i;

	res = false;
	i = start;
	if (ft_strncmp(str, "~/", 2) == 0 || ft_strncmp(str, "~", 2) == 0)
		return (true);
	else if (str[i] == '$' && (str[i + 1] == ' ' || str[i + 1] == '\0'))
		return (false);
	else if (quote_check(str, start) == IN_SINGLE)
		return (false);
	else if (str[i] == '$' && (str[i + 1] == '\'' || str[i + 1] == '\"'))
	{
		if (quote_check(str, start) == NOT_QUOTED)
			return (true);
		else
			return (false);
	}
	return (true);
}

size_t	expand(t_list *tokens, t_env *env, t_init *process)
{
	t_token	*token;
	size_t	i;

	while (tokens != NULL)
	{
		i = 0;
		token = tokens->content;
		while (token->data != NULL && token->data[i] != '\0')
		{
			if (ft_strncmp(token->data, "~/", 2) == 0 || \
			ft_strncmp(token->data, "~", 2) == 0 || token->data[i] == '$' )
			{
				if (expand_check(token->data, i) == true)
				{
					if (replace_token(token, env, process) == EXIT_FAILURE)
						return (EXIT_FAILURE);
					i = -1;
				}
			}
			i++;
		}
		tokens = tokens->next;
	}
	return (EXIT_SUCCESS);
}
