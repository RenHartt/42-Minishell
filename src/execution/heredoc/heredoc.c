/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgoron <bgoron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 15:43:27 by bgoron            #+#    #+#             */
/*   Updated: 2024/04/05 15:52:12 by bgoron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

extern int	g_exit_code;

int	last_is_heredoc(t_redir *redir)
{
	t_redir	*tmp;
	t_type	last;

	tmp = redir;
	last = -1;
	while (tmp)
	{
		if (tmp->type == HERE_DOC || tmp->type == REDIR_IN)
			last = tmp->type;
		tmp = tmp->next;
	}
	return (last == HERE_DOC);
}

static void	write_heredoc(char *limiter, int fd, t_cmd *cmd)
{
	char	*line;

	line = NULL;
	fd = open(cmd->heredoc_name, O_WRONLY | O_CREAT | O_EXCL | O_TRUNC, 0600);
	while (1)
	{
		free(line);
		line = readline("heredoc> ");
		if (!line || (!ft_strncmp(line, limiter, ft_strlen(limiter)) \
		&& !line[ft_strlen(limiter)]))
		{
			if (!g_exit_code)
				ft_printf_fd(STDERR_FILENO, "minishell: warning: here-document \
delimited by end-of-file (wanted `%s')\n", limiter);
			break ;
		}
		replace_vars(&line, *cmd->env, NO_QUOTE);
		ft_putendl_fd(line, fd);
	}
	free(line);
	close(fd);
}

static int	poop(char *limiter, t_cmd *cmd, t_token *token, t_cmd *tmp)
{
	int	fd;

	fd = 0;
	g_exit_code = 0;
	rl_catch_signals = 1;
	signal(SIGINT, heredoc_signal_handler);
	write_heredoc(limiter, fd, tmp);
	clear_and_free(cmd);
	free_token(token);
	return (fd);
}

static int	heredoc(char *limiter, t_token *token, t_cmd *cmd, t_cmd *tmp)
{
	pid_t	pid;
	int		fd;
	int		status;

	fd = 0;
	status = 0;
	ft_random(10, tmp->heredoc_name);
	ignore_handler();
	pid = fork();
	if (!pid)
	{
		fd = poop(limiter, cmd, token, tmp);
		exit(g_exit_code == 130);
	}
	waitpid(pid, &status, 0);
	signal(SIGINT, signal_handler);
	if (WEXITSTATUS(status) == 1)
	{
		g_exit_code = 130;
		unlink(tmp->heredoc_name);
		return (-1);
	}
	fd = open(tmp->heredoc_name, O_RDONLY);
	unlink(tmp->heredoc_name);
	return (fd);
}

int	handle_heredoc(t_token *token, t_cmd *cmd)
{
	t_cmd	*tmp;
	t_redir	*redir_tmp;
	int		fd;

	tmp = cmd;
	while (tmp)
	{
		fd = 0;
		redir_tmp = tmp->redir;
		while (redir_tmp)
		{
			if (redir_tmp->type == HERE_DOC)
			{
				if (fd)
					close(fd);
				fd = heredoc(redir_tmp->file, token, cmd, tmp);
				if (fd == -1)
					return (1);
				tmp->heredoc_file = fd;
			}
			redir_tmp = redir_tmp->next;
		}
		tmp = tmp->next;
	}
	return (0);
}
