/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_mem.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerdogan <aerdogan@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 02:02:45 by aerdogan          #+#    #+#             */
/*   Updated: 2023/11/05 05:43:46 by aerdogan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <stdlib.h>
#include <stdbool.h>

t_rdr	*ft_allocate_mem_rdr(char *data, t_rdr_type type)
{
	t_rdr	*rdr;

	rdr = (t_rdr *)malloc(sizeof(t_rdr));
	if (!rdr)
		return (NULL);
	rdr->data = data;
	rdr->type = type;
	return (rdr);
}

t_cmd	*ft_allocate_mem_cmd(char **arg, t_env *env, bool builtin)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->arg = arg;
	cmd->env = env;
	cmd->builtin = builtin;
	cmd->path = NULL;
	return (cmd);
}

t_token	*new_token(const char *data)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (token == NULL)
		return (NULL);
	token->data = (char *)data;
	token->type = 0;
	return (token);
}
