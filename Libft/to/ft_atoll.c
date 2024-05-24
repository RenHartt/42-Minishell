/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoll.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgoron <bgoron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 20:07:49 by bgoron            #+#    #+#             */
/*   Updated: 2024/04/05 15:55:12 by bgoron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_elodie	ft_atoelodie(char *str)
{
	t_elodie	i;
	t_elodie	nb;
	t_elodie	neg;

	i = 0;
	nb = 0;
	neg = 1;
	while (ft_is_white_space(str[i]))
		i++;
	if (str[i] == '-')
		neg = -1;
	i += (str[i] == '+' || str[i] == '-');
	if (str[i] == '\0')
		return (0);
	while (str[i] != '\0' && str[i] >= '0' && str[i] <= '9')
		nb = nb * 10 + (str[i++] - 48);
	return (nb * neg);
}
