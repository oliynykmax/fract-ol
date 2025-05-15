# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: maoliiny <maoliiny@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/09 19:29:32 by maoliiny          #+#    #+#              #
#    Updated: 2025/05/15 16:14:13 by maoliiny         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = fract-ol

CC = cc
CFLAGS = -Wall -Wextra -Werror

SRCS = srcs/fract-ol.c srcs/colors.c
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

srcs/fract-ol.o: srcs/fract-ol.c incl/fract-ol.h

clean:
	@rm -f $(OBJS)
	@make clean -C assets/libft
	@rm -rf assets/MLX42/build

fclean: clean
	@rm -f $(NAME)
	@make fclean -C assets/libft

re: fclean all

.PHONY: all clean fclean re



