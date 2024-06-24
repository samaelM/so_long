/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maemaldo <maemaldo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 12:56:52 by maemaldo          #+#    #+#             */
/*   Updated: 2024/05/31 13:24:17 by maemaldo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

t_Bool	ft_check_texture(t_vars *data)
{
	if (data->wall->height == data->wall->lenght
		&& data->wall->height == data->coin->height
		&& data->wall->height == data->coin->lenght
		&& data->wall->height == data->exit->height
		&& data->wall->height == data->exit->lenght
		&& data->wall->height == data->mc->texture->height
		&& data->wall->height == data->mc->texture->lenght)
		return (True);
	return (False);
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

	mc = (t_mc *)malloc(sizeof(*mc));
	if (!mc)
		(ft_printerror(ERROR14), on_destroy(data));
	data->mc = mc;
	data->mc->texture = NULL;
	if (!(ft_load_texture(data, &data->wall, "assets/wall.xpm")
			&& ft_load_texture(data, &data->mc->texture, "assets/mc.xpm")
			&& ft_load_texture(data, &data->floor, "assets/floor.xpm")
			&& ft_load_texture(data, &data->coin, "assets/coins.xpm")
			&& ft_load_texture(data, &data->exit, "assets/exit.xpm")))
	{
		ft_printerror(ERROR12);
		on_destroy(data);
	}
	if (!ft_check_texture(data))
	{
		ft_printerror(ERROR12);
		on_destroy(data);
	}
}

int	main(int ac, char **av)
{
	t_vars	data;

	if (ac != 2)
		return (ft_printerror(ERROR8));
	ft_memset(&data, 0, sizeof(t_vars));
	if (!ft_check_filename(av[1]))
		return (ft_printerror(ERROR11));
	data.map = ft_convmap(av[1]);
	data.mlx_ptr = mlx_init();
	if (!data.mlx_ptr)
		return (ft_printerror(ERROR14), on_destroy(&data));
	data.win_ptr = NULL;
	ft_texture_init(&data);
	data.win_ptr = mlx_new_window(data.mlx_ptr, data.map->lenght
			* data.wall->lenght, data.map->size * data.wall->lenght, WIN_NAME);
	if (!data.win_ptr)
		return (ft_printerror(ERROR14), on_destroy(&data));
	ft_create_map(&data);
	data.mc->c = 0;
	data.cpt = 0;
	mlx_hook(data.win_ptr, KeyPress, KeyPressMask, &on_keypress, &data);
	mlx_hook(data.win_ptr, DestroyNotify, StructureNotifyMask, &on_destroy,
		&data);
	mlx_loop(data.mlx_ptr);
	return (0);
}
