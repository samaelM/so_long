/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maemaldo <maemaldo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 17:40:56 by maemaldo          #+#    #+#             */
/*   Updated: 2024/05/29 15:08:44 by maemaldo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_freetab(char **s, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		free(s[i]);
		i++;
	}
	free(s);
}

void	ft_freeandexit(t_map *data)
{
	free(data);
	exit(0);
}

int	*ft_floodfill(char **map, int *c, int i, int j)
{
	if (map[j][i] == 'C')
		c[0]++;
	map[j][i] = 'V';
	if (map[j][i + 1] && (map[j][i + 1] == '0' || map[j][i + 1] == 'C'))
		ft_floodfill(map, c, i + 1, j);
	if (map[j][i - 1] && (map[j][i - 1] == '0' || map[j][i - 1] == 'C'))
		ft_floodfill(map, c, i - 1, j);
	if (map[j + 1][i] && (map[j + 1][i] == '0' || map[j + 1][i] == 'C'))
		ft_floodfill(map, c, i, j + 1);
	if (map[j - 1][i] && (map[j - 1][i] == '0' || map[j - 1][i] == 'C'))
		ft_floodfill(map, c, i, j - 1);
	if ((map[j - 1][i] && map[j - 1][i] == 'E') || (map[j + 1][i] && map[j
			+ 1][i] == 'E'))
		c[1] = 1;
	if ((map[j][i + 1] && map[j][i + 1] == 'E') || (map[j][i - 1] && map[j][i
			- 1] == 'E'))
		c[1] = 1;
	return (c);
}

t_Bool	ft_floodfill_check(char **map, int size, int c)
{
	int	i;
	int	j;
	int	*res;

	res = malloc(2 * sizeof(int));
	if (!res)
		return (False);
	res[0] = 0;
	res[1] = 0;
	j = 0;
	while (j < size)
	{
		i = 0;
		while (map && map[j] && map[j][i])
		{
			if (map[j][i] == 'P')
				ft_floodfill(map, res, i, j);
			i++;
		}
		j++;
	}
	if (c != res[0] || !res[1])
		return (free(res), ft_printerror(ERROR7), False);
	free(res);
	return (True);
}

int	ft_count_line(t_map *tmap, char *path)
{
	int		fd;
	char	*line;
	int		n;

	fd = open(path, O_RDWR);
	if (fd == -1)
	{
		free(tmap);
		exit(ft_printerror(ERROR9));
	}
	n = 0;
	line = get_next_line(fd);
	if (!line)
		n = -1;
	if (ft_strlen(line) > 50)
		return (-1);
	while (line)
	{
		free(line);
		line = get_next_line(fd);
		n++;
	}
	close(fd);
	return (n);
}
