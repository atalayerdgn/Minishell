/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_append.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerdogan <aerdogan@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 09:16:03 by aerdogan          #+#    #+#             */
/*   Updated: 2023/11/18 11:01:04 by abulut           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../42lib/libft/libft.h"
#include <stdlib.h>
#include <sys/errno.h>

static void	ft_append_to_var(t_init *process, t_export *exp, char *arg, \
	size_t j)
{
	size_t	add_from_pos;

	add_from_pos = ft_find_value(arg);
	exp->arg_len = ft_strlen(process->cmd->env->new_env[j]);
	exp->var_len = exp->arg_len + ft_strlen(&arg[add_from_pos]);
	exp->new_var = ft_strjoin(process->cmd->env->new_env[j], \
		&arg[exp->name_len + 1]);
	if (!exp->new_var)
	{
		ft_throw_error(process, ENOMEM);
		process->must_exit = true;
		return ;
	}
	free(process->cmd->env->new_env[j]);
	process->cmd->env->new_env[j] = NULL;
	process->cmd->env->new_env[j] = exp->new_var;
}

void	ft_export_append(t_init *process, t_cmd *cmd, char *arg, size_t j)
{
	t_export	exp;

	exp.name_len = j;
	j = 0;
	while (cmd->env->new_env[j])
	{
		if (!ft_cmpname(cmd->env->new_env[j], arg, exp.name_len))
		{
			ft_check_for_plus(arg);
			if (!cmd->env->new_env[j][exp.name_len])
			{
				ft_overwrite_var(process, cmd, arg, j);
				return ;
			}
			ft_append_to_var(process, &exp, arg, j);
			return ;
		}
		j++;
	}
	ft_add_new_var(process, cmd, cmd->env, arg);
}
