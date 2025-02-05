MACOS_FLAGS = -framework Cocoa -framework OpenGL -framework IOKit -lglfw
MLX_A = MLXGLFW/MacOS/mlx/libmlx42.a
GLFW_P = MLXGLFW/MacOS/glfw
GLFW_L = -IMLXGLFW/MacOS/glfw/3.4/include/GLFW
GLFW_A = -LMLXGLFW/MacOS/glfw/3.4/lib

CFLAGS	= cc -Wall -Werror -Wextra -O3 -ffast-math

LIB_FT	= libft_gcl_ptf/
LIB_FT_A= libft_gcl_ptf/libft_gcl_ptf.a

NAME	= cub3D
NAME_B	= cub3D_bonus
HEADER_FILES = cub3d.h cub3d_bonus.h
SRCS	= main.c execution/execution.c execution/mouvement.c execution/raycasting.c execution/render.c execution/render2.c execution/execfree.c \
			parsing/o_list.c parsing/o_map.c parsing/outils.c parsing/p_map.c parsing/p_map1.c parsing/p_map2.c \
			parsing/p_textures1.c parsing/p_textures2.c parsing/par1.c parsing/parsing.c

SRCS_B	= bonus/main_bonus.c bonus/execution_bonus.c bonus/mouvement_bonus.c bonus/2dmap_bonus.c bonus/raycasting_bonus.c bonus/render_bonus.c bonus/render2_bonus.c bonus/execfree_bonus.c \
			parsing/o_list.c parsing/o_map.c parsing/outils.c parsing/p_map.c parsing/p_map1.c parsing/p_map2.c \
			parsing/p_textures1.c parsing/p_textures2.c parsing/par1.c parsing/parsing.c

MOBJS	= ${SRCS:%.c=%.o}
MOBJS_B	= ${SRCS_B:%.c=%.o}


all: $(NAME)
	@mkdir -p /tmp/LTC/opt && cp -rf $(GLFW_P) /tmp/LTC/opt

$(NAME): $(MOBJS)
	@make -s -C $(LIB_FT)
	@$(CFLAGS) $(MACOS_FLAGS) $(LIB_FT_A) $(MLX_A) $(GLFW_A) $(MOBJS) -o $(NAME)

%.o: %.c $(HEADER_FILES)
	$(CFLAGS) $(GLFW_L) -c $< -o $@

bonus: $(MOBJS_B)
	@mkdir -p /tmp/LTC/opt && cp -rf $(GLFW_P) /tmp/LTC/opt
	@make -s -C $(LIB_FT)
	@$(CFLAGS) $(MACOS_FLAGS) $(LIB_FT_A) $(MLX_A) $(GLFW_A) $(MOBJS_B) -o $(NAME_B)

clean:
	@make clean -s -C $(LIB_FT)
	@rm -f $(MOBJS) $(MOBJS_B)

fclean: clean
	@make fclean -s -C $(LIB_FT)
	@rm -f $(NAME) $(NAME_B) mini

re: fclean all

mini:
	@$(CFLAGS) $(MACOS_FLAGS) $(MLX_A) $(GLFW_A) mini_cub3D.c -o mini

.PHONY: all clean fclean re bonus