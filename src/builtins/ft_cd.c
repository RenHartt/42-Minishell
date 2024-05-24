/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgoron <bgoron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 14:22:55 by bgoron            #+#    #+#             */
/*   Updated: 2024/04/06 17:41:07 by bgoron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

extern int	g_exit_code;

char	*get_env_value(char *name, t_env *env)
{
	while (env)
	{
		if (!ft_strncmp(env->name, name, ft_strlen(name)))
			return (env->value[0]);
		env = env->next;
	}
	return (NULL);
}

static int	check_permission(char *path)
{
	if (access(path, F_OK) == -1)
	{
		g_exit_code = 1;
		ft_printf_fd(STDERR_FILENO, NO_FILE, path);
		return (1);
	}
	else if (chdir(path) == -1)
	{
		g_exit_code = 1;
		ft_printf_fd(STDERR_FILENO, NO_PERM, path);
		return (1);
	}
	return (0);
}

void	ft_cd(char *path, t_cmd *cmd)
{
	char	*oldpwd;
	char	newpwd[1024];

	if (cmd->cmd[0] && cmd->cmd[1] && cmd->cmd[2])
	{
		ft_printf_fd(STDERR_FILENO, "minishell: cd: too many arguments\n");
		g_exit_code = 1;
		return ;
	}
	if (path == NULL)
		path = get_env_value("HOME", *cmd->env);
	else if (!ft_strncmp(path, "-", 1))
	{
		path = get_env_value("OLDPWD", *cmd->env);
		if (path)
			ft_printf_fd(cmd->outfile, "%s\n", path);
		else
			return ;
	}
	if (check_permission(path))
		return ;
	oldpwd = get_env_value("PWD", *cmd->env);
	getcwd(newpwd, 1024);
	export_equal_arg(cmd->env, "OLDPWD", ft_strdup(oldpwd));
	export_equal_arg(cmd->env, "PWD", ft_strdup(newpwd));
}
