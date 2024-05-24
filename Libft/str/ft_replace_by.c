/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_replace_by.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgoron <bgoron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 15:29:54 by bgoron            #+#    #+#             */
/*   Updated: 2024/03/12 23:43:20 by bgoron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_replace_by(char **str, char *supp, char *add, int f)
{
	char	*new;
	char	*first;
	char	*last;

	new = NULL;
	first = ft_strndup(*str, ft_strnstr(*str, supp, ft_strlen(*str)) - *str);
	if (!first)
		first = ft_strdup("");
	*str += ft_strlen(first) + ft_strlen(supp);
	last = ft_strdup(*str);
	new = ft_strjoin(new, first, 0b11);
	new = ft_strjoin(new, add, 0b11);
	new = ft_strjoin(new, last, 0b11);
	if (f & 0b10)
		free(*str);
	if (f & 0b01)
		free(supp);
	return (new);
}
