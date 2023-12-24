/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerdogan <aerdogan@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 11:00:45 by abulut            #+#    #+#             */
/*   Updated: 2023/12/20 10:31:46 by aerdogan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include "../42lib/libft/libft.h"
#include <sys/errno.h>
#include <sys/param.h>

bool	ft_set_oldpwd(t_init *process, t_env *env, char *str, size_t i)
{
	char	*temp;

	temp = ft_strjoin("OLDPWD=", str);
	if (!temp)
		return (ft_throw_error(process, ENOMEM), false);
	free(env->new_env[i]);
	env->new_env[i] = temp;
	return (true);
}

bool	ft_set_pwd(t_init *process, t_env *env, char *buffer, size_t i)
{
	char	*temp;

	if (!getcwd(buffer, MAXPATHLEN))
		return (ft_throw_error(process, errno), true);
	temp = ft_strjoin("PWD=", buffer);
	if (!temp)
		return (ft_throw_error(process, ENOMEM), false);
	free(env->new_env[i]);
	env->new_env[i] = temp;
	return (true);
}
