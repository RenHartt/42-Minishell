/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgoron <bgoron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 01:21:56 by bgoron            #+#    #+#             */
/*   Updated: 2024/03/23 13:21:03 by bgoron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include "libft.h"

static size_t	lennbr(size_t nb)
{
	size_t	i;

	i = 0;
	while (nb > 0)
	{
		nb /= 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	unsigned char	*dest;
	size_t			len;
	int				sign;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	if (n == 0)
		return (ft_strdup("0"));
	sign = 0;
	if (n < 0)
	{
		n *= -1;
		sign = 1;
	}
	len = lennbr(n);
	dest = ft_calloc((len + 1 + sign), sizeof(char));
	while (n > 0 && dest)
	{
		dest[len - 1 + sign] = (n % 10) + '0';
		n /= 10;
		len--;
	}
	if (sign == 1 && dest)
		dest[0] = '-';
	return ((char *)dest);
}
