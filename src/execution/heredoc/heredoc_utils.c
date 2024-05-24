/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgoron <bgoron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 13:07:05 by bgoron            #+#    #+#             */
/*   Updated: 2024/04/05 16:17:15 by bgoron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

static int	ft_abs(int nb)
{
	if (nb < 0)
		return (-nb);
	return (nb);
}

static char	random_c(char *file)
{
	int	i;

	i = ft_abs(file[0] % 52);
	if (i < 26)
		return (i + 65);
	return (i + 71);
}

char	*ft_random(int size, char *file)
{
	int	i;
	int	fd;

	i = 0;
	fd = open("/dev/random", O_RDONLY);
	if (fd == -1)
		return (NULL);
	file[0] = '.';
	read(fd, file + 1, size);
	while (++i < size)
		file[i] = random_c(file + i);
	file[i] = '\0';
	close(fd);
	return (file);
}
