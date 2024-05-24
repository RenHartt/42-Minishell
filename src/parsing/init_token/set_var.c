/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgoron <bgoron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 23:51:02 by bgoron            #+#    #+#             */
/*   Updated: 2024/03/30 21:06:18 by bgoron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

extern int	g_exit_code;

char	*get_var(char *name, t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (!ft_strncmp(tmp->name, name + 1, ft_strlen(tmp->name)) && \
		!*(name + ft_strlen(tmp->name) + 1))
			return (ft_ctabjoin(tmp->value, ":", 0b00));
		tmp = tmp->next;
	}
	return (NULL);
}

void	insert_var(char ***new, char *tmp, int *len, t_env *env)
{
	char	*name;
	char	*value;

	if (*(tmp + 1) == '?')
	{
		ft_extand_tab(new, ft_itoa(g_exit_code));
		*len = 2;
		return ;
	}
	if (!is_var_name(tmp, 1))
	{
		ft_extand_tab(new, ft_strdup("$"));
		*len = 1;
		return ;
	}
	*len = (*tmp == '$') + 1;
	while (*(tmp) && is_var_name(tmp, *len))
		(*len)++;
	name = ft_strndup(tmp, *len);
	value = get_var(name, env);
	free(name);
	ft_extand_tab(new, value);
}

void	quoted_skip(char **str, int len, t_quote *quote)
{
	while (**str && len--)
		*quote = quote_state((*str)++, *quote);
}

void	end_replace_vars(char **str, char **new)
{
	free(*str);
	*str = ft_ctabjoin(new, "", 0b00);
	ft_free_tab((void **)new);
}

void	replace_vars(char **str, t_env *env, t_quote quote)
{
	char	*tmp;
	char	**new;
	int		len;

	tmp = *str;
	if (!tmp || !*tmp)
		return ;
	new = NULL;
	while (*tmp)
	{
		len = ft_strcspn(tmp, "$");
		ft_extand_tab(&new, ft_strndup(tmp, len));
		quoted_skip(&tmp, len, &quote);
		if (!*tmp)
			break ;
		if (quote != S_QUOTE)
			insert_var(&new, tmp, &len, env);
		else
		{
			len = ft_strcspn(tmp, "'");
			ft_extand_tab(&new, ft_strndup(tmp, len));
		}
		tmp += len;
	}
	end_replace_vars(str, new);
}
