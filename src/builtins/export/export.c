/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eazmir <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 13:38:08 by eazmir            #+#    #+#             **   Updated: 2025/05/26 15:46:00 by eazmir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void ft_export(t_shell **shell,char **env,t_cmd *cmd)
{
	// int	i;
	// char	*plus;
	// char	*equal;
	// char	**cleaned;
	(void)env;
	if (!cmd->args[0])
		return;
	if (!cmd->args[1])
	{
		printList(shell);
		return ;
	}
	if(is_valid_export_syntax(cmd->args[1]) != 0)
		return;
	add_node(shell,NULL,cmd->args[1]);
	// cleaned = clean_str(cmd->args[1]);
	// i = 0;
	// while (cleaned[i])
	// {
	// 	plus = ft_strchr(cmd->args[i],'+');
	// 	equal = ft_strchr(cmd->args[i],'=');
	// 	if (plus && equal)
	// 	{
	// 		if (plus + 1 == equal)
	// 			join_key(shell,cleaned[i]);
	// 		else
	// 			add_node(shell,env,cleaned[i]);
	// 	}
	// 	else
	// 	{
	// 		add_node(shell,env,cleaned[i]);
	// 		printf("am here\n");
	// 	}
			
	// 	i++;
	// }
}




























