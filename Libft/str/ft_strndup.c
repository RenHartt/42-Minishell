/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgoron <bgoron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 22:25:22 by bgoron            #+#    #+#             */
/*   Updated: 2024/03/12 23:43:20 by bgoron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(char *s1, size_t n)
{
	char	*dup;
	size_t	i;

	if (!s1 || !n)
		return (NULL);
	i = -1;
	if (n > ft_strlen(s1))
		n = ft_strlen(s1);
	dup = malloc(sizeof(char) * (n + 1));
	if (!dup)
		return (NULL);
	while (s1[++i] && i < n)
		dup[i] = s1[i];
	dup[i] = '\0';
	return (dup);
}
