/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerdogan <aerdogan@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 15:32:16 by aerdogan          #+#    #+#             */
/*   Updated: 2023/11/28 01:01:17 by abulut           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../42lib/libft/libft.h"
#include <stdlib.h>
#include <stdbool.h>
#include <sys/param.h>
#include <sys/errno.h>

static bool	ft_cd3(t_init *process, char *buffer, size_t i, size_t j)
{
	while (process->env->new_env[j])
	{
		if (ft_strncmp(process->env->new_env[j], "PWD=", 4) == 0)
			break ;
		j++;
	}
	if (!process->env->new_env[j])
	{
		if (!ft_set_pwd(process, process->env, buffer, j))
			return (false);
		return (true);
	}
	if (!ft_set_oldpwd(process, process->env, process->env->new_env[j] + 4, i))
		return (false);
	if (!ft_set_pwd(process, process->env, buffer, j))
		return (false);
	return (true);
}

static bool	ft_cd2(t_init *process, t_cmd *cmd)
{
	char	buffer[MAXPATHLEN];
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (cmd->env->new_env[i])
	{
		if (ft_strncmp(cmd->env->new_env[i], "OLDPWD=", 7) == 0)
			break ;
		i++;
	}
	if (!cmd->env->new_env[i])
	{
		if (!ft_set_oldpwd(process, process->env, "no OLDPWD :)", i))
			return (false);
	}
	if (!ft_cd3(process, buffer, i, j))
		return (false);
	return (true);
}

void	ft_cd_builtin(t_init *process, t_cmd *cmd, size_t i)
{
	process->errorcode = 0;
	if (!cmd->arg[1])
	{
		while (cmd->env->new_env[i])
		{
			if (ft_strncmp(cmd->env->new_env[i], "HOME=", 5) == 0)
			{
				if (chdir(cmd->env->new_env[i] + 5) == -1)
				{
					ft_throw_error(process, errno);
					return ;
				}
			}
			i++;
		}
	}
	else if (chdir(cmd->arg[1]) == -1)
	{
		ft_throw_error(process, errno);
		return ;
	}
	if (!ft_cd2(process, cmd))
		process->must_exit = true;
}
