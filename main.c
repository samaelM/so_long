/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maemaldo <maemaldo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 12:56:52 by maemaldo          #+#    #+#             */
/*   Updated: 2024/02/07 18:24:47 by maemaldo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_create_mc(t_vars *data, int x, int y)
{
	int		aa;
	int		bb;
	int		*a;
	int		*b;
	t_data	img;

	aa = 0, bb = 0;
	a = &aa, b = &bb;
	img.img = mlx_xpm_file_to_image(data->mlx_ptr, "mlx/test/open24.xpm", a, b);
	data->mc->texture = &img;
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
		data->mc->texture->img, x, y);
	data->mc->x = x;
	data->mc->y = y;
}

void	ft_updatemap(t_vars *data)
{
	if (data->wall->img)
	{
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->wall->img,
			0, 0);
	}
}

void	ft_print_mlx(t_vars *data, void *img, int x, int y)
{
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, img, ft_min(x,
			WIN_LENGHT), ft_min(y, WIN_HEIGHT));
}

void	ft_create_map(t_vars *data)
{
	int		i;
	size_t	j;
	int		aa;
	int		bb;
	int		*a;
	int		*b;

	aa = 0, bb = 0;
	a = &aa, b = &bb;
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
				mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
					data->wall->img, ft_min(i * data->wall->height, WIN_HEIGHT),
					ft_min(j * data->wall->lenght, WIN_HEIGHT));
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
void	ft_texture_init(t_vars *data)
{
	t_mc	*mc;
	t_data	*wall;
	t_data	*texture;
	t_data	*floor;
	t_data	*coin;
	int		a;
	int		b;

	wall = (t_data *)malloc(sizeof(*wall));
	wall->img = mlx_xpm_file_to_image(data->mlx_ptr, "assets/textur.xpm", &a,
			&b);
	data->wall = wall;
	data->wall->height = a;
	data->wall->lenght = b;
	mc = (t_mc *)malloc(sizeof(*mc));
	data->mc = mc;
	texture = (t_data *)malloc(sizeof(*texture));
	texture->img = mlx_xpm_file_to_image(data->mlx_ptr, "assets/textures.xpm",
			&a, &b);
	data->mc->texture = texture;
	data->mc->texture->height = a;
	data->mc->texture->lenght = b;
	floor = (t_data *)malloc(sizeof(*floor));
	floor->img = mlx_xpm_file_to_image(data->mlx_ptr, "assets/floor.xpm",
			&a, &b);
	data->floor = floor;
	data->floor->height = a;
	data->floor->lenght = b;
	coin = (t_data *)malloc(sizeof(*coin));
	coin->img = mlx_xpm_file_to_image(data->mlx_ptr, "assets/coin.xpm",
			&a, &b);
	data->coin = coin;
	data->coin->height = a;
	data->coin->lenght = b;
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
	write(1, "textures loaded", 15);
	ft_create_map(&data);
	mlx_hook(data.win_ptr, KeyRelease, KeyReleaseMask, &on_keypress, &data);
	mlx_hook(data.win_ptr, DestroyNotify, StructureNotifyMask, &on_destroy,
		&data);
	mlx_loop(data.mlx_ptr);
	return (0);
}
