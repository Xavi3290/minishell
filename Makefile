# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cgaratej <cgaratej@student.42barcel>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/21 19:54:24 by xroca-pe          #+#    #+#              #
#    Updated: 2024/06/12 16:20:10 by cgaratej         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = cc
CFLAGS = -Wall -Werror -Wextra -fsanitize=address
RM = rm -f
INCLUDE = includes/minishell.h Makefile
LIBRARY = -Lreadline -lreadline -lhistory -ltermcap
LIBFT = libft/libft.a
LIBFT_MAKE = make --no-print-directory -C libft/

GREEN=\033[32m
LGREEN=\033[1;92m
ORANGE=\033[33m
RED = \033[1;91m
NONE=\033[0m

SRC = src/main.c src/init.c src/tokenaizer.c src/tokenaizer2.c \
	  src/tokenaizer3.c src/free_data.c src/utils.c \
	  src/parse.c src/expand.c src/built-ins/env.c

OBJ = $(SRC:%.c=%.o)
DEPS = $(SRC:%.c=$.d)

all: ${NAME}

$(NAME): libft $(OBJ) $(INCLUDE)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIBFT) $(LIBRARY)
	@echo "\n$(LGREEN)Create $(NAME) ✔$(NONE)\n"

%.o: %.c $(INCLUDE)
	@$(CC) $(CFLAGS) -c -MMD -o $@ $<
	@echo "$(GREEN)File $< compiled ✔$(NONE)"

-include $(DEPS)

libft:
	@echo "$(ORANGE)\nCompilando libft$(NONE)"
	@$(LIBFT_MAKE)

clean:
	@$(RM) $(OBJ)
	@$(RM) src/*.d
	@$(LIBFT_MAKE) clean
	@echo "$(RED)Deleted .o files$(NONE)"
	@echo "$(RED)Deleted .d files$(NONE)"


fclean: clean
	@$(RM) $(NAME)
	@$(LIBFT_MAKE) fclean
	@echo "$(RED)$(NAME) Deleted$(NONE)"

re: fclean all

.PHONY: all clean fclean re libft