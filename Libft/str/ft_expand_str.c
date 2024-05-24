/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand_str.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgoron <bgoron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 12:26:40 by bgoron            #+#    #+#             */
/*   Updated: 2024/03/12 23:43:20 by bgoron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_expand_str(char *str, char *to_add, int index)
{
	char	*tmp;
	char	*tmp2;

	tmp = ft_strndup(str, index);
	tmp2 = ft_strjoin(tmp, to_add, 3);
	tmp = ft_strdup(str + index + 1);
	free(str);
	str = ft_strjoin(tmp2, tmp, 3);
	return (str);
}
