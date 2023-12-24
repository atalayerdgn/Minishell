/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerdogan <aerdogan@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 12:01:00 by aerdogan          #+#    #+#             */
/*   Updated: 2023/11/18 01:01:01 by abulut           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <stdlib.h>
#include <sys/errno.h>
#include "../42lib/libft/libft.h"

void	ft_add_new_var(t_init *process, t_cmd *cmd, t_env *env, char *arg)
{
	t_export	exp;
	int32_t		i;

	i = 0;
	ft_check_for_plus(arg);
	exp.arg_len = ft_strlen(arg);
	exp.new_env = malloc((env->env_len + 2) * sizeof(char *));
	if (!exp.new_env)
	{
		ft_throw_error(process, errno);
		process->must_exit = true;
		return ;
	}
	exp.arg_copy = malloc((exp.arg_len + 1) * sizeof(char));
	if (!exp.arg_copy)
	{
		ft_throw_error(process, errno);
		free(exp.new_env);
		exp.new_env = NULL;
		process->must_exit = true;
		return ;
	}
	ft_memcpy(exp.arg_copy, arg, (exp.arg_len + 1));
	ft_fill_env(process, cmd, &exp, i);
}

void	ft_overwrite_var(t_init *process, t_cmd *cmd, char *arg, size_t c)
{
	char	*temp;
	size_t	len;

	if (!ft_strchr(arg, '='))
		return ;
	len = ft_strlen(arg);
	temp = malloc((len + 1) * sizeof(char));
	if (!cmd->env->new_env[c])
	{
		ft_throw_error(process, errno);
		process->must_exit = true;
		return ;
	}
	free(cmd->env->new_env[c]);
	cmd->env->new_env[c] = temp;
	ft_memcpy(cmd->env->new_env[c], arg, (len + 1));
}

static bool	ft_check_export_input(t_init *process, char *arg, size_t j)
{
	t_cmd	*cmd;
	size_t	c;

	cmd = process->cmd;
	c = 0;
	if (arg[j] == '_' && (arg[j + 1] == '=' || arg[j + 1] == '+'))
		return (false);
	if (arg[j] && (ft_isalpha(arg[j]) || (arg[j] == '_' && arg[1])))
	{
		while (ft_isalpha(arg[j]) || ft_isdigit(arg[j]) || arg[j] == '_')
			j++;
		while (cmd->env->new_env[c])
		{
			if (!ft_cmpname(arg, cmd->env->new_env[c], j) && arg[j] != '+')
				return (ft_overwrite_var(process, cmd, arg, c), true);
			c++;
		}
		if (arg[j] == '+' && (arg[j + 1] == '='))
			return (ft_export_append(process, cmd, arg, j), true);
		else if (arg[j] == '=' || !arg[j])
			return (ft_add_new_var(process, cmd, cmd->env, arg), true);
	}
	return (false);
}

static bool	ft_export_no_args(t_cmd *cmd)
{
	char	**sortedenv;
	size_t	len;

	len = 0;
	while (cmd->env->new_env[len])
		len++;
	sortedenv = malloc((len + 1) * sizeof(char *));
	if (!sortedenv)
		return (perror("minishell"), false);
	ft_memcpy(sortedenv, cmd->env->new_env, (len + 1) * sizeof(char *));
	ft_bubble_sort(sortedenv, len);
	if (!ft_write_export(sortedenv))
	{
		free(sortedenv);
		sortedenv = NULL;
		return (false);
	}
	free(sortedenv);
	sortedenv = NULL;
	return (true);
}

void	ft_export_builtin(t_init *process, t_cmd *cmd)
{
	size_t	i;

	i = 1;
	process->errorcode = 0;
	if (!cmd->arg[i])
	{
		if (!ft_export_no_args(cmd))
		{
			process->errorcode = 1;
			process->must_exit = true;
		}
	}
	while (process->must_exit == false && cmd->arg[i])
	{
		if (!ft_check_export_input(process, cmd->arg[i], 0))
		{
			ft_error_export_unset("export", cmd->arg[i]);
			process->errorcode = 1;
		}
		else if (process->must_exit == true)
			process->errorcode = 1;
		else
			process->errorcode = 0;
		i++;
	}
}
