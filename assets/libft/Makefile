# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: maoliiny <maoliiny@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/15 11:05:26 by maoliiny          #+#    #+#              #
#    Updated: 2025/05/15 17:43:29 by maoliiny         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRCS = ft_atoi.c ft_isalpha.c ft_itoa.c ft_memmove.c ft_putnbr_fd.c  ft_strdup.c    ft_strlcpy.c  ft_strnstr.c \
	   ft_tolower.c  ft_bzero.c    ft_isascii.c  ft_memchr.c  ft_memset.c      ft_putstr_fd.c  ft_striteri.c  \
	   ft_strlen.c   ft_strrchr.c  ft_toupper.c ft_calloc.c   ft_isdigit.c  ft_memcmp.c  ft_putchar_fd.c  \
	   ft_split.c      ft_strjoin.c   ft_strmapi.c  ft_strtrim.c  ft_isalnum.c  ft_isprint.c  ft_memcpy.c \
	   ft_putendl_fd.c  ft_strchr.c     ft_strlcat.c   ft_strncmp.c  ft_substr.c   get_next_line.c \
	   get_next_line_utils.c ft_printf.c ft_printf_utils.c ft_lstnew_bonus.c ft_lstadd_front_bonus.c \
	   ft_lstsize_bonus.c ft_lstlast_bonus.c ft_lstadd_back_bonus.c ft_lstdelone_bonus.c \
	   ft_lstclear_bonus.c ft_lstiter_bonus.c ft_lstmap_bonus.c ft_strtod.c 

#BONUS_C = ft_lstnew_bonus.c ft_lstadd_front_bonus.c ft_lstsize_bonus.c ft_lstlast_bonus.c ft_lstadd_back_bonus.c ft_lstdelone_bonus.c ft_lstclear_bonus.c ft_lstiter_bonus.c ft_lstmap_bonus.c 

#BONUS = ${BONUS_C:.c=.o}
#.SECONDARY: ${BONUS}

OBJS = ${SRCS:.c=.o}
.SECONDARY: ${OBJS}

CC = cc

RM = rm -f

CFLAGS = -Wall -Wextra -Werror

all:	${NAME}

.c.o:
	${CC} ${CFLAGS} -I. -c $< -o ${<:.c=.o}

$(NAME): ${OBJS}
	ar rcs ${NAME} ${OBJS}
	
clean:
	${RM} ${OBJS} ${BONUS}

#bonus:	${OBJS} ${BONUS} 
#	ar rcs ${NAME} ${OBJS} ${BONUS}

fclean:	clean
	${RM} ${NAME}
	
re:		fclean all

.PHONY: all clean fclean re
