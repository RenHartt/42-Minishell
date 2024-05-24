/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgoron <bgoron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 17:12:58 by bgoron            #+#    #+#             */
/*   Updated: 2024/03/28 15:30:51 by bgoron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

t_env	*new_env(char *name, char **value)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->name = name;
	new->value = value;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

void	add_env(t_env **env, t_env *next)
{
	t_env	*tmp;

	if (!env || !next)
		return ;
	if (!*env)
	{
		*env = next;
		return ;
	}
	tmp = *env;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = next;
	next->prev = tmp;
}

t_env	*parse_env(char **envp)
{
	t_env	*env;
	char	*name;
	char	*tmp;
	char	**value;

	env = NULL;
	while (*envp)
	{
		name = ft_strndup(*envp, ft_strchr(*envp, '=') - *envp);
		tmp = ft_strdup(ft_strchr(*envp, '=') + 1);
		value = ft_split(tmp, ':');
		free(tmp);
		add_env(&env, new_env(name, value));
		envp++;
	}
	return (env);
}
