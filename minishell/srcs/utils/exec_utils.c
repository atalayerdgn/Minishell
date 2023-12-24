/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerdogan <aerdogan@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 01:12:28 by aerdogan          #+#    #+#             */
/*   Updated: 2023/12/13 11:22:29 by aerdogan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <unistd.h>
#include <stdlib.h>
#include <sys/errno.h>
#include <stdbool.h>

void	ft_remove_quotes(char *data)
{
	size_t	i;

	i = 0;
	while (data[i])
	{
		if (data[i] == '\'' || data[i] == '"' || data[i] == '\n')
		{
			while (data[i])
			{
				data[i] = data[i + 1];
				i++;
			}
			i = 0;
		}
		else
			i++;
	}
}

void	ft_restore_old_fd(t_init *process)
{
	if (process->oldout != -1)
	{
		if (dup2(process->oldout, STDOUT_FILENO) == -1 || \
			close (process->oldout) == -1)
			ft_throw_error(process, errno);
		process->oldout = -1;
	}
	if (process->oldin != -1)
	{
		if (dup2(process->oldin, STDIN_FILENO) == -1 || \
			close (process->oldin) == -1)
			ft_throw_error(process, errno);
		process->oldin = -1;
	}
}

void	ft_store_old_fd(t_init *process)
{
	process->oldout = dup(STDOUT_FILENO);
	if (process->oldout == -1)
		ft_throw_error(process, errno);
	process->oldin = dup(STDIN_FILENO);
	if (process->oldin == -1)
		ft_throw_error(process, errno);
}

void	ft_run_builtin(t_list *lst, t_init *process, t_cmd *cmd)
{
	if (!ft_strncmp("echo", cmd->arg[0], 5))
	{
		if (ft_echo_builtin(process, cmd))
			process->errorcode = 0;
	}
	if (!ft_strncmp("cd", cmd->arg[0], 3))
	{
		if (cmd->arg[1] && cmd->arg[2])
		{
			ft_putendl_fd("minishell: cd: too many arguments", STDERR_FILENO);
			process->errorcode = 1;
			return ;
		}
		ft_cd_builtin(process, cmd, 0);
	}
	if (!ft_strncmp("pwd", cmd->arg[0], 4))
		ft_pwd_builtin(process);
	if (!ft_strncmp("export", cmd->arg[0], 7))
		ft_export_builtin(process, cmd);
	if (!ft_strncmp("unset", cmd->arg[0], 6))
		ft_unset_builtin(process, cmd);
	if (!ft_strncmp("env", cmd->arg[0], 4))
		ft_env_builtin(process, cmd);
	if (!ft_strncmp("exit", cmd->arg[0], 5))
		ft_exit_builtin(lst, process, cmd);
}

bool	ft_prep(t_list *lst, t_init *process)
{
	process->ids = NULL;
	process->cmd = NULL;
	process->status = 0;
	process->oldout = -1;
	process->oldin = -1;
	process->fdin = 0;
	process->fdout = 0;
	process->pipes = NULL;
	process->i = 0;
	process->pipe_count = ft_count_pipes(lst);
	process->nr_of_cmds = process->pipe_count + 1;
	process->heredoc = false;
	process->ids = malloc(process->nr_of_cmds * sizeof(pid_t));
	if (!process->ids)
		return (perror("minishell:"), false);
	if (process->nr_of_cmds > 1)
	{
		if (!ft_create_pipes(process, process->pipe_count))
			return (false);
	}
	return (true);
}
