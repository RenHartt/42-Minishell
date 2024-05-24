/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgoron <bgoron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 21:07:09 by bgoron            #+#    #+#             */
/*   Updated: 2024/04/05 16:23:50 by bgoron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

extern int	g_exit_code;

void	dup_close(t_cmd *cmd)
{
	if (cmd->infile != STDIN_FILENO && cmd->infile != -1)
	{
		dup2(cmd->infile, STDIN_FILENO);
		close(cmd->infile);
	}
	if (cmd->outfile != STDOUT_FILENO && cmd->outfile != -1)
	{
		dup2(cmd->outfile, STDOUT_FILENO);
		close(cmd->outfile);
	}
	if (cmd->next && cmd->outfile == STDOUT_FILENO)
		dup2(cmd->fd[1], STDOUT_FILENO);
	if (cmd->prev && cmd->infile == STDIN_FILENO)
		dup2(cmd->prev->fd[0], STDIN_FILENO);
	if (cmd->prev)
		close(cmd->prev->fd[0]);
	close(cmd->fd[0]);
	close(cmd->fd[1]);
}

static void	exec(t_cmd *cmd, char **env)
{
	if (cmd && !cmd->empty)
	{
		dup_close(cmd);
		if (cmd->cmd && is_builtin(cmd->cmd[0]))
			exec_builtin(cmd, 1);
		else
		{
			manage_wrong_redir(cmd);
			manage_wrong_cmd(cmd);
			env = env_string(*cmd->env);
			if (cmd->path && cmd->cmd)
				execve(cmd->path, cmd->cmd, env);
			else if (cmd->cmd)
				execve(cmd->cmd[0], cmd->cmd, env);
			if (cmd->prev)
				close(cmd->prev->fd[0]);
			close(cmd->fd[0]);
			close(cmd->fd[1]);
			clear_and_free(cmd);
			ft_free_tab((void *)env);
			exit(g_exit_code);
		}
		clear_and_free(cmd);
		exit(g_exit_code);
	}
}

static void	ft_pipe(t_cmd *tmp, t_cmd *cmd, pid_t *pid, int *i)
{
	char	**env;

	env = NULL;
	while (tmp)
	{
		pipe(tmp->fd);
		if (cmd && !cmd->empty)
			manage_redir(tmp);
		pid[*i] = fork();
		if (!pid[(*i)++])
			exec(tmp, env);
		close_fd(tmp);
		tmp = tmp->next;
	}
}

static void	check_sigint(int status)
{
	if (WCOREDUMP(status))
		put_error("Quit (core dumped)", 128 + WTERMSIG(status));
	if (WIFSIGNALED(status) && WTERMSIG(status) == 2)
	{
		ft_printf_fd(STDERR_FILENO, "\n");
		g_exit_code = 130;
	}
}

void	exec_line(t_cmd *cmd)
{
	t_cmd	*tmp;
	pid_t	pid[1024];
	t_exe	exe;

	if (cmd && cmd->cmd && !cmd->next && is_builtin(cmd->cmd[0]))
		exec_builtin(cmd, 0);
	else
	{
		exe = (t_exe){0, 0, 0};
		tmp = cmd;
		if (!tmp)
			return ;
		ft_pipe(tmp, cmd, pid, &exe.i);
		rl_catch_signals = 0;
		signal(SIGINT, ignore_sigint);
		while (exe.i--)
		{
			waitpid(pid[exe.i], &exe.status, 0);
			if (!exe.first++)
				g_exit_code = WEXITSTATUS(exe.status);
		}
		check_sigint(exe.status);
		signal(SIGINT, signal_handler);
		close(last_cmd(cmd)->fd[0]);
	}
}
