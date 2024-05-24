/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_shrink_str.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgoron <bgoron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 12:32:01 by bgoron            #+#    #+#             */
/*   Updated: 2024/03/12 23:43:20 by bgoron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_shrink_str(char *str, int index, int len)
{
	char	*tmp;
	char	*tmp2;

	tmp = ft_strndup(str, index);
	tmp2 = ft_strdup(str + index + len);
	free(str);
	str = ft_strjoin(tmp, tmp2, 3);
	return (str);
}
