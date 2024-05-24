/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_minishell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgoron <bgoron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 13:26:27 by bgoron            #+#    #+#             */
/*   Updated: 2024/04/01 20:22:20 by bgoron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

extern int	g_exit_code;

int	put_error(char *str, int exit_code)
{
	g_exit_code = exit_code;
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putendl_fd(str, STDERR_FILENO);
	return (1);
}

void	clear_and_free(t_cmd *cmd)
{
	rl_clear_history();
	free_env(*cmd->env);
	free_cmd(first_cmd(cmd));
}

void	exit_minishell(t_env *env)
{
	rl_clear_history();
	free_env(env);
	ft_putendl_fd("exit", STDOUT_FILENO);
	exit(g_exit_code);
}

void	exit_minishell_error(t_cmd *cmd)
{
	rl_clear_history();
	if (cmd->prev)
		close(cmd->prev->fd[0]);
	close(cmd->fd[0]);
	close(cmd->fd[1]);
	free_env(*cmd->env);
	free_cmd(first_cmd(cmd));
	exit(g_exit_code);
}
