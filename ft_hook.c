/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hook.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maemaldo <maemaldo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 11:33:44 by maemaldo          #+#    #+#             */
/*   Updated: 2024/02/16 15:25:08 by maemaldo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	is_valid_move(t_vars *data, int x, int y)
{
	return ((data->map->map[x][y] == 'E' && data->map->c == 0)
		|| (data->map->map[x][y] != '1' && data->map->map[x][y] != 'E'));
}

void	ft_win(t_vars *data)
{
	printf("\n\n\n\nGG ma boy you won\n\n\n\n");
	on_destroy(data);
}

void	move_player(t_vars *data, int dx, int dy)
{
	int	new_x;
	int	new_y;

	new_x = data->mc->x + dx;
	new_y = data->mc->y + dy;
	if (is_valid_move(data, new_x, new_y))
	{
		data->cpt++;
		printf(" movements: %lld\nScore: %d\n", data->cpt, data->mc->c);
		ft_print_mlx(data, data->floor->img, data->mc->y * data->floor->lenght,
			data->mc->x * data->floor->height);
		data->mc->x = new_x;
		data->mc->y = new_y;
		ft_print_mlx(data, data->mc->texture->img, data->mc->y
			* data->mc->texture->lenght, data->mc->x
			* data->mc->texture->height);
		if (data->map->map[data->mc->x][data->mc->y] == 'C')
		{
			data->map->map[data->mc->x][data->mc->y] = '0';
			data->map->c--;
			data->mc->c++;
		}
		if (data->map->map[data->mc->x][data->mc->y] == 'E')
			ft_win(data);
	}
}

int	on_keypress(int keysym, t_vars *data)
{
	if (keysym == 115)
		move_player(data, 1, 0);
	if (keysym == 119)
		move_player(data, -1, 0);
	if (keysym == 97)
		move_player(data, 0, -1);
	if (keysym == 100)
		move_player(data, 0, 1);
	if (keysym == 65307)
		on_destroy(data);
	return (0);
}

void	ft_freetextures(t_vars *data)
{
	if (data->wall)
		mlx_destroy_image(data->mlx_ptr, data->wall->img);
	free(data->wall);
	if (data->mc)
	{
		if (data->mc->texture)
			mlx_destroy_image(data->mlx_ptr, data->mc->texture->img);
		free(data->mc->texture);
		free(data->mc);
	}
	if (data->floor)
		mlx_destroy_image(data->mlx_ptr, data->floor->img);
	free(data->floor);
	if (data->coin)
		mlx_destroy_image(data->mlx_ptr, data->coin->img);
	free(data->coin);
	if (data->exit)
		mlx_destroy_image(data->mlx_ptr, data->exit->img);
	free(data->exit);
}

int	on_destroy(t_vars *data)
{
	ft_freetab(data->map->map, data->map->size);
	free(data->map);
	ft_freetextures(data);
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	mlx_destroy_display(data->mlx_ptr);
	free(data->mlx_ptr);
	exit(0);
	return (0);
}
