# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: afatir <afatir@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/01 07:32:35 by afatir            #+#    #+#              #
#    Updated: 2023/11/25 17:44:25 by afatir           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= cub3D
LIB_FT	= libft_gcl_ptf/
LIB_FT_A= libft_gcl_ptf/libft_gcl_ptf.a

MLX = /Users/afatir/Desktop/MLX42/build/libmlx42.a
FLAG_MLX = -framework Cocoa -framework OpenGL -framework IOKit -lglfw
INCLUDE = -I/Users/${USER}/.brew/Cellar/glfw/3.3.8/include/GLFW
LIB = -L/Users/${USER}/.brew/Cellar/glfw/3.3.8/lib

CC		= cc
CFLAGS	= -Wall -Werror -Wextra #-fsanitize=address -g

MOBJS	= ${SRCS:%.c=objectF/%.o}
SRCS	= main.c linked_list.c fill_list.c parsing.c pars_map.c pars_colors.c \
		pars_utils.c pars_utils2.c execution.c mouvement.c 2dmap.c raycasting.c render.c


mkdir := mkdir -p
all: $(NAME)

$(NAME): $(MOBJS)
	@$(mkdir) objectF
	@make -s -C $(LIB_FT)
	@$(CC) $(CFLAGS) $(FLAG_MLX) $(MOBJS) $(LIB_FT_A) $(MLX) $(LIB) -o $(NAME)

objectF/%.o: %.c cub3d.h | objectF
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

objectF:
	@$(mkdir) objectF

clean:
	@make clean -s -C $(LIB_FT)
	@rm -f $(MOBJS)
	@rm -rf objectF

fclean: clean
	@make fclean -s -C $(LIB_FT)
	@rm -f $(NAME)

re: fclean all
