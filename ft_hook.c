/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hook.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maemaldo <maemaldo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 11:33:44 by maemaldo          #+#    #+#             */
/*   Updated: 2024/02/08 16:56:16 by maemaldo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

enum	Direction
{
	UP = 65361,
	DOWN = 65362,
	LEFT = 65363,
	RIGHT = 65364,
	ESCAPE_KEY = 0xff1b
};
int	is_valid_move(t_vars *data, int x, int y)
{
	return (data->map->map[x][y] != '1');
}

void	move_player(t_vars *data, int dx, int dy)
{
	int	new_x;
	int	new_y;

	new_x = data->mc->x + dx;
	new_y = data->mc->y + dy;
	if (is_valid_move(data, new_x, new_y))
	{
		ft_print_mlx(data, data->floor->img, data->mc->y
			* data->mc->texture->lenght, data->mc->x
			* data->mc->texture->height);
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
			printf("\nScore: %d (left %d)", data->mc->c, data->map->c);
		}
	}
}

int	on_keypress(int keysym, t_vars *data)
{
	switch (keysym)
	{
	case RIGHT:
		move_player(data, 1, 0);
		// write(1, "right\n", 6);
		break ;
	case DOWN:
		move_player(data, -1, 0);
		break ;
	case UP:
		move_player(data, 0, -1);
		break ;
	case LEFT:
		move_player(data, 0, 1);
		break ;
	case ESCAPE_KEY:
		on_destroy(data);
		break ;
	default:
		break ;
	}
	return (0);
}
int	on_destroy(t_vars *data)
{
	ft_freetab(data->map->map, data->map->size);
	// free(data->wall->img->image);
	free(data->wall->img);
	free(data->wall);
	free(data->floor->img);
	free(data->floor);
	free(data->coin->img);
	free(data->coin);
	free(data->mc->texture->img);
	free(data->mc->texture);
	free(data->mc);
	free(data->exit->img);
	free(data->exit);
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	mlx_destroy_display(data->mlx_ptr);
	free(data->mlx_ptr);
	exit(0);
	return (0);
}
