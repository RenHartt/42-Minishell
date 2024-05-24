/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgoron <bgoron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 15:02:27 by bgoron            #+#    #+#             */
/*   Updated: 2024/03/30 14:23:06 by bgoron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

extern int	g_exit_code;

int	check_pipe(t_token *token)
{
	t_token	*tmp;

	tmp = token;
	if (tmp && (tmp->type == PIPE || last_token(tmp)->type == PIPE))
		return (1);
	while (tmp)
	{
		if (tmp->type == PIPE)
		{
			if (tmp->next->type == PIPE)
				return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

int	check_redir(t_token *token)
{
	t_token	*tmp;

	tmp = token;
	while (tmp)
	{
		if (tmp->type == REDIR_IN || tmp->type == REDIR_OUT \
			||tmp->type == APPEND || tmp->type == HERE_DOC)
		{
			if (!tmp->next)
				return (1);
			if (tmp->next->type != COMMAND)
				return (tmp->next->type);
		}
		tmp = tmp->next;
	}
	return (0);
}

int	check_heredoc(t_token *token)
{
	t_token	*tmp;
	int		count;

	tmp = token;
	count = 0;
	while (tmp)
	{
		if (tmp->type == HERE_DOC)
			count++;
		tmp = tmp->next;
	}
	return (count > 16);
}

int	check_exe_dir(t_token *token)
{
	if (token)
	{
		if (ft_strlen(token->content) == 1 && (token->content[0] == '.'))
			return (1);
	}
	return (0);
}

int	check_token(t_token *token)
{
	int	type;

	type = 0;
	if (check_heredoc(token))
		return (put_error("maximum here-document count exceeded", 2));
	if (check_exe_dir(token))
		return (put_error(".: filename argument required", 2));
	if (check_pipe(token))
		return (put_error("syntax error near unexpected token `|'", 2));
	type = check_redir(token);
	if (type == REDIR_IN)
		return (put_error("syntax error near unexpected token `<'", 2));
	else if (type == REDIR_OUT)
		return (put_error("syntax error near unexpected token `>'", 2));
	else if (type == APPEND)
		return (put_error("syntax error near unexpected token `>>'", 2));
	else if (type == HERE_DOC)
		return (put_error("syntax error near unexpected token `<<'", 2));
	else if (type)
		return (put_error("syntax error near unexpected token `newline'", 2));
	return (0);
}
