/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eazmir <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 09:34:41 by eazmir            #+#    #+#             */
/*   Updated: 2025/06/23 15:40:12 by eazmir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../include/minishell.h"

t_cmd *create_commands(char **tokens)
{
    t_cmd *node = malloc(sizeof(t_cmd));
    if (!node)
        return NULL;
        
    // Count non-redirection arguments
    int arg_count = 0;
    int i = 0;
    
    while (tokens[i])
    {
        if (is_redir(tokens[i]))
        {
            i += 2;
            continue;
        }
        arg_count++;
        i++;
    }
    
    // Allocate args array
    node->args = malloc(sizeof(char *) * (arg_count + 1));
    if (!node->args) 
    {
        free(node);
        return NULL;
    }
    i = 0;
    int j = 0;
    while (tokens[i]) 
    {
        if (is_redir(tokens[i])) 
        {
            i += 2;
            continue;
        }
        node->args[j++] = ft_strdup(tokens[i++]);
    }
    node->args[j] = NULL;
    node->append = 0;
    node->outfile = NULL;
    node->infile = NULL;
    node->next = NULL;
    return node;
}

void print_command(t_cmd *cmd)
{
    if (!cmd || !cmd->args)
        return;
        
    printf("Command: ");
    for (int i = 0; cmd->args[i]; i++)
        printf("%s ", cmd->args[i]);
    printf("\n");
    
    if (cmd->infile)
        printf("Input redirection: < %s\n", cmd->infile);
    if (cmd->outfile)
    {
        printf("Output redirection: %s %s\n",cmd->append ? ">>" : ">", cmd->outfile);
    }
}

int main(int argc, char **argv, char **env)
{
    (void)argc;
    (void)argv;
    
    
    
    // Test case with multiple output redirections
    char *tokens[] = {"cat","<","file",">","outfile",NULL};
    
    t_cmd *cmd = create_commands(tokens);
    t_context *ctx = malloc(sizeof(t_context));
    // ctx = malloc(sizeof(t_context));
    ctx->env = env;
    if (!cmd)
    {
        printf("Failed to create command\n");
        return 1;
    }
    // Handle redirections BEFORE printing so they show up correctly
    handle_redir(cmd, tokens);
    print_command(cmd);
    
    
    
    // Apply redirections before executing
    // redirection(cmd);
    
    // int result=
    printf("hmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm\n");
    int status =  execute_commands(cmd,ctx);


    //free_command(cmd); 
    printf("Command executed with status: %d\n", status);
    
    return 0;
}