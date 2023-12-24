/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerdogan <aerdogan@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 13:38:11 by aerdogan          #+#    #+#             */
/*   Updated: 2023/12/11 19:01:12 by abulut           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <stdlib.h>
#include <sys/errno.h>
#include <sys/param.h>

void	ft_env_builtin(t_init *process, t_cmd *cmd)
{
	size_t	i;

	i = 0;
	if (str_equals("env", cmd->arg[0]))
	{
		if (cmd->arg[1])
		{
			process->errorcode = 127;
			ft_error_env(ENOENT, cmd);
			return ;
		}
		while (cmd->env->new_env[i])
		{
			if (ft_strchr(cmd->env->new_env[i], '='))
				printf("%s\n", cmd->env->new_env[i]);
			i++;
		}
	}
	process->errorcode = 0;
}

static bool	ft_copy_env3(t_init *process, t_env *env, size_t pwds, size_t i)
{
	char	buffer[MAXPATHLEN];

	if (pwds == 1)
	{
		if (!ft_set_oldpwd(process, env, "no OLDPWD :)", i))
			return (false);
	}
	else if (pwds == 3)
	{
		if (!ft_set_pwd(process, env, buffer, i))
			return (false);
	}
	env->new_env[i + 1] = NULL;
	env->env_len += 1;
	return (true);
}

static bool	ft_copy_env2(t_init *process, t_env *env, size_t pwds, size_t i)
{
	char	buffer[MAXPATHLEN];

	if (pwds == 0)
	{
		if (!ft_set_pwd(process, env, buffer, i) || \
			!ft_set_oldpwd(process, env, "no OLDPWD :)", i + 1))
			return (false);
		env->env_len += 2;
	}
	else if (pwds == 2)
	{
		env->new_env[i] = NULL;
		env->new_env[i + 1] = NULL;
	}
	else if (!ft_copy_env3(process, env, pwds, i))
	{
		env->new_env[i] = NULL;
		return (false);
	}
	env->new_env[i + 2] = NULL;
	return (true);
}

static size_t	ft_env_len(t_env *env, char **old_env)
{
	bool	found_pwd;
	bool	found_oldpwd;

	env->env_len = 0;
	found_pwd = false;
	found_oldpwd = false;
	while (old_env[env->env_len])
	{
		if (ft_strncmp(old_env[env->env_len], "PWD=", 4) == 0)
			found_pwd = true;
		if (ft_strncmp(old_env[env->env_len], "OLDPWD=", 7) == 0)
			found_oldpwd = true;
		env->env_len++;
	}
	if (found_oldpwd && found_pwd)
		return (2);
	if (!found_oldpwd && !found_pwd)
		return (0);
	if (!found_oldpwd && found_pwd)
		return (1);
	return (3);
}

bool	ft_copy_env(t_init *process, t_env *env, char **old_env)
{
	size_t	i;
	size_t	str_len;
	size_t	pwds;

	i = 0;
	pwds = ft_env_len(env, old_env);
	env->new_env = malloc((env->env_len + 3) * sizeof(char *));
	if (!env->new_env)
		return (ft_throw_error(process, errno), false);
	while (old_env[i])
	{
		str_len = ft_strlen(old_env[i]);
		env->new_env[i] = malloc((str_len + 1) * sizeof(char));
		if (!env->new_env[i])
		{
			ft_free_str_array(env->new_env, NULL);
			return (ft_throw_error(process, ENOMEM), false);
		}
		ft_memmove(env->new_env[i], old_env[i], (str_len + 1));
		i++;
	}
	if (!ft_copy_env2(process, env, pwds, i))
		return (ft_free_str_array(env->new_env, NULL), false);
	return (true);
}
