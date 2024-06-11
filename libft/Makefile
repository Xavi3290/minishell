
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

PRINTF_MAKE= make --no-print-directory -C ft_printf
GNL_MAKE= make --no-print-directory -C get_next_line
GNL= get_next_line/libftget_next_line.a
PRINTF= ft_printf/libftprintf.a

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
	ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c 

OBJ = $(SRC:%.c=%.o)

all: $(NAME)

$(NAME): printf get_next_line $(OBJ) $(INCLUDE)
	@$(LIB) $(NAME) $(OBJ) $(GNL) $(PRINTF)
	@echo "\n$(LGREEN)Create $(NAME) ✔$(NONE)\n"

%.o: %.c $(INCLUDE)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -o $@ -c $<
	@echo "$(GREEN)File $< compiled ✔$(NONE)"

printf:
	@echo "$(ORANGE)\nCompilando ft_printf$(NONE)"
	@$(PRINTF_MAKE)

get_next_line:
	@echo "$(ORANGE)\nCompilando get_next_line$(NONE)"
	@$(GNL_MAKE)

clean:
	@$(RM) $(OBJ)
	@$(GNL_MAKE) clean
	@$(PRINTF_MAKE) clean

fclean: clean
	@$(RM) $(NAME)
	@$(PRINTF_MAKE) fclean
	@$(GNL_MAKE) fclean
	@echo "$(RED)$(NAME) Deleted$(NONE)"

re:	fclean all

.PHONY: all clean fclean re printf get_next_line