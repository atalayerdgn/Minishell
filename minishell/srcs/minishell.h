/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerdogan <aerdogan@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 21:02:03 by aerdogan          #+#    #+#             */
/*   Updated: 2023/12/24 01:04:39 by aerdogan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdbool.h>
# include <stdlib.h>
# include "42lib/libft/libft.h"

extern int32_t	g_signal;

typedef enum e_quotes
{
	NOT_QUOTED = 0,
	IN_SINGLE = 1,
	IN_DOUBLE = 2
}	t_quotes;

typedef enum e_string_status
{
	NO_STRING = 0,
	EMPTY_STRING = 1,
	VALID_STRING = 2
}	t_string_status;

typedef enum e_struct_type
{
	CMD = 0,
	RDR = 1
}	t_struct_type;

typedef enum e_rdr_type
{
	RDR_INPUT,
	RDR_OUTPUT,
	HERE_DOC,
	RDR_APPEND
}	t_rdr_type;

typedef enum e_token_type
{
	CMD_TOKEN			= 1,
	RDR_TOKEN			= 2,
	PIPE_TOKEN			= 3
}	t_token_type;

typedef struct s_rdr
{
	char		*data;
	t_rdr_type	type;
	bool		expand;
}	t_rdr;

typedef struct s_env
{
	char	**new_env;
	size_t	env_len;
}	t_env;

typedef struct s_cmd
{
	char	*path;
	char	**arg;
	t_env	*env;
	bool	builtin;
}	t_cmd;

typedef struct s_scmd_list
{
	void				*data;
	t_struct_type		type;
	struct s_scmd_list	*next;
}	t_scmd_list;

typedef struct s_export
{
	char	**new_env;
	char	*arg_copy;
	size_t	arg_len;
	size_t	var_len;
	size_t	name_len;
	char	*new_var;
}	t_export;

typedef struct s_init
{
	t_env	*env;
	pid_t	*ids;
	t_cmd	*cmd;
	int32_t	status;
	int32_t	errorcode;
	size_t	i;
	size_t	nr_of_cmds;
	size_t	pipe_count;
	int32_t	**pipes;
	int32_t	fdin;
	int32_t	fdout;
	int32_t	oldout;
	int32_t	oldin;
	bool	heredoc;
	bool	must_exit;
	size_t	arg_count;
}	t_init;

typedef struct s_token
{
	char			*data;
	t_token_type	type;
}	t_token;

bool		ft_echo_builtin(t_init *process, t_cmd *cmd);
void		ft_cd_builtin(t_init *process, t_cmd *cmd, size_t i);
void		ft_pwd_builtin(t_init *process);
void		ft_exit_builtin(t_list *lst, t_init *process, t_cmd *cmd);

void		ft_env_builtin(t_init *process, t_cmd *cmd);
bool		ft_set_oldpwd(t_init *process, t_env *env, char *str, size_t i);
bool		ft_set_pwd(t_init *process, t_env *env, char *buffer, size_t i);
bool		ft_copy_env(t_init *process, t_env *env, char **old_env);

void		ft_export_append(t_init *process, t_cmd *cmd, char *arg, size_t j);

void		ft_add_new_var(t_init *process, t_cmd *cmd, t_env *env, char *arg);
void		ft_overwrite_var(t_init *process, t_cmd *cmd, char *arg, size_t c);
void		ft_export_builtin(t_init *process, t_cmd *cmd);

void		ft_fill_env(t_init *process, t_cmd *cmd, t_export *exp, size_t i);
void		ft_check_for_plus(char *arg);
int32_t		ft_find_value(char *var);
bool		ft_write_export(char **sortedenv);

void		ft_unset_builtin(t_init *process, t_cmd *cmd);

void		ft_wait_for_last_child(t_init *process);
void		ft_create_child(t_list *lst, t_init *process);

void		ft_error_export_unset(char *name, char *option);
void		ft_error_exit(t_list *lst, t_init *process, char *str);
void		ft_error_env(int32_t errnr, t_cmd *cmd);
void		ft_throw_error(t_init *process, int32_t errnr);

void		ft_reset_process(t_list *lst, t_init *process);
void		ft_execve(t_list *lst, t_init *process);
bool		ft_executor(t_list *lst, t_init *process);

void		ft_close_pipe_fds(t_init *process);
bool		ft_check_for_files(t_scmd_list *lst, t_init *process);

bool		ft_heredoc(t_init *process, char *data);

bool		ft_find_path(t_list *lst, t_init *process);

void		ft_free_pipes(t_init *process, size_t pipe_count);
size_t		ft_count_pipes(t_list *arglst);
bool		ft_create_pipes(t_init *process, size_t pipe_count);

bool		ft_setup_interactive(t_init *process);
bool		ft_setup_noninteractive(t_init *process);

char		*find_end(char *str, char *beginning);
char		*find_middle(char *str, size_t i, size_t len);
char		*find_begin(char *str, bool in_heredoc);
void		multi_free(char *begin, char *mid, char *end, char *temp);

char		*expand_data(char *str, t_env *env, bool in_heredoc, \
			t_init *process);
t_quotes	quote_check(const char *str, size_t start);
size_t		expand(t_list *tokens, t_env *env, t_init *process);

t_token		*split_rdrtoken(t_token *token, size_t i);
size_t		is_splitable(t_token *token);
t_list		*tokenisation(const char *user_input);
char		**lexer_split(char const *s);

t_list		*parse(t_env *env, t_init *process, const char *user_input);
t_list		*make_scmdlist(t_list *tokens, t_scmd_list **scmds, \
			t_init *process);
t_list		*scmdlist2(t_list *tokens, t_scmd_list **scmds, t_init *process);
size_t		remove_quotes(t_list *tokens);
size_t		count_cmdtokens(t_list **tokens);
bool		is_builtin(t_list **tokens);
char		*new_userinput(char *input, char c);
char		*complete_input(t_init *process, char *input);

int32_t		is_whitespace_ll(char c);
int64_t		ft_atollong(t_list *lst, t_init *process, const char *str);

void		ft_bubble_sort(char **sortedenv, size_t len);

void		ft_remove_quotes(char *data);
void		ft_restore_old_fd(t_init *process);
void		ft_store_old_fd(t_init *process);
void		ft_run_builtin(t_list *lst, t_init *process, t_cmd *cmd);
bool		ft_prep(t_list *lst, t_init *process);

void		freestructs_nodata(t_scmd_list *temp);
void		freescmdlst_nodata(t_scmd_list **lst);
void		freelst_nodata(t_list *lst);

void		ft_free_str_array(char **arr, char *str);
void		freescmdlst(t_scmd_list **lst);
void		ft_freelst(t_list *lst);
void		free_tokenlst(t_list **tokens, bool free_data);

t_scmd_list	*ft_lstnewscmd(void *data, t_struct_type type, t_init *process);
void		scmdlst_add_back(t_scmd_list **scmds, t_scmd_list *new);

t_rdr		*ft_allocate_mem_rdr(char *data, t_rdr_type type);
t_cmd		*ft_allocate_mem_cmd(char **arg, t_env *env, bool builtin);
t_token		*new_token(const char *data);

bool		str_equals(char *lhs, char *rhs);
bool		ft_cmpname(const char *s1, const char *s2, size_t n);

#endif
