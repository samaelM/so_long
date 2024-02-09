/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maemaldo <maemaldo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 12:56:52 by maemaldo          #+#    #+#             */
/*   Updated: 2024/02/09 17:53:20 by maemaldo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_print_mlx(t_vars *data, void *img, int x, int y)
{
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, img, ft_min(x,
			WIN_LENGHT), ft_min(y, WIN_HEIGHT));
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
			if (data->map->map[j][i] == '1')
				ft_print_mlx(data, data->wall->img, i * data->wall->height, j
					* data->wall->lenght);
			else if (data->map->map[j][i] == 'C')
				ft_print_mlx(data, data->coin->img, i * data->floor->height, j
					* data->floor->lenght);
			else if (data->map->map[j][i] == 'E')
				ft_print_mlx(data, data->exit->img, i * data->wall->height, j
					* data->exit->lenght);
			else if (data->map->map[j][i] == '0')
				ft_print_mlx(data, data->floor->img, i * data->floor->height, j
					* data->floor->lenght);
			else if (data->map->map[j][i] == 'P')
			{
				ft_print_mlx(data, data->mc->texture->img, i
					* data->mc->texture->height, j * data->mc->texture->lenght);
				data->mc->x = j;
				data->mc->y = i;
			}
			i++;
		}
		j++;
	}
}

int	ft_load_texture(t_vars *data, t_data *image, char *direction)
{
	t_data	*e;
	int		a;
	int		b;

	e = (t_data *)malloc(sizeof(*e));
	if (!e)
		return (0);
	e->img = mlx_xpm_file_to_image(data->mlx_ptr, direction, &a, &b);
	image = e;
	image->height = a;
	image->lenght = b;
	return (1);
}
void	ft_texture_init(t_vars *data)
{
	t_mc	*mc;
	t_data	*texture;
	t_data	*floor;
	t_data	*coin;
	t_data	*exit;
	int		a;
	int		b;

	t_data	*wall;
	wall = (t_data *)malloc(sizeof(*wall));
	wall->img = mlx_xpm_file_to_image(data->mlx_ptr, "assets/wall.xpm", &a,
			&b);
	data->wall = wall;
	data->wall->height = a;
	data->wall->lenght = b;
	// ft_load_texture(data, data->wall, "assets/wall.xpm");
	// printf("%d, %d", data->wall->height, data->wall->lenght);
	// sleep(2);
	mc = (t_mc *)malloc(sizeof(*mc));
	data->mc = mc;
	texture = (t_data *)malloc(sizeof(*texture));
	texture->img = mlx_xpm_file_to_image(data->mlx_ptr, "assets/mc_texture.xpm",
			&a, &b);
	data->mc->texture = texture;
	data->mc->texture->height = a;
	data->mc->texture->lenght = b;
	floor = (t_data *)malloc(sizeof(*floor));
	floor->img = mlx_xpm_file_to_image(data->mlx_ptr, "assets/floor.xpm", &a,
			&b);
	data->floor = floor;
	data->floor->height = a;
	data->floor->lenght = b;
	coin = (t_data *)malloc(sizeof(*coin));
	coin->img = mlx_xpm_file_to_image(data->mlx_ptr, "assets/test.xpm", &a, &b);
	data->coin = coin;
	data->coin->height = a;
	data->coin->lenght = b;
	exit = (t_data *)malloc(sizeof(*exit));
	exit->img = mlx_xpm_file_to_image(data->mlx_ptr, "assets/exit.xpm", &a, &b);
	data->exit = exit;
	data->exit->height = a;
	data->exit->lenght = b;
}
int	main(void)
{
	t_vars	data;
	t_map	map;

	data.mlx_ptr = mlx_init();
	if (!data.mlx_ptr)
		return (1);
	data.map = &map;
	ft_convmap(&data);
	write(1, "map loaded\n", 11);
	data.win_ptr = mlx_new_window(data.mlx_ptr, WIN_LENGHT, WIN_HEIGHT,
			WIN_NAME);
	if (!data.win_ptr)
		return (free(data.mlx_ptr), 1);
	ft_texture_init(&data);
	write(1, "textures loaded\n", 15);
	ft_create_map(&data);
	data.mc->c = 0;
	data.cpt = 0;
	mlx_hook(data.win_ptr, KeyPress, KeyPressMask, &on_keypress, &data);
	mlx_hook(data.win_ptr, DestroyNotify, StructureNotifyMask, &on_destroy,
		&data);
	mlx_loop(data.mlx_ptr);
	return (0);
}
