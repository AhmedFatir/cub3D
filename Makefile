# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: afatir <afatir@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/01 07:32:35 by afatir            #+#    #+#              #
#    Updated: 2023/12/05 19:15:34 by afatir           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= cub3D
NAME_B	= cub3D_bonus
LIB_FT	= libft_gcl_ptf/
LIB_FT_A= libft_gcl_ptf/libft_gcl_ptf.a

MLX = MLX/libmlx42.a
FLAG_MLX = -framework Cocoa -framework OpenGL -framework IOKit -lglfw
INCLUDE = -I/Users/${USER}/.brew/Cellar/glfw/3.3.8/include/GLFW
LIB = -L/Users/${USER}/.brew/Cellar/glfw/3.3.8/lib

CC		= cc
CFLAGS	= -Wall -Werror -Wextra -O3 -ffast-math #-fsanitize=address -g

MOBJS	= ${SRCS:%.c=%.o}
MOBJS_B	= ${SRCS_B:%.c=%.o}
SRCS	= main.c execution/execution.c execution/mouvement.c execution/raycasting.c execution/render.c execution/render2.c execution/execfree.c \
			parsing/o_list.c parsing/o_map.c parsing/outils.c parsing/p_map.c parsing/p_map1.c parsing/p_map2.c \
			parsing/p_textures1.c parsing/p_textures2.c parsing/par1.c parsing/parsing.c

SRCS_B	= bonus/main_bonus.c bonus/execution_bonus.c bonus/mouvement_bonus.c bonus/2dmap_bonus.c bonus/raycasting_bonus.c bonus/render_bonus.c bonus/render2_bonus.c bonus/execfree_bonus.c \
			parsing/o_list.c parsing/o_map.c parsing/outils.c parsing/p_map.c parsing/p_map1.c parsing/p_map2.c \
			parsing/p_textures1.c parsing/p_textures2.c parsing/par1.c parsing/parsing.c

all: $(NAME)

$(NAME): $(MOBJS)
	@make -s -C $(LIB_FT)
	@$(CC) $(CFLAGS) $(FLAG_MLX) $(MOBJS) $(LIB_FT_A) $(MLX) $(LIB) -o $(NAME)

%.o: %.c cub3d.h cub3d_bonus.h
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

bonus: $(MOBJS_B)
	@make -s -C $(LIB_FT)
	@$(CC) $(CFLAGS) $(FLAG_MLX) $(MOBJS_B) $(LIB_FT_A) $(MLX) $(LIB) -o $(NAME_B)

clean:
	@make clean -s -C $(LIB_FT)
	@rm -f $(MOBJS)
	@rm -f $(MOBJS_B)

fclean: clean
	@make fclean -s -C $(LIB_FT)
	@rm -f $(NAME)
	@rm -f $(NAME_B)

re: fclean all