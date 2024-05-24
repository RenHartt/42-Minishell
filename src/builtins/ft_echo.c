/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgoron <bgoron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 14:23:01 by bgoron            #+#    #+#             */
/*   Updated: 2024/03/29 17:49:14 by bgoron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

static int	is_nflag(char *str)
{
	str += (*str == '-');
	while (*str == 'n')
		str++;
	if (!*str)
		return (1);
	return (0);
}

void	ft_echo(t_cmd *cmd)
{
	int	i;
	int	n;

	i = 1;
	n = 0;
	while (cmd->cmd[i] && is_nflag(cmd->cmd[i]))
	{
		n = 1;
		i++;
	}
	while (cmd->cmd[i])
	{
		ft_putstr_fd(cmd->cmd[i], cmd->outfile);
		if (cmd->cmd[i + 1])
			ft_putchar_fd(' ', cmd->outfile);
		i++;
	}
	if (!n)
		ft_putchar_fd('\n', cmd->outfile);
}
