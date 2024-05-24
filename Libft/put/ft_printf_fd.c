/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgoron <bgoron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 13:16:54 by bgoron            #+#    #+#             */
/*   Updated: 2024/03/28 13:17:55 by bgoron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_printf_fd(int fd, char *str, ...)
{
	va_list	ap;
	int		i;

	i = 0;
	va_start(ap, str);
	while (str[i])
	{
		if (str[i] == '%')
		{
			i++;
			if (str[i] == 'd')
				ft_putnbr_fd(va_arg(ap, int), fd);
			else if (str[i] == 's')
				ft_putstr_fd(va_arg(ap, char *), fd);
			else if (str[i] == 'c')
				ft_putchar_fd(va_arg(ap, int), fd);
		}
		else
			ft_putchar_fd(str[i], fd);
		i++;
	}
	va_end(ap);
}
