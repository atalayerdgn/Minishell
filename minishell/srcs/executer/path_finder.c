/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_finder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerdogan <aerdogan@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 16:30:49 by aerdogan          #+#    #+#             */
/*   Updated: 2023/11/23 03:40:50 by aerdogan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <stdbool.h>
#include <stdlib.h>
#include "../42lib/libft/libft.h"
#include <unistd.h>
#include <sys/errno.h>

static bool	ft_try_paths(char **path, t_cmd *cmd)
{
	size_t	i;
	char	*cmdpath;
	char	*temp;

	i = 0;
	while (path && path[i])
	{
		temp = ft_strjoin(path[i], "/");
		if (!temp)
			return (false);
		cmdpath = ft_strjoin(temp, cmd->arg[0]);
		free(temp);
		temp = NULL;
		if (!cmdpath)
			return (false);
		if (access(cmdpath, F_OK) == 0)
		{
			cmd->path = cmdpath;
			break ;
		}
		free(cmdpath);
		cmdpath = NULL;
		i++;
	}
	return (true);
}

static bool	ft_is_path(t_init *process, t_cmd *cmd)
{
	char	*arg_copy;
	size_t	len;

	len = ft_strlen(cmd->arg[0]) + 1;
	if (cmd->arg[0][0] == '/' || cmd->arg[0][0] == '.')
	{
		arg_copy = malloc(sizeof(char) * len);
		if (!arg_copy)
		{
			process->must_exit = true;
			return (false);
		}
		ft_memmove(arg_copy, cmd->arg[0], len);
		cmd->path = arg_copy;
		return (true);
	}
	return (false);
}

static char	**ft_search_in_env(t_init *process, t_cmd *tempcmd, char **path, \
	size_t i)
{
	while (tempcmd->env->new_env[i])
	{
		if (ft_strncmp(tempcmd->env->new_env[i], "PATH=", 5) == 0)
		{
			path = ft_split(tempcmd->env->new_env[i] + 5, ':');
			if (!path)
				process->must_exit = true;
			return (path);
		}
		i++;
	}
	return (path);
}

static bool	ft_find_path2(t_init *process, t_scmd_list *tempscmd)
{
	t_cmd	*tempcmd;
	char	**path;
	size_t	i;

	path = NULL;
	i = 0;
	tempcmd = tempscmd->data;
	if (tempcmd->builtin == false)
	{
		if (ft_is_path(process, tempcmd))
			return (true);
		if (process->must_exit == true)
			return (false);
		path = ft_search_in_env(process, tempcmd, path, i);
		if (process->must_exit == true)
			return (false);
		if (!ft_try_paths(path, tempcmd))
			return (ft_free_str_array(path, NULL), false);
		return (ft_free_str_array(path, NULL), true);
	}
	return (true);
}

bool	ft_find_path(t_list *lst, t_init *process)
{
	t_list		*temp;
	t_scmd_list	*tempscmd;

	temp = lst;
	while (temp)
	{
		tempscmd = temp->content;
		while (tempscmd)
		{
			if (tempscmd->type == CMD)
			{
				if (!ft_find_path2(process, tempscmd) || process->must_exit)
					return (ft_throw_error(process, ENOMEM), false);
			}
			tempscmd = tempscmd->next;
		}
		temp = temp->next;
	}
	return (true);
}
