NAME	= mlx
CC		= cc
MLX		= -lmlx -framework OpenGL -framework AppKit

MOBJS	= ${SRCS:%.c=%.o}
SRCS	= zmlx.c

all: $(NAME)

$(NAME): $(MOBJS)
	@$(CC) $(MLX) $(MOBJS) -o $(NAME)

%.o: %.c
	$(CC) -c $< -o $@

clean:
	@rm -f $(MOBJS)

fclean: clean
	@rm -f $(NAME)

re: fclean all