/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgoron <bgoron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 08:42:35 by bgoron            #+#    #+#             */
/*   Updated: 2024/03/12 23:43:20 by bgoron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	size_dst;
	size_t	fullsize;

	if (size == 0 && dst == NULL)
		return (0);
	size_dst = ft_strlen(dst);
	i = 0;
	while (dst[i] && i < size)
		i++;
	fullsize = ft_strlen(src) + i;
	i = 0;
	while (src[i] && size_dst + 1 < size)
	{
		dst[size_dst] = src[i];
		i++;
		size_dst++;
	}
	dst[size_dst] = '\0';
	return (fullsize);
}
