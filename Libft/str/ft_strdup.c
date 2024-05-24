/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgoron <bgoron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 16:13:55 by bgoron            #+#    #+#             */
/*   Updated: 2024/03/12 23:43:20 by bgoron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(char *s)
{
	char	*tab;
	int		i;

	if (!s)
		return (NULL);
	i = -1;
	tab = ft_calloc(sizeof(char), (ft_strlen(s) + 1));
	if (!tab)
		return (NULL);
	while (s[++i])
		tab[i] = s[i];
	tab[i] = '\0';
	return (tab);
}
