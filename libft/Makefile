
# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cgaratej <cgaratej@student.42barcel>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/17 12:27:13 by cgaratej          #+#    #+#              #
#    Updated: 2024/01/29 18:40:12 by cgaratej         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=libft.a
CC=cc
CFLAGS=-Wall -Wextra -Werror
INCLUDE= Makefile libft.h
LIB=ar rcs
RM=rm -f

GREEN=\033[32m
LGREEN=\033[1;92m
ORANGE=\033[33m
RED = \033[1;91m
NONE=\033[0m

SRC=ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c ft_strlen.c \
	ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c ft_strlcpy.c ft_strlcat.c \
	ft_toupper.c ft_tolower.c ft_strchr.c ft_strrchr.c ft_strncmp.c ft_memchr.c \
	ft_memcmp.c ft_strnstr.c ft_atoi.c ft_calloc.c ft_strdup.c ft_substr.c \
	ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c ft_striteri.c \
	ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
	get_next_line.c get_next_line_utils.c

OBJ = $(SRC:%.c=%.o)

all: $(NAME)

$(NAME): $(OBJ) $(INCLUDE)
	@$(LIB) $(NAME) $(OBJ) $(GNL) $(PRINTF)
	@echo "\n$(LGREEN)Create $(NAME) ✔$(NONE)\n"

%.o: %.c $(INCLUDE)
	@$(CC) $(CFLAGS) -o $@ -c $<
	@echo "$(GREEN)File $< compiled ✔$(NONE)"

clean:
	@$(RM) $(OBJ)

fclean: clean
	@$(RM) $(NAME)
	@echo "$(RED)$(NAME) Deleted$(NONE)"

re:	fclean all

.PHONY: all clean fclean re