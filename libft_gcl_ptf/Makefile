# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: afatir <afatir@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/15 23:01:07 by afatir            #+#    #+#              #
#    Updated: 2023/03/02 13:59:55 by afatir           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= libft_gcl_ptf.a
CC		= cc
CFLAGS	= -Wall -Wextra -Werror
RM		= rm -f
OBJS	= ${SRCS:%.c=%.o}
SRCS	= ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c \
			ft_strlen.c ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c \
			ft_strlcpy.c ft_strlcat.c ft_toupper.c ft_tolower.c ft_strchr.c \
			ft_strrchr.c ft_strncmp.c ft_memchr.c ft_memcmp.c ft_strnstr.c ft_atoi.c \
			ft_calloc.c ft_strdup.c ft_substr.c ft_strtrim.c ft_split.c ft_itoa.c ft_strcmp.c\
			ft_strmapi.c ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
			get_next_line_utils.c get_next_line.c \
			ft_putchar.c ft_putstr.c ft_put_deci.c ft_put_unsigned.c \
			ft_put_hexa.c ft_put_ad.c ft_printf.c ft_free_all.c


all:		${NAME}
${NAME}:	${OBJS}
			@ar rcs ${NAME} ${OBJS}
%.o: %.c	libft.h
			${CC} ${CFLAGS}  -c $< -o $@
clean:
			${RM} ${OBJS}
fclean:		clean
			${RM} ${NAME}
re:			fclean all
