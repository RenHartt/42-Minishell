/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgoron <bgoron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 14:23:26 by bgoron            #+#    #+#             */
/*   Updated: 2024/03/31 20:07:23 by bgoron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

extern int	g_exit_code;

static int	ft_unsetenv(char *name, t_env **env)
{
	t_env	*tmp;
	t_env	*prev;

	prev = NULL;
	tmp = *env;
	while (tmp)
	{
		if (!ft_strncmp(name, tmp->name, ft_strlen(name) + 1))
		{
			if (prev)
				prev->next = tmp->next;
			else
				*env = tmp->next;
			free(tmp->name);
			if (tmp->value)
				ft_free_tab((void *)tmp->value);
			free(tmp);
			return (0);
		}
		prev = tmp;
		tmp = tmp->next;
	}
	return (-1);
}

void	ft_unset(t_cmd *cmd)
{
	int	i;

	i = 1;
	while (cmd->cmd[i])
	{
		if (ft_unsetenv(cmd->cmd[i], cmd->env) == -1)
			break ;
		i++;
	}
}
