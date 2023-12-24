/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prelim_parser_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerdogan <aerdogan@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 11:30:05 by aerdogan          #+#    #+#             */
/*   Updated: 2023/11/16 21:40:03 by aerdogan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../42lib/libft/libft.h"
#include <stdlib.h>
#include <stdbool.h>
#include <readline/readline.h>
#include <readline/history.h>

static bool	userinput_check(char c, char *user_input)
{
	bool	res;

	res = false;
	if (c == '\'' && ft_strchr(user_input, '\'') != NULL)
		res = true;
	else if (c == '\"' && ft_strchr(user_input, '\"') != NULL)
		res = true;
	else if (c == '|' && ft_strlen(user_input) > 0)
		res = true;
	return (res);
}

static char	*new_userinput2(char *temp, char *user_input, char c)
{
	char	*rl;

	while (1)
	{
		if (c == '|')
			temp = ft_strjoin(user_input, " ");
		else
			temp = ft_strjoin(user_input, "\n");
		free(user_input);
		if (!temp)
			return (NULL);
		rl = readline("> ");
		if (!rl)
			return (ft_putendl_fd("minishell: unexpected end of file", \
				STDERR_FILENO), free(temp), ft_calloc(1, sizeof(char)));
		user_input = ft_strjoin(temp, rl);
		free(temp);
		free(rl);
		if (!user_input)
			return (NULL);
		if (userinput_check(c, user_input) == true)
			break ;
	}
	return (user_input);
}

char	*new_userinput(char *input, char c)
{
	char	*user_input;
	char	*temp;

	temp = NULL;
	user_input = ft_calloc(1, sizeof(char));
	if (!user_input)
		return (NULL);
	user_input = new_userinput2(temp, user_input, c);
	if (!user_input)
		return (NULL);
	if (user_input[0] == '\0')
		return (free(input), user_input);
	temp = ft_strjoin(input, user_input);
	if (!temp)
		return (free(input), free(user_input), NULL);
	return (free(input), free(user_input), temp);
}
