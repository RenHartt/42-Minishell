/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgoron <bgoron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 17:24:32 by bgoron            #+#    #+#             */
/*   Updated: 2024/03/12 23:43:20 by bgoron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_countwords(const char *s, char c)
{
	size_t	i;
	size_t	count;

	i = 1;
	count = 0;
	if (!*s)
		return (0);
	if (*s != c)
		count++;
	while (s[i])
	{
		if (s[i - 1] == c && s[i] != c)
			count++;
		i++;
	}
	return (count);
}

static size_t	ft_countletters(const char *s, char c)
{
	size_t	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

static void	*ft_free_char_tab(char **s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		free(s[i]);
		i++;
	}
	free(s);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char	**str;
	int		i;
	int		wcount;
	int		wsize;

	i = -1;
	wsize = 0;
	if (!s)
		return (NULL);
	wcount = ft_countwords(s, c);
	str = ft_calloc((wcount + 1), sizeof(char *));
	if (!str)
		return (NULL);
	while (++i < wcount)
	{
		while (wsize-- > 0 || *s == c)
			s++;
		wsize = ft_countletters(s, c);
		str[i] = ft_calloc((wsize + 1), sizeof(char));
		if (!str[i])
			return (ft_free_char_tab(str));
		ft_strlcpy(str[i], s, wsize + 1);
	}
	str[i] = 0;
	return (str);
}
