CFLAGS = -Wall -Wextra -Werror
MLXFLAGS = -Lmlx -lmlx -L/usr/lib/X11 -lXext -lX11
NAME = so_long
SRC = main.c ft_map.c gnl/get_next_line.c gnl/get_next_line_utils.c ft_hook.c ft_utils.c
OBJETS = $(SRC:.c=.o)

all :	minilibx $(NAME) 

minilibx:
	make -C mlx

$(NAME) : $(OBJETS)
	cc $(CFLAGS) -o $(NAME) $(OBJETS) -Lmlx -lmlx -L/usr/lib -lXext -lX11 -g

%.o:	%.c
	cc $(CFLAGS) -c -o $@ $< -g

clean :
	rm -f $(OBJETS)
	make -C mlx clean

fclean :
	rm -f $(NAME)
	rm -f $(OBJETS)
	make -C mlx clean

re : fclean all
	make -C mlx re

.PHONY : all clean fclean re
