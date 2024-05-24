/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgoron <bgoron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 14:23:16 by bgoron            #+#    #+#             */
/*   Updated: 2024/04/05 15:44:39 by bgoron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

extern int	g_exit_code;

static void	export_no_arg(t_cmd *cmd, t_env **env)
{
	t_env	*tmp;
	char	*value;

	tmp = *env;
	sort_env(tmp);
	while (tmp)
	{
		value = ft_ctabjoin(tmp->value, ":", 0b00);
		if (value)
			ft_printf_fd(cmd->outfile, \
			"declare -x %s=\"%s\"\n", tmp->name, value);
		else
			ft_printf_fd(cmd->outfile, \
			"declare -x %s\n", tmp->name);
		tmp = tmp->next;
		free(value);
	}
}

static void	export_add_arg(t_env **env, char *name, char *value)
{
	t_env	*tmp;
	int		i;

	i = 0;
	tmp = *env;
	while (tmp)
	{
		if (!ft_strncmp(tmp->name, name, ft_strlen(name) + 1))
		{
			while (tmp->value[i])
				i++;
			i -= (i > 0);
			tmp->value[i] = ft_strjoin(tmp->value[i], value, 0b11);
			return ;
		}
		tmp = tmp->next;
	}
	add_env(env, new_env(ft_strdup(name), char_to_tab(value)));
}

void	export_equal_arg(t_env **env, char *name, char *value)
{
	t_env	*tmp;

	tmp = *env;
	while (tmp)
	{
		if (!ft_strncmp(tmp->name, name, ft_strlen(name) + 1))
		{
			ft_free_tab((void *)tmp->value);
			tmp->value = char_to_tab(value);
			return ;
		}
		tmp = tmp->next;
	}
	add_env(env, new_env(ft_strdup(name), char_to_tab(value)));
}

static void	export_no_value(t_env **env, char *name)
{
	t_env	*tmp;

	tmp = *env;
	while (tmp)
	{
		if (!ft_strncmp(tmp->name, name, ft_strlen(name) + 1))
			return ;
		tmp = tmp->next;
	}
	add_env(env, new_env(ft_strdup(name), NULL));
}

void	ft_export(t_cmd *cmd, t_env **env)
{
	t_export	xpr;

	xpr = (t_export){NULL, NULL, NULL, 1};
	if (!cmd->cmd[1])
	{
		export_no_arg(cmd, env);
		return ;
	}
	while (cmd->cmd[xpr.i])
	{
		init_export_arg(cmd->cmd[xpr.i++], &xpr.name, &xpr.type, &xpr.value);
		if (!is_valid_name(xpr.name))
		{
			exit_export(xpr.name, xpr.type, xpr.value);
			return ;
		}
		if (!ft_strncmp(xpr.type, "+=", 3))
			export_add_arg(env, xpr.name, xpr.value);
		else if (!ft_strncmp(xpr.type, "=", 2))
			export_equal_arg(env, xpr.name, xpr.value);
		else
			export_no_value(env, xpr.name);
		free(xpr.name);
		free(xpr.type);
	}
}
