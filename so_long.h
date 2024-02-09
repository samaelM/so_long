/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maemaldo <maemaldo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 17:30:39 by maemaldo          #+#    #+#             */
/*   Updated: 2024/02/09 17:47:05 by maemaldo         ###   ########.fr       */
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

# define WIN_NAME "42 lore"

# define WIN_LENGHT 1900
# define WIN_HEIGHT 1500

# define RED 0x00ff0000
# define GREEN 0x0000ff00
# define BLUE 0x000000ff
# define WHITE 0x00ffffff
# define BLACK 0x00000000
# define NICE 0x00B00B69
# define YELLOW 0x00FFFF00

# define SQUARE 100

# define DEBUG write(1, "\nDEBUGi\n", 8);
# define DEBUG2 write(1, "\nDEBUG-j--\n", 11);

typedef enum Bool
{
	False,
	True
}			t_Bool;

typedef struct s_data
{
	void	*img;
	int		height;
	int		lenght;
}			t_data;

typedef struct s_map
{
	char	**map;
	void	***pmap;
	size_t	size;
	int		c;
	int		e;
	int		p;
	t_data	*img;
}			t_map;

typedef struct s_mc
{
	t_data	*texture;
	int		x;
	int		y;
	int		c;
}			t_mc;

typedef struct s_vars
{
	void	*mlx_ptr;
	void	*win_ptr;
	t_data	*wall;
	t_data	*exit;
	t_data	*floor;
	t_data	*coin;
	t_mc	*mc;
	t_map	*map;
	long long cpt;
}			t_vars;

void		ft_convmap(t_vars *data);
void		ft_freetab(char **s, int size);
int			on_destroy(t_vars *data);
int			on_keypress(int keysym, t_vars *data);
void		my_mlx_pixel_put(t_data *data, int x, int y, int color);
void		ft_square(t_vars *data, int width, int posx, int posy, int color);
void		ft_create_mc(t_vars *data, int x, int y);
void		ft_updatemap(t_vars *data);
void		ft_create_map(t_vars *data);
size_t		ft_strlennl(char *s);
int			ft_max(int a, int b);
int			ft_min(int a, int b);
void		ft_print_mlx(t_vars *data, void *img, int x, int y);
int	ft_ultimate_check(char **map);

#endif