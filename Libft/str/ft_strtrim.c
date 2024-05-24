/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgoron <bgoron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 21:10:32 by bgoron            #+#    #+#             */
/*   Updated: 2024/03/12 23:43:20 by bgoron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isinset(char c, const char *set)
{
	size_t	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*dst;
	size_t	i;

	if (s1 == NULL)
		return (NULL);
	while (ft_isinset(*s1, set) == 1 && *s1)
		s1++;
	i = ft_strlen(s1) - 1;
	while (ft_isinset(s1[i], set) == 1 && (long long) i >= 0)
		i--;
	dst = ft_calloc(i + 2, sizeof(char));
	if (!dst)
		return (NULL);
	ft_strlcpy(dst, s1, i + 2);
	return (dst);
}
