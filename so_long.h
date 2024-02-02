/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maemaldo <maemaldo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 17:30:39 by maemaldo          #+#    #+#             */
/*   Updated: 2024/02/02 15:49:47 by maemaldo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# ifndef MAP
#  define MAP "./map0.ber"
# endif

# include "gnl/get_next_line.h"
# include "mlx/mlx.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define WIN_NAME "fenetre tres cool"

# define WIN_LENGHT 1080
# define WIN_HEIGHT 1080

# define RED 0x00ff0000
# define GREEN 0x0000ff00
# define BLUE 0x000000ff
# define WHITE 0x00ffffff
# define BLACK 0x00000000
# define NICE 0x00B00B69
# define YELLOW 0x00FFFF00

# define SQUARE 100

# define DEBUG write(1, "\nDEBUG\n", 7);

typedef enum Bool
{
	False,
	True
}			t_Bool;

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}			t_data;

typedef struct s_map
{
	char	**map;
	size_t	size;
	int		c;
	int		e;
	int		p;
	t_data *img;
}			t_map;

typedef struct s_mc
{
	t_data	texture;
	int		x;
	int		y;
	int		c;
}			t_mc;

typedef struct s_vars
{
	void	*mlx_ptr;
	void	*win_ptr;
	t_data	*img;
	t_mc	*mc;
	t_map	*map;
}			t_vars;

void		ft_convmap(t_vars *data);
void		ft_freetab(char **s, int size);

#endif