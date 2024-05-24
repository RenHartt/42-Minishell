/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgoron <bgoron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 14:23:11 by bgoron            #+#    #+#             */
/*   Updated: 2024/04/06 17:44:27 by bgoron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

extern int	g_exit_code;

static int	format_nbrlen(char *str)
{
	int	i;

	i = 0;
	while (ft_is_white_space(str[i]))
		str++;
	if (str[i] == '+')
		str++;
	if (str[i] == '-')
		i++;
	while (str[i] == '0')
		str++;
	if (!str[i])
		return (1);
	while (str[i] && ft_isdigit(str[i]))
		i++;
	return (i);
}

static char	*format_nbr(char *str)
{
	int		i;
	int		j;
	char	*new;

	i = 0;
	j = 0;
	new = malloc(sizeof(char) * (format_nbrlen(str) + 1));
	if (!new)
		return (NULL);
	while (ft_is_white_space(str[i]))
		i++;
	i += (str[i] == '+');
	if (str[i] == '-')
		new[j++] = str[i++];
	while (str[i] == '0')
		i++;
	if (!str[i])
	{
		free(new);
		return (ft_strdup("0"));
	}
	while (str[i] && ft_isdigit(str[i]))
		new[j++] = str[i++];
	new[j] = '\0';
	return (new);
}

int	is_number(char *str)
{
	long long	nb;
	char		*new;
	char		*tmp;

	tmp = str;
	while (ft_is_white_space(*tmp))
		tmp++;
	tmp += (*tmp == '-' || *tmp == '+');
	while (ft_isdigit(*tmp) && *tmp)
		tmp++;
	if (*tmp)
		return (0);
	new = format_nbr(str);
	if (!new || !*new)
	{
		free(new);
		return (0);
	}
	nb = ft_atoelodie(new);
	free(new);
	if ((ft_longlonglen(nb)) != format_nbrlen(str))
		return (0);
	return (1);
}

static void	exit_no_arg(t_cmd *cmd)
{
	clear_and_free(cmd);
	exit(g_exit_code);
}

void	ft_exit(t_cmd *cmd)
{
	if (cmd->outfile > 2)
		close(cmd->outfile);
	if (!cmd->cmd[1])
		exit_no_arg(cmd);
	else if (!is_number(cmd->cmd[1]))
	{
		g_exit_code = 2;
		ft_putstr_fd("exit\nminishell: exit: ", STDERR_FILENO);
		ft_putstr_fd(cmd->cmd[1], STDERR_FILENO);
		ft_putendl_fd(": numeric argument required", STDERR_FILENO);
		clear_and_free(cmd);
		exit(g_exit_code);
	}
	else if (cmd->cmd[1] && cmd->cmd[2])
	{
		g_exit_code = 1;
		ft_putendl_fd("exit\nminishell: exit: too many arguments", \
		STDERR_FILENO);
	}
	else if (is_number(cmd->cmd[1]))
	{
		g_exit_code = (int)(ft_atoelodie(cmd->cmd[1]) % 256);
		clear_and_free(cmd);
		exit(g_exit_code);
	}
}
