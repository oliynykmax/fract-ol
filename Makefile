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

SRCS = fract-ol.c \

LIBFT_SRCS = libft/ft_atoi.c \
			 libft/ft_bzero.c \
			 libft/ft_calloc.c \
			 libft/ft_isalnum.c \
			 libft/ft_isalpha.c \
			 libft/ft_isascii.c \
			 libft/ft_isdigit.c \
			 libft/ft_isprint.c \
			 libft/ft_itoa.c \
			 libft/ft_lstadd_back_bonus.c \
			 libft/ft_lstadd_front_bonus.c \
			 libft/ft_lstclear_bonus.c \
			 libft/ft_lstdelone_bonus.c \
			 libft/ft_lstiter_bonus.c \
			 libft/ft_lstlast_bonus.c \
			 libft/ft_lstmap_bonus.c \
			 libft/ft_lstnew_bonus.c \
			 libft/ft_lstsize_bonus.c \
			 libft/ft_memchr.c \
			 libft/ft_memcmp.c \
			 libft/ft_memcpy.c \
			 libft/ft_memmove.c \
			 libft/ft_memset.c \
			 libft/ft_printf.c \
			 libft/ft_printf_utils.c \
			 libft/ft_putchar_fd.c \
			 libft/ft_putendl_fd.c \
			 libft/ft_putnbr_fd.c \
			 libft/ft_putstr_fd.c \
			 libft/ft_split.c \
			 libft/ft_strdup.c \
			 libft/ft_striteri.c \
			 libft/ft_strjoin.c \
			 libft/ft_strlcat.c \
			 libft/ft_strlcpy.c \
			 libft/ft_strlen.c \
			 libft/ft_strncmp.c \
			 libft/ft_strnstr.c \
			 libft/ft_strrchr.c \
			 libft/ft_strtrim.c \
			 libft/ft_substr.c \
			 libft/ft_strmapi.c \
			 libft/ft_tolower.c \
			 libft/ft_toupper.c \
			 libft/get_next_line.c \
			 libft/get_next_line_utils.c

OBJS = $(SRCS:.c=.o)
.SECONDARY = $(OBJS) 
LIBFT_OBJS = $(LIBFT_SRCS:.c=.o)
.SECONDARY = $(LIBFT_OBJS) 
INCLUDES = -I./libft

all: $(NAME)

$(NAME): $(OBJS) libft/libft.a
	$(CC) $(CFLAGS) $(OBJS) libft/libft.a libmlx42.a -Iinclude -ldl -lglfw -pthread -lm -o $(NAME)

libft/libft.a: $(LIBFT_OBJS)
	@make -C libft

%.o: %.c push_swap.h
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJS)
	@make clean -C libft

fclean: clean
	rm -f $(NAME)
	rm -f libft/libft.a
	@make fclean -C libft

re: fclean all

.PHONY: all clean fclean re

