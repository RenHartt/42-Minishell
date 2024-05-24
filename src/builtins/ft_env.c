/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgoron <bgoron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 14:23:06 by bgoron            #+#    #+#             */
/*   Updated: 2024/04/05 17:09:35 by bgoron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

void	ft_env(t_cmd *cmd)
{
	t_env	*env;
	char	*value;

	if (cmd->cmd[1])
		put_error("too many arguments", 127);
	env = *cmd->env;
	if (!env || cmd->cmd[1])
		return ;
	while (env)
	{
		if (env->value)
		{
			value = ft_ctabjoin(env->value, ":", 0b00);
			ft_putstr_fd(env->name, cmd->outfile);
			ft_putchar_fd('=', cmd->outfile);
			if (env->value)
				ft_putendl_fd(value, cmd->outfile);
			else
				ft_putstr_fd("NULL", 2);
			free(value);
		}
		env = env->next;
	}
}
