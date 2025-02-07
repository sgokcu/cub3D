MLX_FLAGS = -Lmlx -lmlx -lXext -lX11 -lm
MAKEFLAGS += --no-print-directory
CFLAGS = -Wall -Werror -Wextra
LIBFT = libft/libft.a
NAME = cub3D
CC = gcc

SRCS = src/execute/exec1.c src/execute/exec2.c src/execute/exec3.c src/execute/exec4.c src/execute/exec5.c src/execute/exec6.c src/execute/exec7.c src/execute/exec8.c src/execute/exec9.c \
src/parse/basic_utils.c src/parse/cases.c src/parse/general.c src/parse/general1.c src/parse/general3.c src/parse/malloc.c src/parse/map_filler.c src/parse/parse_main.c src/parse/square_map.c src/parse/texture_filler.c src/parse/verifiers.c \
get_next_line/get_next_line.c get_next_line/get_next_line_utils.c \
src/main.c

OBJ = $(SRCS:.c=.o)

%.o: %.c
	 $(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ)
	make -C mlx > /dev/null 2> /dev/null
	make -C libft
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(MLX_FLAGS) -o $(NAME)


all: $(NAME)

fclean: clean
	make -C libft fclean
	rm -rf $(NAME)

clean:
	# make clean -C mlx
	rm -rf $(OBJ)
	make -C libft clean

re: fclean all

.PHONY: all clean fclean re