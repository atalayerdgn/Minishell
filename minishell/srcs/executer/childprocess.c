/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childprocess.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerdogan <aerdogan@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 19:23:14 by aerdogan          #+#    #+#             */
/*   Updated: 2023/12/21 12:01:15 by aerdogan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <sys/errno.h>
#include <readline/readline.h>
#include <readline/history.h>

void	ft_wait_for_last_child(t_init *process)
{
	ft_close_pipe_fds(process);
	waitpid(process->ids[process->i - 1], &process->status, 0);
	if (WIFEXITED(process->status))
		process->errorcode = WEXITSTATUS(process->status);
	else if (WIFSIGNALED(process->status))
		process->errorcode = 128 + WTERMSIG(process->status);
	while (1)
	{
		if (wait(NULL) == -1)
			break ;
	}
	free(process->ids);
	process->ids = NULL;
	if (g_signal == SIGINT)
		process->errorcode = 130;
	g_signal = 0;
}

static void	ft_child_free(t_list *lst, t_init *process)
{
	int32_t	exit_nr;

	exit_nr = process->errorcode;
	rl_clear_history();
	ft_free_str_array(process->env->new_env, NULL);
	ft_reset_process(lst, process);
	exit(exit_nr);
}

static void	ft_child_process(t_list *lst, t_init *process)
{
	if (!process->cmd || process->fdin == -1 || process->fdout == -1)
	{
		ft_close_pipe_fds(process);
		exit(process->errorcode);
	}
	if (!process->fdout && ((!process->i && process->nr_of_cmds > 1) || \
		(process->i != (process->nr_of_cmds - 1))))
	{
		if (dup2(process->pipes[process->i][1], STDOUT_FILENO) == -1)
			ft_throw_error(process, errno);
	}
	if (process->i != 0 && process->heredoc == false && !process->fdin)
	{
		if (dup2(process->pipes[process->i - 1][0], STDIN_FILENO) == -1)
			ft_throw_error(process, errno);
	}
	ft_close_pipe_fds(process);
	if (process->cmd->builtin == false)
		ft_execve(lst, process);
	else
	{
		ft_run_builtin(lst, process, process->cmd);
		ft_child_free(lst, process);
	}
}

static void	ft_find_cmd(t_scmd_list *lst, t_init *process)
{
	while (lst)
	{
		if (lst->type == CMD)
		{
			process->cmd = lst->data;
			break ;
		}
		lst = lst->next;
	}
	if (!lst)
		process->cmd = NULL;
}

void	ft_create_child(t_list *lst, t_init *process)
{
	ft_find_cmd(lst->content, process);
	process->ids[process->i] = fork();
	if (process->ids[process->i] == -1)
	{
		ft_throw_error(process, errno);
		return ;
	}
	if (process->ids[process->i] == 0)
		ft_child_process(lst, process);
	process->i++;
	process->heredoc = false;
	process->fdout = 0;
	process->fdin = 0;
}
