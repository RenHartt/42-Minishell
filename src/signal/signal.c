/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgoron <bgoron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 14:03:31 by bgoron            #+#    #+#             */
/*   Updated: 2024/04/06 17:43:36 by bgoron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

extern int	g_exit_code;

void	signal_handler(int signum)
{
	if (signum == 2)
	{
		printf("^C\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		g_exit_code = 130;
	}
}

void	heredoc_signal_handler(int signum)
{
	if (signum == 2)
	{
		printf("\n");
		rl_replace_line("", 0);
		g_exit_code = 130;
		close(0);
	}
}

char	*get_prompt(void)
{
	char	pwd[1024];
	char	*tmp;
	char	*prompt;

	tmp = getcwd(NULL, sizeof(char) * sizeof(pwd));
	ft_strlcpy(pwd, tmp, sizeof(pwd));
	free(tmp);
	prompt = ft_strjoin(pwd, PROMPT, 0);
	rl_set_prompt(prompt);
	return (prompt);
}

void	init_shell(char **envp, t_env **env)
{
	struct termios	new_termios;
	char			*c_nbr;
	int				i_nbr;

	new_termios = (struct termios){0};
	rl_catch_signals = 0;
	tcgetattr(0, &new_termios);
	new_termios.c_lflag = new_termios.c_lflag & (~ECHOCTL);
	tcsetattr(0, 0, &new_termios);
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, signal_handler);
	*env = parse_env(envp);
	c_nbr = get_env_value("SHLVL", *env);
	if (c_nbr)
	{
		i_nbr = ft_atoi(c_nbr);
		i_nbr++;
		c_nbr = ft_itoa(i_nbr);
		export_equal_arg(env, "SHLVL", c_nbr);
	}
	else
		export_equal_arg(env, "SHLVL", ft_strdup("1"));
}
