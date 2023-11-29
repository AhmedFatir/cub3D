# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: khbouych <khbouych@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/01 07:32:35 by afatir            #+#    #+#              #
#    Updated: 2023/11/29 17:43:44 by khbouych         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= cub3D
LIB_FT	= libft_gcl_ptf/
LIB_FT_A= libft_gcl_ptf/libft_gcl_ptf.a

MLX = MLX42/build/libmlx42.a
FLAG_MLX = -framework Cocoa -framework OpenGL -framework IOKit -lglfw
INCLUDE = -I/Users/${USER}/.brew/Cellar/glfw/3.3.8/include/GLFW
LIB = -L/Users/${USER}/.brew/Cellar/glfw/3.3.8/lib

CC		= cc
CFLAGS	= -Wall -Werror -Wextra -O3 -ffast-math #-fsanitize=address -g

MOBJS	= ${SRCS:%.c=%.o}
SRCS	= main.c execution/execution.c execution/mouvement.c execution/2dmap.c execution/raycasting.c execution/render.c \
			parsing/o_list.c parsing/o_map.c parsing/outils_.c parsing/outils.c parsing/p_map.c parsing/p_map1.c parsing/p_map2.c \
			parsing/p_textures1.c parsing/p_textures2.c parsing/par1.c parsing/parsing.c


all: $(NAME)

$(NAME): $(MOBJS)
	@make -s -C $(LIB_FT)
	@$(CC) $(CFLAGS) $(FLAG_MLX) $(MOBJS) $(LIB_FT_A) $(MLX) $(LIB) -o $(NAME)

%.o: %.c cub3d.h
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@


clean:
	@make clean -s -C $(LIB_FT)
	@rm -f $(MOBJS)

fclean: clean
	@make fclean -s -C $(LIB_FT)
	@rm -f $(NAME)

git :
	git add .
	git commit -m "khbouych"
	git push

re: fclean all
