/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgoron <bgoron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 20:40:30 by bgoron            #+#    #+#             */
/*   Updated: 2024/03/24 13:27:37 by bgoron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

t_cmd	*first_cmd(t_cmd *cmd)
{
	if (!cmd)
		return (NULL);
	while (cmd->prev)
		cmd = cmd->prev;
	return (cmd);
}

int	env_size(t_env *env)
{
	t_env	*tmp;
	int		len;

	tmp = env;
	len = 0;
	while (tmp)
	{
		tmp = tmp->next;
		len++;
	}
	return (len);
}

t_cmd	*last_cmd(t_cmd *cmd)
{
	if (!cmd)
		return (NULL);
	while (cmd->next)
		cmd = cmd->next;
	return (cmd);
}

void	close_fd(t_cmd *tmp)
{
	if (tmp->prev)
		close(tmp->prev->fd[0]);
	close(tmp->fd[1]);
	if (tmp->infile > 2)
		close(tmp->infile);
	if (tmp->outfile > 2)
		close(tmp->outfile);
}

char	**env_string(t_env *env)
{
	t_env	*tmp;
	char	**join_env;
	char	*value;

	tmp = env;
	value = NULL;
	join_env = malloc(sizeof(char *) * (env_size(env) + 1));
	if (!join_env)
		return (NULL);
	while (tmp)
	{
		value = ft_ctabjoin(tmp->value, ft_strdup(":"), 0b01);
		value = ft_strjoin(ft_strdup("="), value, 0b11);
		value = ft_strjoin(tmp->name, value, 0b01);
		*join_env = ft_strdup(value);
		join_env++;
		tmp = tmp->next;
		free(value);
	}
	*join_env = NULL;
	return (join_env - env_size(env));
}
