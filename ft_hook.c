/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hook.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maemaldo <maemaldo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 11:33:44 by maemaldo          #+#    #+#             */
/*   Updated: 2024/02/07 17:54:45 by maemaldo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	on_keypress(int keysym, t_vars *data)
{
	if (keysym == 65364)
	{
		if (data->map->map[data->mc->x + 1][data->mc->y] != '1')
		{
			ft_print_mlx(data, data->floor->img, data->mc->y
				* data->mc->texture->lenght, data->mc->x
				* data->mc->texture->height);
			data->mc->x++;
			ft_print_mlx(data, data->mc->texture->img, data->mc->y
				* data->mc->texture->lenght, data->mc->x
				* data->mc->texture->height);
		}
	}
	if (keysym == 65362)
	{
		if (data->map->map[data->mc->x - 1][data->mc->y] != '1')
		{
			ft_print_mlx(data, data->floor->img, data->mc->y
				* data->mc->texture->lenght, data->mc->x
				* data->mc->texture->height);
			data->mc->x--;
			ft_print_mlx(data, data->mc->texture->img, data->mc->y
				* data->mc->texture->lenght, data->mc->x
				* data->mc->texture->height);
		}
	}
	if (keysym == 65361)
	{
		if (data->map->map[data->mc->x][data->mc->y - 1] != '1')
		{
			ft_print_mlx(data, data->floor->img, data->mc->y
				* data->mc->texture->lenght, data->mc->x
				* data->mc->texture->height);
			data->mc->y--;
			ft_print_mlx(data, data->mc->texture->img, data->mc->y
				* data->mc->texture->lenght, data->mc->x
				* data->mc->texture->height);
		}
	}
	if (keysym == 65363)
	{

		if (data->map->map[data->mc->x][data->mc->y + 1] != '1')
		{
			ft_print_mlx(data, data->floor->img, data->mc->y
				* data->mc->texture->lenght, data->mc->x
				* data->mc->texture->height);
			data->mc->y++;
			ft_print_mlx(data, data->mc->texture->img, data->mc->y
				* data->mc->texture->lenght, data->mc->x
				* data->mc->texture->height);
		}
	}
	if (keysym == 0xff1b)
		on_destroy(data);
	return (0);
}

int	on_destroy(t_vars *data)
{
	ft_freetab(data->map->map, data->map->size);
	free(data->wall);
	free(data->floor);
	free(data->coin);
	free(data->mc->texture);
	free(data->mc);
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	mlx_destroy_display(data->mlx_ptr);
	free(data->mlx_ptr);
	exit(0);
	return (0);
}
