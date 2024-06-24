/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maemaldo <maemaldo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 12:35:28 by maemaldo          #+#    #+#             */
/*   Updated: 2024/05/30 14:16:29 by maemaldo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	ft_min(int a, int b)
{
	if (a > b)
		return (b);
	return (a);
}

size_t	ft_strlennl(char *s)
{
	int	i;

	i = 0;
	while (s && s[i] && s[i] != '\n')
		i++;
	return (i);
}

int	ft_countchr(char *s, char c)
{
	int	i;
	int	n;

	i = 0;
	n = 0;
	while (s && s[i])
	{
		if (s[i] == c)
			n++;
		i++;
	}
	return (n);
}

char	**ft_doubletabdup(char **tab, int size)
{
	char	**dest;
	int		i;
	int		j;

	dest = malloc(size * sizeof(char *));
	if (!dest)
		return (NULL);
	i = 0;
	while (i < size)
	{
		j = 0;
		dest[i] = malloc(ft_strlen(tab[i]) + 1 * sizeof(char));
		if (!dest[i])
			return (ft_freetab(dest, i), NULL);
		while (tab[i][j])
		{
			dest[i][j] = tab[i][j];
			j++;
		}
		dest[i][j] = '\0';
		i++;
	}
	return (dest);
}
