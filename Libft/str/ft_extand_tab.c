/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_extand_tab.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgoron <bgoron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 17:29:55 by bgoron            #+#    #+#             */
/*   Updated: 2024/03/12 23:43:20 by bgoron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_ctablen(char **tab)
{
	int		i;

	i = 0;
	if (!tab)
		return (0);
	while (tab[i])
		i++;
	return (i);
}

static char	**ft_strtab(char *str)
{
	char	**new;

	new = malloc(sizeof(char *) * (1 + !!str));
	*new = str;
	if (str)
		*(new + 1) = NULL;
	return (new);
}

void	ft_extand_tab(char ***tab, char *add)
{
	char	**new;
	char	**tmp;
	char	**tmp_n;

	if (!tab)
		return ;
	if (!*tab)
	{
		*tab = ft_strtab(add);
		return ;
	}
	new = malloc((ft_ctablen(*tab) + 2) * sizeof(char *));
	if (!new)
		return ;
	tmp = *tab;
	tmp_n = new;
	while (*tmp)
		*(tmp_n++) = *(tmp++);
	*(tmp_n++) = add;
	*tmp_n = NULL;
	free(*tab);
	*tab = new;
}
