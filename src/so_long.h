/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maemaldo <maemaldo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 17:30:39 by maemaldo          #+#    #+#             */
/*   Updated: 2024/03/29 21:28:36 by maemaldo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# ifndef MAP
#  define MAP "./map0.ber"
# endif

# include "libft/libft.h"
# include "../mlx/mlx.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define WIN_NAME "42 lore"
# define MAX 32
# define MAX2 17

# define ERROR0 "map must have a rectangular shape\n"
# define ERROR1 "at least one character is not correct\n"
# define ERROR2 "map have more than one exit\n"
# define ERROR3 "map have no exit\n"
# define ERROR4 "map have no coins\n"
# define ERROR5 "map must have ONE player position\n"
# define ERROR6 "map border must have wall\n"
# define ERROR7 "map is not beatable\n"
# define ERROR8 "Usage: ./so_long [map]\n"
# define ERROR9 "unable to open the map\n"
# define ERROR10 "first line is empty\n"

typedef enum Bool
{
	False,
	True
}				t_Bool;

typedef struct s_data
{
	void		*img;
	int			height;
	int			lenght;
}				t_data;

typedef struct s_map
{
	char		**map;
	size_t		size;
	size_t		lenght;
	int			c;
	int			e;
	int			p;
	t_data		*img;
}				t_map;

typedef struct s_mc
{
	t_data		*texture;
	int			x;
	int			y;
	int			c;
}				t_mc;

typedef struct s_vars
{
	void		*mlx_ptr;
	void		*win_ptr;
	t_data		*wall;
	t_data		*exit;
	t_data		*floor;
	t_data		*coin;
	t_mc		*mc;
	t_map		*map;
	long long	cpt;
}				t_vars;

int				on_destroy(t_vars *data);
int				on_keypress(int keysym, t_vars *data);
int				ft_max(int a, int b);
int				ft_min(int a, int b);
size_t			ft_strlennl(char *s);
t_map			*ft_convmap(char *path);
t_Bool			ft_check(t_map *data);
t_Bool			ft_check1(char *s);
t_Bool			ft_check2(t_map *data, char *s, t_Bool last_line);
t_Bool			ft_check3(char *s);
t_Bool			ft_check4(char *s);
t_Bool			ft_floodfill_check(char **map, int size, int c);
void			ft_create_map(t_vars *data);
void			ft_print_mlx(t_vars *data, void *img, int x, int y);
void			ft_freetab(char **s, int size);
int				ft_countchr(char *s, char c);
char			**ft_doubletabdup(char **tab, int size);
t_Bool			ft_printerror(char *error_msg);
int				ft_count_line(t_map *tmap, char *path);
void			ft_freeandexit(t_map *data);

#endif