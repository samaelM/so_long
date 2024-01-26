CFLAGS = -Wall -Wextra -Werror
MLXFLAGS = -Lmlx -lmlx -L/usr/lib/X11 -lXext -lX11
NAME = so_long
SRC = main.c
OBJETS = $(SRC:.c=.o)

all :	minilibx $(NAME) 

minilibx:
	make -C mlx

$(NAME) : $(OBJETS)
	cc $(CFLAGS) -o $(NAME) $(OBJETS) -Lmlx -lmlx -L/usr/lib/X11 -lXext -lX11

%.o:	%.c
	cc $(CFLAGS) -c -o $@ $<

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
