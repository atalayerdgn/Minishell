/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prelim_parser.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerdogan <aerdogan@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 23:01:50 by aerdogan          #+#    #+#             */
/*   Updated: 2023/11/16 23:41:31 by aerdogan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <stdlib.h>
#include <sys/errno.h>
#include <sys/param.h>

static size_t	needs_closing(char *input, char c, size_t start)
{
	size_t	i;
	size_t	count;

	i = start;
	count = 0;
	while (input[i] != '\0')
	{
		if ((input[i] == c && i == 0) || \
			(input[i] == c && input[i - 1] != '\\'))
			count++;
		if (count == 2)
			return (i);
		i++;
	}
	if (count == 1)
		return (0);
	return (i);
}

static char	*close_quotes(char *input)
{
	size_t	i;
	size_t	check;
	char	c;

	i = 0;
	check = 0;
	while (input[i] != '\0')
	{
		c = '0';
		if (input[i] == '\'')
			c = '\'';
		else if (input[i] == '\"')
			c = '\"';
		if (c != '0')
		{
			check = needs_closing(input, c, i);
			if (check == 0)
				return (new_userinput(input, c));
			i = check;
		}
		i++;
	}
	return (input);
}

char	*complete_input(t_init *process, char *input)
{
	size_t	len;

	input = close_quotes(input);
	if (!input)
		return (ft_throw_error(process, ENOMEM), NULL);
	len = ft_strlen(input);
	if (!len)
		return (input);
	if ((len > 1 && (input[len - 1] == '|' && input[len - 2] != '\\')) || \
		(len > 2 && (input[len - 2] == '|' && input[len - 3] != '\\')))
		input = new_userinput(input, '|');
	if (!input)
		return (ft_throw_error(process, ENOMEM), NULL);
	return (input);
}
