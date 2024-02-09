/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hook.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maemaldo <maemaldo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 11:33:44 by maemaldo          #+#    #+#             */
/*   Updated: 2024/02/09 17:19:52 by maemaldo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

enum	e_Direction
{
	UP = 65361,
	DOWN = 65362,
	LEFT = 65363,
	RIGHT = 65364,
	ESCAPE_KEY = 0xff1b
};

int	is_valid_move(t_vars *data, int x, int y)
{
	return ((data->map->map[x][y] == 'E' && data->map->c == 0)
		|| (data->map->map[x][y] != '1' && data->map->map[x][y] != 'E'));
}

void	ft_win(t_vars *data)
{
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
		printf(" movements: %lld\n", data->cpt);
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
			printf("Score: %d (left %d)\n", data->mc->c, data->map->c);
		}
		if (data->map->map[data->mc->x][data->mc->y] == 'E')
			ft_win(data);
	}
}

int	on_keypress(int keysym, t_vars *data)
{
	switch (keysym)
	{
	case 115:
		move_player(data, 1, 0);
		// write(1, "right\n", 6);
		break ;
	case 119:
		move_player(data, -1, 0);
		break ;
	case 97:
		move_player(data, 0, -1);
		break ;
	case 100:
		move_player(data, 0, 1);
		break ;
	case 65307:
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
	mlx_destroy_image(data->mlx_ptr, data->wall->img);
	free(data->wall);
	mlx_destroy_image(data->mlx_ptr, data->floor->img);
	free(data->floor);
	mlx_destroy_image(data->mlx_ptr, data->coin->img);
	free(data->coin);
	mlx_destroy_image(data->mlx_ptr, data->mc->texture->img);
	free(data->mc->texture);
	free(data->mc);
	mlx_destroy_image(data->mlx_ptr, data->exit->img);
	free(data->exit);
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	mlx_destroy_display(data->mlx_ptr);
	free(data->mlx_ptr);
	exit(0);
	return (0);
}
