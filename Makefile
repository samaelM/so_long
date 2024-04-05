CFLAGS = -Wall -Wextra -Werror

MLXFLAGS = -Lmlx -lmlx -L/usr/lib/X11 -lXext -lX11

NAME = so_long

SRC = src/main.c src/ft_map.c src/ft_hook.c src/ft_utils.c src/ft_check.c src/ft_map_utils.c src/ft_print_things.c

LIBFT_DIR = ./src/libft/

LIBFT = libft.a

OBJETS = $(SRC:.c=.o)

RED=\033[0;31m

GREEN=\033[0;32m

YELLOW=\033[0;33m

WHITE=\033[0m

BLUE = \033[0;36m

$(NAME) : $(OBJETS)
	@printf "$(YELLOW) TRYING TO COMPILE SO_LONG$(WHITE)"
	@make -s libft
	@make -s minilibx
	@cc $(CFLAGS) -o $(NAME) $(OBJETS) $(MLXFLAGS) -g $(LIBFT_DIR)$(LIBFT)
	@printf "\r$(GREEN)SO_LONG READY TO USE$(WHITE)"

all : $(NAME)

minilibx:
	@make -C mlx >/dev/null 2>&1

libft:
	@make -s -C $(LIBFT_DIR) >/dev/null 2>&1

.c.o:
	@cc $(CFLAGS) -c -o $@ $< -g

clean :
	@printf "$(YELLOW)CLEANING ".o" FILES$(WHITE)"
	@rm -f $(OBJETS)
	@make -C mlx clean >/dev/null
	@make -C $(LIBFT_DIR) clean >/dev/null
	@printf "\r$(RED)".o" FILES ARE CLEANED$(WHITE)"

fclean : clean
	@printf "\r$(YELLOW)CLEANING MLX AND LIBFT$(WHITE)"
	@make -C mlx clean >/dev/null
	@make -C $(LIBFT_DIR) fclean >/dev/null
	@rm -f ${NAME}
	@printf "\r$(YELLOW)FCLEANED WITH SUCCESS$(WHITE)"

re : fclean all

test : re
	@norminette src
	@valgrind --leak-check=full --show-leak-kinds=all -s --track-origins=yes ./$(NAME) maps/map0.ber

.PHONY : all clean fclean re

debug: $(OBJETS)
	make -C mlx
	make -C $(LIBFT_DIR)
	cc $(CFLAGS) -o $(NAME) $(OBJETS) -Lmlx -lmlx -L/usr/lib -lXext -lX11 -g $(LIBFT_DIR)$(LIBFT)

samael:
	@echo "$(BLUE)                               (\_/)                                        "
	@echo "                               (0.0)                                        "
	@echo "                               />*<\                                        "
	@echo "         ******\   ******\  **\      **\  ******\  ********\ **\            "
	@echo "        **  __**\ **  __**\ ***\    *** |**  __**\ **  _____|** |           "
	@echo "        ** /  \__|** /  ** |****\  **** |** /  ** |** |      ** |           "
	@echo "        \******\  ******** |**\**\** ** |******** |*****\    ** |           "
	@echo "         \____**\ **  __** |** \***  ** |**  __** |**  __|   ** |           "
	@echo "        **\   ** |** |  ** |** |\*  /** |** |  ** |** |      ** |           "
	@echo "        \******  |** |  ** |** | \_/ ** |** |  ** |********\ ********\      "
	@echo "         \______/ \__|  \__|\__|     \__|\__|  \__|\________|\________|     $(WHITE)"

