/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ctabjoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgoron <bgoron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 17:31:06 by bgoron            #+#    #+#             */
/*   Updated: 2024/04/02 07:19:22 by bgoron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_ctablen(char **tab)
{
	int		i;

	i = 0;
	if (!tab)
		return (0);
	while (tab[i])
		i++;
	return (i);
}

static int	ft_ctabslen(char **tab)
{
	int		i;
	int		len;

	i = 0;
	len = 0;
	if (!tab)
		return (0);
	while (tab[i])
	{
		len += ft_strlen(tab[i]);
		i++;
	}
	return (len);
}

static void	ft_strvcpy(char *dst, char *src)
{
	while (*src)
		*(dst++) = *(src++);
	*dst = '\0';
}

char	*ft_ctabjoin(char **tab, char *sep, int f)
{
	char	*new;
	char	*tmp;

	if (!tab)
		return (ft_strdup(""));
	new = malloc(ft_ctabslen(tab) + ft_ctablen(tab) * ft_strlen(sep) + 1);
	if (!new)
		return (NULL);
	tmp = new;
	while (*tab)
	{
		ft_strvcpy(tmp, *tab);
		tmp += ft_strlen(*tab);
		if (*((tab++) + 1))
		{
			ft_strvcpy(tmp, sep);
			tmp += ft_strlen(sep);
		}
	}
	*tmp = '\0';
	if (f & 0b10)
		ft_free_tab((void **)tab);
	if (f & 0b01)
		free(sep);
	return (new);
}
