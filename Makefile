# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: maoliiny <maoliiny@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/09 19:29:32 by maoliiny          #+#    #+#              #
#    Updated: 2025/05/12 11:23:24 by maoliiny         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fract-ol

CC = cc
CFLAGS = -Wall -Wextra -Werror

SRCS = srcs/fract-ol.c
OBJS = $(SRCS:.c=.o)

INCLUDES = -Iincl -Iassets/libft
MLX42 = assets/MLX42/libmlx42.a

all: $(NAME)

$(NAME): $(OBJS) assets/libft/libft.a
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) assets/libft/libft.a $(MLX42) -ldl -lglfw -pthread -lm -o $(NAME)

assets/libft/libft.a:
	@make -C assets/libft

srcs/%.o: srcs/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Ensure object files are rebuilt if headers change
srcs/fract-ol.o: srcs/fract-ol.c incl/fract-ol.h

clean:
	rm -f $(OBJS)
	@make clean -C assets/libft

fclean: clean
	rm -f $(NAME)
	rm -f assets/libft/libft.a
	@make fclean -C assets/libft

re: fclean all

.PHONY: all clean fclean re


