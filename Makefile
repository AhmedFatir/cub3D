# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: afatir <afatir@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/01 07:32:35 by afatir            #+#    #+#              #
#    Updated: 2023/10/22 15:36:48 by afatir           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= cub3D
LIB_FT	= libft_gcl_ptf/
LIB_FT_A= libft_gcl_ptf/libft_gcl_ptf.a

CC		= cc
CFLAGS	= -Wall -Werror -Wextra -fsanitize=address -g
MLX		= -lmlx -framework OpenGL -framework AppKit

MOBJS	= ${SRCS:%.c=objectF/%.o}
SRCS	= main.c linked_list.c fill_list.c parsing1_head.c parsing2_map.c parsing3_utils.c


mkdir := mkdir -p
all: $(NAME)

$(NAME): $(MOBJS)
	@$(mkdir) objectF
	@make -s -C $(LIB_FT)
	@$(CC) $(CFLAGS) $(LIB_FT_A) $(MLX) $(MOBJS) -o $(NAME)

objectF/%.o: %.c cub3d.h | objectF
	$(CC) $(CFLAGS) -c $< -o $@

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
