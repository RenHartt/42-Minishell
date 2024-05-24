/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgoron <bgoron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 08:55:20 by bgoron            #+#    #+#             */
/*   Updated: 2024/04/06 13:31:11 by bgoron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

extern int	g_exit_code;

char	**char_to_tab(char *str)
{
	char	**tab;

	tab = malloc(sizeof(char *) * 2);
	if (!tab)
		return (NULL);
	tab[0] = ft_strdup(str);
	tab[1] = NULL;
	free(str);
	return (tab);
}

int	is_valid_name(char *name)
{
	if (!name || !*name || !(*name == '_' || ft_isalpha(*name)))
		return (0);
	name += (*name == '_' || ft_isalpha(*name));
	while (*name && (*name == '_' || ft_isalnum(*name)))
		name++;
	return (!*name);
}

void	init_export_arg(char *cmd, char **name, char **type, char **value)
{
	*name = ft_strndup(cmd, ft_strcspn(cmd, "+="));
	if (!*name)
		*name = ft_strdup("");
	if (ft_strnstr(cmd, "+=", ft_strlen(cmd)))
		*type = ft_strdup("+=");
	else if (ft_strnstr(cmd, "=", ft_strlen(cmd)))
		*type = ft_strdup("=");
	else
		*type = ft_strdup("");
	*value = ft_strdup(cmd + ft_strlen(*name) + ft_strlen(*type));
	if (!*value)
		*value = ft_strdup("");
}

void	sort_env(t_env *env)
{
	t_env	*tmp;
	t_env	*tmp2;
	char	*name;
	char	**value;

	tmp = env;
	while (tmp)
	{
		tmp2 = tmp->next;
		while (tmp2)
		{
			if (ft_strncmp(tmp->name, tmp2->name, \
			ft_strlen(tmp->name) + 1) > 0)
			{
				name = tmp->name;
				value = tmp->value;
				tmp->name = tmp2->name;
				tmp->value = tmp2->value;
				tmp2->name = name;
				tmp2->value = value;
			}
			tmp2 = tmp2->next;
		}
		tmp = tmp->next;
	}
}

void	exit_export(char *name, char *type, char *value)
{
	g_exit_code = 1;
	ft_printf_fd(STDERR_FILENO, \
	"minishell: export: `%s': not a valid identifier\n", name);
	free(name);
	free(type);
	free(value);
}
