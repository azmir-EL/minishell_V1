/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eazmir <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 09:34:41 by eazmir            #+#    #+#             */
/*   Updated: 2025/06/01 18:55:29 by eazmir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../include/minishell.h"

#define GREEN   "\033[1;32m"
#define RESET   "\033[0m"

void check_redirection(t_cmd *cmd, const char *token)
{
    if (strcmp(token, ">") == 0)
        cmd->append = 0;
    else if (strcmp(token, ">>") == 0)
        cmd->append = 1;
}

int	open_file_to_red(t_cmd *cmd)
{
	int fd = 0;
	
	if (cmd->outfile)
	{
		if (cmd->append == 0)
			fd = open(cmd->args[1],O_CREAT | O_WRONLY | O_TRUNC,644);
		else
			fd = open(cmd->args[1], O_CREAT | O_APPEND | O_WRONLY ,644);
	}
	return (fd);
	
}
void	redirection(t_cmd *cmd)
{
	int fd;
	fd = open_file_to_red(cmd);
	dup2(fd,STDOUT_FILENO);
}

int	ft_exec(t_cmd *cmd,char **env)
{
	t_cmd	*tmp;
	int	var;
	int	status;
	int	i;
	int	fdpipe[2];
	pid_t	pids;

	tmp = cmd;
	var = -1;
	i = 0;
	while (tmp)
	{
		if (tmp->next)
			pipe(fdpipe);
		pids = fork();
		if (pids == 0)
		{
			if (var != -1)
			{
				dup2(var,STDIN_FILENO);
				close(var);
			}
			if (tmp->next)
			{
				dup2(fdpipe[1],STDOUT_FILENO);
				close(fdpipe[0]);
			}
			if (cmd->outfile)
				redirection(cmd);
			exec(tmp->args[0],env);
		}
		else
		{
			if (var != -1)
				close(var);
			close(fdpipe[1]);
		}
		var = fdpipe[0];
		tmp = tmp->next;
	}
	waitpid(pids,&status,0);
	while (wait(NULL) > 0);
	return (status);
}

char **split_input(char *token)
{
	char **split;
	char **ptr;
	int i;
	split = ft_split(token,' ');
	i = 0;
	while (split[i])
		i++;
	ptr = malloc((i + 1) * sizeof(char));
	i = 0;
	while (split[i])
	{
		ptr[i] = ft_strdup(split[i]);
		i++;
	}
	ptr[i] = NULL;
	return (ptr);
}

int main(int argc,char **argv,char **env)
{
	(void)argc;
	(void)argv;
	

	t_cmd *cmd;
	char *input;
	char **args;
	cmd = malloc(sizeof(t_cmd));
	t_shell *shell = NULL;
	add_node(&shell, env, NULL );
	while (1)
	{
		input = readline(GREEN"$> "RESET);
		if (!input)
			break;
		if (*input)
			add_history(input);
		check_redirection(cmd, input);
		args = split_input(input);
       		if (args[0] && strcmp(args[0], "export") == 0)
			ft_export(&shell,env,args);
		else if (args[0] && strcmp(args[0],"unset") == 0)
			unset(&shell,args);
		else if (args[0] && strcmp(args[0],"env") == 0)
			ft_env(&shell,args);
		else if (args[0] && strcmp(args[0],"cd") == 0)
			cd(&shell,args);
		else if (args[0] && strcmp(args[0],"pwd") == 0)
			pwd(args);
		else if (args[0] && strcmp(args[0],"exit") == 0)
			ft_exit(args);
		else
		{
			cmd = parse_commands(input);
			print_cmd_list(cmd);
			if (cmd)
				ft_exec(cmd,env);
		}
	}
}
