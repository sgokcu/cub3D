# INCLUDES_MAC = -Imlx

NAME = cub3D
LIBFT = libft/libft.a
CC = gcc

CFLAGS = -Wall -Werror -Wextra #-g -fsanitize=address


MLX_FLAGS_MAC = -Lmlx -lmlx -lXext -lX11 -lm

SRCS = $(shell find src -type f -name "*.c") get_next_line/get_next_line.c get_next_line/get_next_line_utils.c

OBJ = $(SRCS:.c=.o)

%.o: %.c
	 $(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ)
	make -C mlx
	make -C libft
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(MLX_FLAGS_MAC) -o $(NAME)


all: $(NAME)

fclean: clean
	rm -rf libft/*.a
	rm -rf get_next_line/*.a
	rm -rf $(NAME)

clean:
	# make clean -C mlx
	rm -rf src/*.o src/parse/*.o
	rm -rf libft/*.o
	rm -rf get_next_line/*.o

re: fclean all

.PHONY: all clean fclean re