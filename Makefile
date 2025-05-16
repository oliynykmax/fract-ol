# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: maoliiny <maoliiny@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/09 19:29:32 by maoliiny          #+#    #+#              #
#    Updated: 2025/05/16 16:13:18 by maoliiny         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = fractol

CC = cc

CFLAGS = -Wall -Wextra -Werror -O3 -march=native -ffast-math

SRCS = srcs/fractal.c srcs/colors.c srcs/utils.c srcs/hooks.c
OBJS = $(SRCS:.c=.o)

INCLUDES = -Iincl -Iassets/libft -Iassets/MLX42/include
MLX42 = assets/MLX42/build/libmlx42.a 
.SECONDARY : MLX42
all: $(MLX42) assets/libft/libft.a $(NAME)

$(MLX42):
	@cmake -S assets/MLX42 -B assets/MLX42/build
	@make -C assets/MLX42/build -j4

$(NAME): $(OBJS) assets/libft/libft.a $(MLX42)
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) assets/libft/libft.a $(MLX42) -ldl -lglfw -pthread -lm -o $(NAME)

assets/libft/libft.a:
	@make -C assets/libft

srcs/%.o: srcs/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

srcs/fract-ol.o: srcs/fract-ol.c incl/fractal.h

clean:
	@rm -f $(OBJS)
	@make clean -C assets/libft
	@rm -rf assets/MLX42/build

fclean: clean
	@rm -f $(NAME)
	@make fclean -C assets/libft

re: fclean all

.PHONY: all clean fclean re



