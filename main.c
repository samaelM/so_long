/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maemaldo <maemaldo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 17:33:16 by maemaldo          #+#    #+#             */
/*   Updated: 2024/01/26 16:49:25 by maemaldo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx/mlx.h"
#include <stdio.h>
#include <stdlib.h>

#define WIN_NAME "yamete"

#define WIN_LENGHT 1920
#define WIN_HEIGHT 1080

#define RED 0x00ff0000
#define GREEN 0x0000ff00
#define BLUE 0x000000ff
#define WHITE 0x00ffffff
#define BLACK 0x00000000

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}			t_data;

typedef struct	s_vars {
	void	*mlx;
	void	*win;
}				t_vars;

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

int	close(t_vars *vars)
{
	mlx_destroy_window(vars->mlx, vars->win);
	mlx_destroy_display(vars->mlx);
	free(vars->mlx);
	// exit(0);
	return (0);
}

int ft_max(int a, int b)
{
	return (a > b)?a:b;
}
int ft_min(int a, int b)
{
	return (a > b)?b:a;
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void ft_square(t_data data, int width, int posx, int posy, int color)
{
	int i = 0;
	int j = 0;
	while (i < width && i+posx < WIN_LENGHT)
	{
		j = 0;
		while (j < width && j+posy < WIN_HEIGHT)
		{
			// printf("--%d-- --%d--\n", i, j);
			my_mlx_pixel_put(&data, i+posx, j+posy, color);
			j++;
		}
		i++;
	}
}

int	main(void)
{
	// void	*mlx;
	void	*mlx_win;
	t_data	img;
	t_vars	vars;
	vars.mlx = mlx_init();
	vars.win = mlx_win = mlx_new_window(vars.mlx, WIN_LENGHT, WIN_HEIGHT, WIN_NAME);
	img.img = mlx_new_image(vars.mlx, WIN_LENGHT, WIN_HEIGHT); 
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
			&img.endian);
	ft_square(img, 100, 10, 10, BLUE);
	ft_square(img, 100, 110, 10, GREEN);
	ft_square(img, 100, 10, 110, RED);
	ft_square(img, 100, 110, 110, WHITE);
	mlx_put_image_to_window(vars.mlx, mlx_win, img.img, 0, 0);
	mlx_hook(vars.win, 2, 1L<<0, &close, &vars);
	mlx_loop(vars.mlx);
}
