/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_char.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgoron <bgoron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 19:24:19 by bgoron            #+#    #+#             */
/*   Updated: 2024/03/12 23:43:20 by bgoron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_char(char *s1, char c)
{
	char	*s2;
	int		i;

	i = -1;
	if (!s1)
		return (NULL);
	s2 = ft_calloc(sizeof(char), (ft_strlen(s1) + 2));
	if (s2 == NULL)
		return (NULL);
	while (s1[++i] != '\0')
		s2[i] = s1[i];
	s2[i] = c;
	s2[i + 1] = '\0';
	free(s1);
	return (s2);
}
