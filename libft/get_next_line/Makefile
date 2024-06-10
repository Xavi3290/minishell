# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cgaratej <cgaratej@student.42barcel>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/15 11:59:53 by cgaratej          #+#    #+#              #
#    Updated: 2024/04/15 12:00:59 by cgaratej         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=libftget_next_line.a
CC=cc
CFLGS=-Wall -Wextra -Werror
LIB=ar rcs
INCLUDE=Makefile get_next_line.h
RM=rm -f

GREEN=\033[0;32m
LGREEN=\033[1;92m
RED = \033[1;91m
NONE=\033[0m

SRC= get_next_line.c get_next_line_utils.c

OBJ=$(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	@$(LIB) $(NAME) $(OBJ)
	@echo "\n$(LGREEN)Create $(NAME) ✔\n$(NONE)"

%.o: %.c $(INCLUDE)
	@$(CC) $(CFLGS) -o $@ -c $<
	@echo "$(GREEN)File $< compiled ✔$(NONE)"

clean:
	@$(RM) $(OBJ)

fclean: clean
	@$(RM) $(NAME)
	@echo "$(RED)$(NAME) Deleted$(NONE)"
	
re: fclean all

.PHONY=all clean fclean re