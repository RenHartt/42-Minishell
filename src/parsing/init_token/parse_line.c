/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgoron <bgoron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 02:14:45 by bgoron            #+#    #+#             */
/*   Updated: 2024/03/31 16:17:43 by bgoron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

void	init_token(t_token **token, char *line, char *word, t_quote quote)
{
	while (*line)
	{
		while (*line && ft_is_white_space(*line))
			quote = quote_state(line++, quote);
		if (!*line)
			break ;
		quote = quote_state(line, quote);
		if (quote == NO_QUOTE)
		{
			if (*line && !ft_strncmp(line, "<<", 2))
				heredoc_token(token, &line);
			else if (*line && !ft_strncmp(line, ">>", 2))
				append_token(token, &line);
			else if (*line == '|')
				add_token(token, new_token("|", PIPE));
			else if (*line == '<')
				add_token(token, new_token("<", REDIR_IN));
			else if (*line == '>')
				add_token(token, new_token(">", REDIR_OUT));
		}
		word_token(token, &line, word, &quote);
		quote = quote_state(line++, quote);
	}
	free(word);
}

void	del_useless_quote(char **str, t_quote quote)
{
	char	*tmp;
	t_quote	tmp_quote;

	if (!str || !*str)
		return ;
	tmp = *str;
	while (*tmp)
	{
		tmp_quote = quote;
		quote = quote_state(tmp, quote);
		if (quote != tmp_quote)
			ft_memmove(tmp, tmp + 1, ft_strlen(tmp));
		else
			tmp++;
	}
}

static t_token	*del_token(t_token **token, t_token *tmp)
{
	t_token	*save;

	if (!tmp)
		return (NULL);
	if (tmp->next)
		save = tmp->next;
	else if (tmp->prev)
		save = tmp->prev;
	else
		save = NULL;
	if (tmp->prev)
		tmp->prev->next = tmp->next;
	if (tmp->next)
		tmp->next->prev = tmp->prev;
	if (*token == tmp)
		*token = tmp->next;
	free(tmp->content);
	free(tmp);
	return (save);
}

static void	format_tokens(t_token **token, t_env *env, t_quote quote)
{
	t_token	*tmp;

	tmp = *token;
	while (tmp)
	{
		if (tmp->type == COMMAND)
		{
			replace_vars(&(tmp->content), env, quote);
			if (!*tmp->content)
			{
				tmp = del_token(token, tmp);
				continue ;
			}
			else
				del_useless_quote(&(tmp->content), quote);
		}
		if (tmp)
			tmp = tmp->next;
	}
}

t_token	*parse_line(char **line, t_env *env)
{
	t_token	*token;
	char	*word;

	token = NULL;
	word = NULL;
	if (check_quote(*line, NO_QUOTE))
		return (NULL);
	init_token(&token, *line, word, NO_QUOTE);
	if (check_token(token))
	{
		if (check_heredoc(token))
		{
			free_token_content(token);
			free(*line);
			exit_minishell(env);
		}
		free_token_content(token);
		return (NULL);
	}
	format_tokens(&token, env, NO_QUOTE);
	free(*line);
	return (token);
}
