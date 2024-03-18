/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maemaldo <maemaldo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 12:56:52 by maemaldo          #+#    #+#             */
/*   Updated: 2024/03/12 14:26:15 by maemaldo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_print_mlx(t_vars *data, void *img, int x, int y)
{
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, img, ft_min(x,
			data->map->lenght * 80), ft_min(y, data->map->size * 80));
}

t_data	*ft_load_texture(t_vars *data, t_data **image, char *direction)
{
	t_data	*e;
	int		a;
	int		b;

	e = (t_data *)malloc(sizeof(*e));
	if (!e)
		return (NULL);
	e->img = mlx_xpm_file_to_image(data->mlx_ptr, direction, &a, &b);
	if (!e->img)
		return (free(e), NULL);
	*image = e;
	(*image)->height = a;
	(*image)->lenght = b;
	return (e);
}

void	ft_texture_init(t_vars *data)
{
	t_mc	*mc;

	data->exit = NULL;
	data->coin = NULL;
	data->floor = NULL;
	data->wall = NULL;
	data->mc = NULL;
	mc = (t_mc *)malloc(sizeof(*mc));
	if (!mc)
		on_destroy(data);
	data->mc = mc;
	data->mc->texture = NULL;
	if (!(ft_load_texture(data, &data->wall, "assets/wall.xpm")
			&& ft_load_texture(data, &data->mc->texture,
				"assets/mc.xpm") && ft_load_texture(data,
				&data->floor, "assets/floor.xpm") && ft_load_texture(data,
				&data->coin, "assets/coins.xpm") && ft_load_texture(data,
				&data->exit, "assets/exit.xpm")))
		on_destroy(data);
}

int	main(int ac, char **av)
{
	t_vars	data;

	if (ac != 2)
		return (ft_printerror(ERROR8));
	data.map = ft_convmap(av[1]);
	write(1, "map loaded\n", 11);
	data.mlx_ptr = mlx_init();
	if (!data.mlx_ptr)
		return (1);
	data.win_ptr = mlx_new_window(data.mlx_ptr, data.map->lenght * 80,
			data.map->size * 80, WIN_NAME);
	if (!data.win_ptr)
		return (free(data.mlx_ptr), 1);
	ft_texture_init(&data);
	write(1, "textures loaded\n", 16);
	ft_create_map(&data);
	data.mc->c = 0;
	data.cpt = 0;
	mlx_hook(data.win_ptr, KeyPress, KeyPressMask, &on_keypress, &data);
	mlx_hook(data.win_ptr, DestroyNotify, StructureNotifyMask, &on_destroy,
		&data);
	mlx_loop(data.mlx_ptr);
	return (0);
}
