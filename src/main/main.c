/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgoron <bgoron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 13:44:57 by bgoron            #+#    #+#             */
/*   Updated: 2024/04/05 16:23:25 by bgoron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

extern int	g_exit_code;

int	main(int __attribute__((unused))argc, \
char __attribute__((unused))**argv, char **envp)
{
	t_data	data;
	char	*line;
	char	*prompt;

	init_shell(envp, &(data.env));
	while (1)
	{
		prompt = get_prompt();
		line = readline(prompt);
		free(prompt);
		if (line && *line)
			add_history(line);
		if (!line)
			exit_minishell(data.env);
		data.token = parse_line(&line, data.env);
		data.cmd = init_cmd(data.token, &(data.env));
		if (!handle_heredoc(data.token, data.cmd))
		{
			free_token(data.token);
			exec_line(data.cmd);
		}
		else
			free_token(data.token);
		free_cmd(data.cmd);
	}
}
