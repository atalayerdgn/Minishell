/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerdogan <aerdogan@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 10:29:59 by aerdogan          #+#    #+#             */
/*   Updated: 2023/12/23 11:54:18 by abulut           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <stdbool.h>

int32_t	g_signal = 0;

static bool	ft_only_spaces_check(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (is_whitespace_ll(str[i]) == 0)
			return (false);
		i++;
	}
	return (true);
}

static t_string_status	read_from_line(char **str)
{
	*str = readline("Minishell@42Kocaeli:");
	if (!*str)
	{
		ft_putendl_fd("Exit", STDERR_FILENO);
		return (NO_STRING);
	}
	else if (!*str[0])
	{
		ft_free_str_array(NULL, *str);
		return (EMPTY_STRING);
	}
	else if (ft_only_spaces_check(*str))
	{
		add_history(*str);
		ft_free_str_array(NULL, *str);
		return (EMPTY_STRING);
	}
	else
		return (VALID_STRING);
}

static void	ft_loop(t_list *lst, t_init *process, char *str)
{
	t_string_status	readline_return;

	while (1)
	{
		if (!ft_setup_interactive(process))
			break ;
		readline_return = read_from_line(&str);
		if (readline_return == NO_STRING)
			break ;
		else if (readline_return == EMPTY_STRING)
			continue ;
		str = complete_input(process, str);
		if (!str || !ft_setup_noninteractive(process))
			break ;
		if (!str[0])
		{
			ft_free_str_array(NULL, str);
			continue ;
		}
		add_history(str);
		lst = parse(process->env, process, str);
		ft_free_str_array(NULL, str);
		if (process->must_exit == true || !ft_executor(lst, process))
			break ;
	}
}

int32_t	main(int32_t argc, char **argv, char **envp)
{
	t_list	lst;
	t_init	process;
	t_env	env;
	char	*str;

	(void)argv, (void)argc;
	process.errorcode = 0;
	process.must_exit = false;
	str = NULL;
	if (!ft_copy_env(&process, &env, envp))
		return (process.errorcode);
	process.env = &env;
	ft_loop(&lst, &process, str);
	rl_clear_history();
	if (g_signal == SIGINT)
		process.errorcode = 130;
	ft_free_str_array(env.new_env, NULL);
	return (process.errorcode);
}
