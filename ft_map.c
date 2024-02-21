/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maemaldo <maemaldo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 16:05:18 by maemaldo          #+#    #+#             */
/*   Updated: 2024/02/20 12:35:00 by maemaldo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

t_Bool	ft_check(t_map *data)
{
	size_t	i;
	char	**temp;

	i = 0;
	if (!ft_check3(data->map[i]))
		return (False);
	while (i < data->size)
	{
		if (!ft_check1(data->map[i]) || !ft_check2(data, data->map[i], False)
			|| !ft_check4(data->map[i]))
			return (False);
		if (data->lenght != ft_strlennl(data->map[i]))
			return (ft_printerror(ERROR0));
		i++;
	}
	if (!ft_check2(data, data->map[i - 1], True) || !ft_check3(data->map[i
				- 1]))
		return (False);
	temp = ft_doubletabdup(data->map, data->size);
	if (!temp)
		return (False);
	if (!ft_floodfill_check(temp, data->size, data->c))
		return (ft_freetab(temp, data->size), False);
	return (ft_freetab(temp, data->size), True);
}

char	**ft_copymap(t_map *tmap, char *path)
{
	char	**map;
	int		nline;
	int		fd;
	int		i;

	nline = ft_count_line(tmap, path);
	if (nline == -1)
		(ft_printerror(ERROR10),ft_freeandexit(tmap));
	map = (char **)malloc(nline * sizeof(char *));
	if (!map)
		ft_freeandexit(tmap);
	fd = open(path, O_RDWR);
	i = 0;
	map[i++] = get_next_line(fd);
	if (map[0] == NULL)
		ft_freeandexit(tmap);
	while (i < nline)
	{
		map[i++] = get_next_line(fd);
		if (map[i - 1] == NULL)
			(ft_freetab(map, ft_min(0, i - 2)), ft_freeandexit(tmap));
	}
	close(fd);
	tmap->size = nline;
	return (map);
}

t_map	*ft_convmap(char *path)
{
	t_map	*tmap;

	tmap = (t_map *)malloc(sizeof(*tmap));
	if (!tmap)
		exit(0);
	tmap->map = ft_copymap(tmap, path);
	tmap->lenght = ft_strlennl(tmap->map[0]);
	tmap->c = 0;
	tmap->e = 0;
	tmap->p = 0;
	if (!ft_check(tmap))
	{
		ft_freetab(tmap->map, tmap->size);
		ft_freeandexit(tmap);
	}
	return (tmap);
}

void	ft_mapflags(t_vars *data, char c, int i, int j)
{
	if (c == '1')
		ft_print_mlx(data, data->wall->img, i * data->wall->height, j
			* data->wall->lenght);
	else if (c == 'C')
		ft_print_mlx(data, data->coin->img, i * data->floor->height, j
			* data->floor->lenght);
	else if (c == 'E')
		ft_print_mlx(data, data->exit->img, i * data->wall->height, j
			* data->exit->lenght);
	else if (c == '0')
		ft_print_mlx(data, data->floor->img, i * data->floor->height, j
			* data->floor->lenght);
	else if (c == 'P')
	{
		ft_print_mlx(data, data->mc->texture->img, i
			* data->mc->texture->height, j * data->mc->texture->lenght);
		data->mc->x = j;
		data->mc->y = i;
	}
}

void	ft_create_map(t_vars *data)
{
	int		i;
	size_t	j;

	j = 0;
	while (j < data->map->size)
	{
		i = 0;
		while (data->map->map[j][i] != '\0' && data->map->map[j][i] != '\n')
		{
			ft_mapflags(data, data->map->map[j][i], i, j);
			i++;
		}
		j++;
	}
}
