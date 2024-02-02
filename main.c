/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maemaldo <maemaldo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 12:56:52 by maemaldo          #+#    #+#             */
/*   Updated: 2024/02/02 16:47:58 by maemaldo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	ft_max(int a, int b)
{
	return ((a > b) ? a : b);
}
int	ft_min(int a, int b)
{
	return ((a > b) ? b : a);
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	ft_square(t_vars *data, int width, int posx, int posy, int color)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < width)
	{
		j = 0;
		while (j < width)
		{
			if (i +posx < WIN_LENGHT && i >= 0 && j + posy < WIN_HEIGHT && j >= 0)
				my_mlx_pixel_put(data->map->img, posx + i, posy + j, color);
			j++;
		}
		i++;
	}
	// mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
		// data->map->img->img,
	// 	0, 0);
}

int	on_destroy(t_vars *data)
{
	ft_freetab(data->map->map, data->map->size);
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	mlx_destroy_display(data->mlx_ptr);
	free(data->mlx_ptr);
	exit(0);
	return (0);
}

int	mouse_hook(int button, int x, int y, t_vars *data)
{
	if (button == 1)
	{
		write(1, "oui", 3);
		ft_square(data, 100, x - 50, y - 50, BLUE);
		// mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
		// 	data->map->img->img, 0, 0);
	}
	if (button == 2)
		ft_square(data, 100, x - 50, y - 50, RED);
	if (button == 3)
		ft_square(data, 100, x - 50, y - 50, GREEN);
	if (button == 4)
		ft_square(data, 100, x - 50, y - 50, WHITE);
	if (button == 5)
		ft_square(data, 100, x - 50, y - 50, NICE);
	return (1);
}

void	ft_create_mc(t_vars *data, int x, int y)
{
	int		aa;
	int		bb;
	int		*a;
	int		*b;
	t_data	img;

	aa = 0, bb = 0;
	a = &aa, b = &bb;
	img.img = mlx_xpm_file_to_image(data->mlx_ptr, "./assets/teapot.xpm", a, b);
	data->img = &img;
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img->img, x, y);
	data->mc->x = x;
	data->mc->y = y;
}
void	ft_updatemap(t_vars *data)
{
	// DEBUG
	if (data->map->img->img)
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
			data->map->img->img, 0, 0);
}
void	ft_create_map(t_vars *data)
{
	int		i;
	size_t	j;
	t_data	img;

	img.img = mlx_new_image(data->mlx_ptr, WIN_HEIGHT, WIN_LENGHT);
	data->map->img = &img;
	data->map->img->addr = mlx_get_data_addr(data->map->img->img,
			&data->map->img->bits_per_pixel, &data->map->img->line_length,
			&data->map->img->endian);
	ft_square(data, WIN_HEIGHT, 0, 0, BLACK);
	j = 0;
	while (j < data->map->size)
	{
		i = 0;
		while (data->map->map[j][i])
		{
			if (data->map->map[j][i] == '1')
				ft_square(data, 50, 1 + 50 * i, 1 + 50 * j, WHITE);
			if (data->map->map[j][i] == 'C')
				ft_square(data, 50, 1 + 50 * i, 1 + 50 * j, YELLOW);
			if (data->map->map[j][i] == 'E')
				ft_square(data, 50, 1 + 50 * i, 1 + 50 * j, BLUE);
			if (data->map->map[j][i] == 'P')
				ft_square(data, 50, 1 + 50 * i, 1 + 50 * j, GREEN);
			i++;
		}
		j++;
	}
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->map->img->img,
		0, 0);
	// ft_square(data, SQUARE, 10, 10, BLUE);
	// ft_square(data, SQUARE, 110, 10, GREEN);
	// ft_square(data, SQUARE, 10, 110, RED);
	// ft_square(data, SQUARE, 110, 110, WHITE);
}

int	on_keypress(int keysym, t_vars *data)
{
	printf("%d", (1 && data->map->img->img));
	if (keysym == 65363)
	{
		ft_updatemap(data);
		ft_create_mc(data, data->mc->x + 100, data->mc->y);
	}
	if (keysym == 65361)
	{
		ft_updatemap(data);
		ft_create_mc(data, data->mc->x - 100, data->mc->y);
	}
	if (keysym == 65362)
	{
		ft_updatemap(data);
		ft_create_mc(data, data->mc->x, data->mc->y - 100);
	}
	if (keysym == 65364)
	{
		ft_updatemap(data);
		ft_create_mc(data, data->mc->x, data->mc->y + 100);
	}
	if (keysym == 0xff1b)
		on_destroy(data);
	return (0);
}
int	main(void)
{
	t_vars	data;
	t_map	map;
	t_mc	mc;

	data.mc = &mc;
	data.map = &map;
	ft_convmap(&data);
	data.mlx_ptr = mlx_init();
	if (!data.mlx_ptr)
		return (1);
	data.win_ptr = mlx_new_window(data.mlx_ptr, WIN_LENGHT, WIN_HEIGHT,
			WIN_NAME);
	if (!data.win_ptr)
		return (free(data.mlx_ptr), 1);
	ft_create_map(&data);
	ft_create_mc(&data, 0, 0);
	printf("%d", (1 && data.map->img->img));
	mlx_hook(data.win_ptr, KeyRelease, KeyReleaseMask, &on_keypress, &data);
	mlx_hook(data.win_ptr, DestroyNotify, StructureNotifyMask, &on_destroy,
		&data);
	mlx_mouse_hook(data.win_ptr, mouse_hook, &data);
	mlx_loop(data.mlx_ptr);
	return (0);
}
