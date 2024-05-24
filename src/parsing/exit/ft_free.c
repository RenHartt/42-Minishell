/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgoron <bgoron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 11:10:29 by bgoron            #+#    #+#             */
/*   Updated: 2024/04/02 20:42:20 by bgoron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

void	free_token(t_token *token)
{
	t_token	*next;

	next = NULL;
	if (!token)
		return ;
	while (token)
	{
		next = token->next;
		free(token);
		token = next;
	}
}

void	free_token_content(t_token *token)
{
	t_token	*next;

	next = NULL;
	if (!token)
		return ;
	while (token)
	{
		next = token->next;
		if (token->content && token->type == COMMAND)
			free(token->content);
		free(token);
		token = next;
	}
}

void	free_env(t_env *env)
{
	t_env	*next;

	next = NULL;
	if (!env)
		return ;
	while (env)
	{
		next = env->next;
		free(env->name);
		ft_free_tab((void **)env->value);
		free(env);
		env = next;
	}
}

void	free_redir(t_redir *redir)
{
	t_redir	*next;

	next = NULL;
	if (!redir)
		return ;
	while (redir)
	{
		next = redir->next;
		free(redir->file);
		free(redir);
		redir = next;
	}
}

void	free_cmd(t_cmd *cmd)
{
	t_cmd	*next;

	next = NULL;
	if (!cmd)
		return ;
	while (cmd)
	{
		next = cmd->next;
		if (cmd->heredoc_file > 2)
			close(cmd->heredoc_file);
		if (cmd->cmd)
			ft_free_tab((void **)cmd->cmd);
		free_redir(cmd->redir);
		free(cmd->path);
		free(cmd);
		cmd = next;
	}
}
