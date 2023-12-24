/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerdogan <aerdogan@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 01:01:09 by aerdogan          #+#    #+#             */
/*   Updated: 2023/12/24 18:32:10 by aerdogan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../42lib/libft/libft.h"
#include <sys/errno.h>
#include <sys/param.h>
#include <readline/readline.h>
#include <readline/history.h>

void	ft_error_export_unset(char *name, char *option)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(name, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putchar_fd('`', STDERR_FILENO);
	ft_putstr_fd(option, STDERR_FILENO);
	ft_putchar_fd('\'', STDERR_FILENO);
	ft_putendl_fd(": not a valid identifier", STDERR_FILENO);
}

void	ft_error_exit(t_list *lst, t_init *process, char *str)
{
	ft_putstr_fd("exit\nminishell: exit: ", STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putendl_fd(": numeric argument required", STDERR_FILENO);
	rl_clear_history();
	ft_free_str_array(process->env->new_env, NULL);
	ft_reset_process(lst, process);
	exit(255);
}

void	ft_error_env(int32_t errnr, t_cmd *cmd)
{
	ft_putstr_fd(cmd->arg[0], STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	errno = errnr;
	perror(cmd->arg[1]);
}

void	ft_throw_error(t_init *process, int32_t errnr)
{
	errno = errnr;
	perror("minishell");
	process->errorcode = 1;
}
