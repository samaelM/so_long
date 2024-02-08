/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maemaldo <maemaldo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 16:05:18 by maemaldo          #+#    #+#             */
/*   Updated: 2024/02/08 15:09:48 by maemaldo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

// #define ROWS 6
// #define COLS 20

// t_Bool	can_beat_map(char **map, int row, int col, int coins)
// {
// 	// Base cases:
// 	// If the current position is out of bounds, a wall, or already visited,
// 	return False if (row < 0 || row >= ROWS || col < 0 || col >= COLS
// 		|| map[row][col] == '1' || map[row][col] == 'V')
// 	{
// 		return (False);
// 	}
// 	// If the current position is the exit ('E') and all coins have been collected,
// 	return True if (map[row][col] == 'E' && coins == 0)
// 	{
// 		return (True);
// 	}
// 	// If the current position is a coin ('C'), collect it
// 	if (map[row][col] == 'C')
// 	{
// 		coins--;
// 	}
// 	// Mark the current position as visited
// 	map[row][col] = 'V';
// 	// Explore in all four directions (up, down, left, right)
// 	if (can_beat_map(map, row - 1, col, coins) || // Up
// 		can_beat_map(map, row + 1, col, coins) || // Down
// 		can_beat_map(map, row, col - 1, coins) || // Left
// 		can_beat_map(map, row, col + 1, coins))
// 	{ // Right
// 		return (True);
// 	}
// 	// If no path to the exit is found, return False
// 	return (False);
// }

// int	ft_ultimate_check(char **map)
// {
// 	t_Bool	result;

// 	// char	map[ROWS][COLS] = {{'1', '1', '1', '1', '1', '1', '1', '1', '1',
// 	// 		'1'}, {'1', 'P', '0', '0', '1', '0', '0', '0', 'C', '1'}, {'1', '1',
// 	// 		'1', '0', '1', '0', '1', '1', '1', '1'}, {'1', '0', '0', '0', '0',
// 	// 		'0', '0', '0', '0', '1'}, {'1', '1', '1', '0', '1', '0', '1', '1',
// 	// 		'1', '1'}, {'1', '0', '0', '0', '1', '0', '0', '0', 'E', '1'}, {'1',
// 	// 		'1', '1', '1', '1', '1', '1', '1', '1', '1'}};
// 	int start_row, start_col;
// 	for (int i = 0; i < ROWS; i++)
// 	{
// 		for (int j = 0; j < COLS; j++)
// 		{
// 			if (map[i][j] == 'P')
// 			{
// 				start_row = i;
// 				start_col = j;
// 				break ;
// 			}
// 		}
// 	}
// 	result = can_beat_map(map, start_row, start_col, 3);
// 	if (result)
// 	{
// 		printf("The map can be beaten!\n");
// 	}
// 	else
// 	{
// 		printf("The map cannot be beaten.\n");
// 	}
// 	return (0);
// }

size_t	ft_strlennl(char *s)
{
	int	i;

	i = 0;
	while (s && s[i] && s[i] != '\n')
		i++;
	return (i);
}
t_Bool	ft_check1(char *s)
{
	int	i;

	i = 0;
	while (s && s[i])
	{
		if (!(s[i] == '0' || s[i] == '1' || s[i] == 'C' || s[i] == 'E'
				|| s[i] == 'P' || s[i] == '\n'))
			return (False);
		i++;
	}
	return (True);
}

int	ft_countchr(char *s, char c)
{
	int	i;
	int	n;

	i = 0;
	n = 0;
	while (s && s[i])
	{
		if (s[i] == c)
			n++;
		i++;
	}
	return (n);
}

t_Bool	ft_check2(t_vars *data, char *s, t_Bool last_line)
{
	data->map->c += ft_countchr(s, 'C');
	data->map->e += ft_countchr(s, 'E');
	data->map->p += ft_countchr(s, 'P');
	if (data->map->e > 1)
		return (False);
	if (last_line)
	{
		if (data->map->e > 1 || data->map->c < 1 || data->map->p != 1)
			return (False);
	}
	return (True);
}
t_Bool	ft_check3(char *s)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != '\n')
	{
		if (s[i] != '1')
			return (False);
		i++;
	}
	return (True);
}
t_Bool	ft_check4(char *s)
{
	if (s[0] != '1' || s[ft_strlennl(s) - 1] != '1')
		return (False);
	return (True);
}

int	ft_count_line(void)
{
	int		fd;
	char	*line;
	int		n;

	fd = open(MAP, O_RDWR);
	line = get_next_line(fd);
	n = 0;
	if (!line)
		n = -1;
	while (line)
	{
		free(line);
		line = get_next_line(fd);
		n++;
	}
	close(fd);
	return (n);
}
t_Bool	ft_check(t_vars *data)
{
	size_t	line_length;
	size_t	i;

	i = 0;
	line_length = ft_strlennl(data->map->map[i]);
	if (!ft_check1(data->map->map[i]) || !ft_check2(data, data->map->map[i],
			False) || !ft_check3(data->map->map[i]))
	{
		printf("CHARACTER PROBLEM\nEXITING THE PROGRAM\n");
		return (False);
	}
	while (i < data->map->size)
	{
		if (!ft_check1(data->map->map[i]) || !ft_check2(data, data->map->map[i],
				False) || !ft_check4(data->map->map[i]))
		{
			printf("CHARACTER PROBLEM\nEXITING THE PROGRAM\n");
			return (False);
		}
		if (line_length != ft_strlennl(data->map->map[i]))
		{
			printf("\nNON AUTHORIZED SHAPE\nEXITING THE PROGRAM\n");
			return (False);
		}
		i++;
	}
	if (!ft_check2(data, data->map->map[i - 1], True)
		|| !ft_check3(data->map->map[i - 1]))
	{
		printf("Error\n");
		return (False);
	}
	return (True);
}

void	ft_freetab(char **s, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		free(s[i]);
		i++;
	}
	free(s);
}

void	ft_convmap(t_vars *data)
{
	int		fd;
	int		i;
	char	**map;
	int		nline;

	nline = ft_count_line();
	if (nline == -1)
		(mlx_destroy_display(data->mlx_ptr), free(data->mlx_ptr), exit(0));
	map = (char **)malloc(nline * sizeof(char *));
	if(!map)
		(mlx_destroy_display(data->mlx_ptr), free(data->mlx_ptr), exit(0));
	fd = open(MAP, O_RDWR);
	i = 0;
	map[i++] = get_next_line(fd);
	if (map[0] == NULL)
		(mlx_destroy_display(data->mlx_ptr), free(data->mlx_ptr), exit(0));
	while (i < nline)
	{
		map[i++] = get_next_line(fd);
		if (map[i - 1] == NULL)
		{
			ft_freetab(map, ft_min(0, i - 2));
			(mlx_destroy_display(data->mlx_ptr), free(data->mlx_ptr), exit(0));
		}
	}
	close(fd);
	data->map->map = map;
	data->map->size = nline;
	data->map->c = 0;
	data->map->e = 0;
	data->map->p = 0;
	if (!ft_check(data))
	{
		ft_freetab(data->map->map, data->map->size);
		(mlx_destroy_display(data->mlx_ptr), free(data->mlx_ptr), exit(0));
	}
	// ft_ultimate_check(data->map->map);
}
