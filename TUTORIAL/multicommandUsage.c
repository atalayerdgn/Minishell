#include "libft/libft.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>
//basit bir multicommand kullanımı
//boşluksuz komutları çalıştırır
//ve tek bir komutu çalıştırır gibi çalışır
//örnek: ls|wc|cat
//kendinize göre ayarlayabilirsiniz
//fd'leri ayarlamak için pipe kullanıldı
//pipe kullanımı için: https://www.geeksforgeeks.org/pipe-system-call/
typedef struct s_cmd
{
	int		**pipe;
	char	*cmd;
	char	**args;
}	t_cmd;
char	*get_path(char *cmd, char **env)
{
	int		i;
	char	**path;
	char	*tmp;
	char	*tmp2;
	i = 0;
	while (env[i])
	{
		if (strncmp(env[i], "PATH=", 5) == 0)
			break ;
		i++;
	}
	path = ft_split(env[i] + 5, ':');
	i = 0;
	while (path[i])
	{
		tmp = ft_strjoin(path[i], "/");
		tmp2 = ft_strjoin(tmp, cmd);
		if (access(tmp2, F_OK) == 0)
		{
			return (tmp2);
			break ;
		}
		i++;
	}
	i = 0;
	return (cmd);
}
int	ft_ministrlen(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}
void	lex(t_cmd *cmd)
{
	cmd->args = ft_split(cmd->cmd, '|');
	if(!cmd->args)
		return ;
}
void	ft_execve(t_cmd *data, char **env)
{
	int	i;
	int	status;
	pid_t	pid;
	char	*path;
	i = 0;
	while (data->args[i])
	{
		pid = fork();
		if (pid == 0)
		{
			path = get_path(data->args[i], env);
			if (i != 0)
			{
				dup2(data->pipe[i - 1][0], 0);
				close(data->pipe[i - 1][0]);
			}
			if (data->args[i + 1])
			{
				dup2(data->pipe[i][1], 1);
				close(data->pipe[i][1]);
			}
			execve(path, ft_split(data->args[i], ' '), env);
			perror("execve");
			exit(0);
		}
		else
		{
			waitpid(pid, &status, 0);
			if (i != 0)
				close(data->pipe[i - 1][0]);
			if (data->args[i + 1])
				close(data->pipe[i][1]);
		}
		i++;
	}
}
void	execute(t_cmd *data, char **env)
{
	data->pipe = malloc(sizeof(int *) * ft_ministrlen(data->args));
	if (!data->pipe)
		return ;
	int	i = 0;
	while(i < ft_ministrlen(data->args) - 1)
	{
		data->pipe[i] = malloc(sizeof(int) * 2);
		if (!data->pipe[i])
			return ;
		pipe(data->pipe[i]);
		i++;
	}
	ft_execve(data, env);
}
int	main(int ac, char **av, char **env)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (0);
	while(1)
	{
		cmd->cmd = readline("minishell$ ");
		if (!cmd->cmd)
			break ;
		if (strcmp(cmd->cmd, "exit") == 0)
			break ;
		lex(cmd);
		execute(cmd, env);
		free(cmd->cmd);
		fflush(stdout);
	}
}
