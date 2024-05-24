/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgoron <bgoron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 12:33:25 by bgoron            #+#    #+#             */
/*   Updated: 2024/04/01 20:09:12 by bgoron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

extern int	g_exit_code;

int	is_builtin(char *cmd)
{
	if (!ft_strncmp(cmd, "echo", 5))
		return (1);
	else if (!ft_strncmp(cmd, "cd", 3))
		return (1);
	else if (!ft_strncmp(cmd, "pwd", 4))
		return (1);
	else if (!ft_strncmp(cmd, "export", 7))
		return (1);
	else if (!ft_strncmp(cmd, "unset", 6))
		return (1);
	else if (!ft_strncmp(cmd, "env", 4))
		return (1);
	else if (!ft_strncmp(cmd, "exit", 5))
		return (1);
	return (0);
}

void	manage_wrong_builtin(t_cmd *cmd)
{
	if ((!cmd->cmd \
	|| cmd->infile == -1 \
	|| cmd->outfile == -1))
	{
		rl_clear_history();
		if (cmd->prev)
			close(cmd->prev->fd[0]);
		close(cmd->fd[0]);
		close(cmd->fd[1]);
		free_env(*cmd->env);
		free_cmd(first_cmd(cmd));
		g_exit_code = 1;
		exit(g_exit_code);
	}
}

void	exec_builtin(t_cmd *cmd, int pipe)
{
	manage_wrong_builtin(cmd);
	manage_redir(cmd);
	manage_wrong_redir(cmd);
	if (cmd && cmd->cmd && !ft_strncmp(cmd->cmd[0], "echo", 5))
		ft_echo(cmd);
	else if (cmd && cmd->cmd && !ft_strncmp(cmd->cmd[0], "cd", 3))
		ft_cd(cmd->cmd[1], cmd);
	else if (cmd && cmd->cmd && !ft_strncmp(cmd->cmd[0], "pwd", 4))
		ft_pwd(cmd);
	else if (cmd && cmd->cmd && !ft_strncmp(cmd->cmd[0], "export", 7))
		ft_export(cmd, cmd->env);
	else if (cmd && cmd->cmd && !ft_strncmp(cmd->cmd[0], "unset", 6))
		ft_unset(cmd);
	else if (cmd && cmd->cmd && !ft_strncmp(cmd->cmd[0], "env", 4))
		ft_env(cmd);
	else if (cmd && cmd->cmd && !ft_strncmp(cmd->cmd[0], "exit", 5))
	{
		if (!pipe && ((!cmd->cmd[1]) \
		|| (cmd->cmd[1] && is_number(cmd->cmd[1]) && !cmd->cmd[2])))
			ft_putendl_fd("exit", STDERR_FILENO);
		ft_exit(cmd);
	}
	if (cmd->outfile > 2)
		close(cmd->outfile);
}
