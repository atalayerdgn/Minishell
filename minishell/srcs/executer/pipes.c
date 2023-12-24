/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerdogan <aerdogan@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 21:40:47 by aerdogan          #+#    #+#             */
/*   Updated: 2023/11/28 23:11:48 by aerdogan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <stdlib.h>
#include <stdbool.h>
#include <sys/errno.h>
#include "../42lib/libft/libft.h"

void	ft_free_pipes(t_init *process, size_t pipe_count)
{
	size_t	i;

	i = 0;
	while (i < pipe_count)
	{
		free(process->pipes[i]);
		process->pipes[i] = NULL;
		i++;
	}
	process->pipe_count = 0;
	if (process->pipes)
	{
		free(process->pipes);
		process->pipes = NULL;
	}
}

size_t	ft_count_pipes(t_list *lst)
{
	size_t	pipe_count;

	pipe_count = 0;
	while (lst->next)
	{
		pipe_count++;
		lst = lst->next;
	}
	return (pipe_count);
}

bool	ft_create_pipes(t_init *process, size_t pipe_count)
{
	size_t	i;

	i = 0;
	process->pipes = malloc(pipe_count * sizeof(int32_t *));
	if (!process->pipes)
		return (perror("minishell"), false);
	while (i < pipe_count)
	{
		process->pipes[i] = malloc(2 * sizeof(int32_t));
		if (!process->pipes[i] || pipe(process->pipes[i]) == -1)
		{
			perror("minishell");
			ft_free_pipes(process, i);
			return (false);
		}
		i++;
	}
	return (true);
}
