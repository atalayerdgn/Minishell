/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerdogan <aerdogan@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 12:22:38 by aerdogan          #+#    #+#             */
/*   Updated: 2023/12/24 01:00:39 by abulut           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../42lib/libft/libft.h"
#include <stdlib.h>

static void	ft_find_unset_arg(char **env, char *arg, size_t len)
{
	char	*temp;
	size_t	j;

	j = 0;
	while (env[j])
	{
		if (!ft_cmpname(arg, env[j], len) && \
			(env[j][len] == '=' || !env[j][len]))
		{
			temp = env[j];
			while (env[j])
			{
				env[j] = env[j + 1];
				j++;
			}
			free(temp);
			temp = NULL;
			env[j] = NULL;
			break ;
		}
		j++;
	}
}

void	ft_unset_builtin(t_init *process, t_cmd *cmd)
{
	size_t	i;
	size_t	len;
	char	**arg;
	char	**env;

	i = 1;
	arg = cmd->arg;
	env = cmd->env->new_env;
	process->errorcode = 0;
	if (!arg[i])
		return ;
	while (arg[i])
	{
		len = ft_strlen(arg[i]);
		ft_find_unset_arg(env, arg[i], len);
		i++;
	}
}
