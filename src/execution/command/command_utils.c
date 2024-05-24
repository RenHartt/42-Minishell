/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgoron <bgoron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 17:49:54 by bgoron            #+#    #+#             */
/*   Updated: 2024/04/06 17:43:16 by bgoron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

extern int	g_exit_code;

void	parse_token(t_cmd **tmp, t_token **token)
{
	(*tmp)->empty = 0;
	while (*token && (*token)->type != PIPE)
	{
		if ((*token)->type == REDIR_IN || (*token)->type == REDIR_OUT || \
			(*token)->type == APPEND || (*token)->type == HERE_DOC)
		{
			add_redir(&(*tmp)->redir, \
			new_redir((*token)->type, (*token)->next->content));
			*token = (*token)->next;
		}
		else if ((*token)->type == COMMAND)
			ft_extand_tab(&(*tmp)->cmd, (*token)->content);
		*token = (*token)->next;
	}
}

void	add_cmd_and_next(t_cmd **tmp, t_token **token, t_env **env)
{
	if (*token)
	{
		*token = (*token)->next;
		add_cmd(&(*tmp), new_cmd(env));
	}
}

static void	print_error(char *str, char *file, int exit_code, t_cmd *cmd)
{
	ft_printf_fd(STDERR_FILENO, str, file);
	g_exit_code = exit_code;
	exit_minishell_error(cmd);
}

void	manage_wrong_redir(t_cmd *cmd)
{
	t_redir	*redir;

	redir = cmd->redir;
	while (redir)
	{
		if (redir->type == REDIR_IN && access(redir->file, F_OK) == -1)
			print_error(NO_FILE, redir->file, 1, cmd);
		else if (redir->type == REDIR_IN && access(redir->file, R_OK) == -1)
			print_error(NO_PERM, redir->file, 1, cmd);
		else if (redir->type == REDIR_OUT && !access(redir->file, F_OK))
		{
			if (access(redir->file, W_OK) == -1)
				print_error(NO_PERM, redir->file, 1, cmd);
		}
		else if (redir->type == APPEND && !access(redir->file, F_OK))
		{
			if (access(redir->file, W_OK) == -1)
				print_error(NO_PERM, redir->file, 1, cmd);
		}
		redir = redir->next;
	}
}

void	manage_wrong_cmd(t_cmd *cmd)
{
	struct stat	buf;

	ft_memset(&buf, 0, sizeof(struct stat));
	if (!cmd->cmd || !cmd->cmd[0])
		return ;
	cmd->path = find_path(cmd->cmd[0], *cmd->env);
	if (cmd->path)
		stat(cmd->path, &buf);
	else
		stat(cmd->cmd[0], &buf);
	if (S_ISDIR(buf.st_mode))
		print_error(IS_DIR, cmd->cmd[0], 127, cmd);
	else if (cmd->path && (stat(cmd->path, &buf) == -1) && \
	!S_ISDIR(buf.st_mode))
		print_error(NO_FILE, cmd->cmd[0], 127, cmd);
	else if (cmd->cmd && (!access(cmd->cmd[0], F_OK)) && \
	access(cmd->cmd[0], X_OK) == -1)
		print_error(NO_PERM, cmd->cmd[0], 126, cmd);
	else if (cmd->path && (!access(cmd->path, F_OK)) && \
	access(cmd->path, X_OK) == -1)
		print_error(NO_PERM, cmd->path, 126, cmd);
	else if (access(cmd->cmd[0], F_OK) == -1 && !cmd->path)
		print_error(NO_CMD, cmd->cmd[0], 127, cmd);
}
