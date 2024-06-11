# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cgaratej <cgaratej@student.42barcel>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/21 19:54:24 by xroca-pe          #+#    #+#              #
#    Updated: 2024/06/11 11:44:38 by cgaratej         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = cc
CFLAGS = -Wall -Werror -Wextra -fsanitize=address
RM = rm -f
INCLUDE = includes/minishell.h Makefile
LIBRARY = -Lreadline -lreadline -lhistory -ltermcap
LIBFT = libft/libft.a

GREEN=\033[32m
LGREEN=\033[1;92m
ORANGE=\033[33m
RED = \033[1;91m
NONE=\033[0m

SRC = src/main.c src/init.c src/tokenaizer.c src/tokenaizer2.c \
	  src/tokenaizer3.c src/free_data.c src/utils.c \
	  src/parse.c src/expand.c

OBJ = $(SRC:%.c=%.o)
DEPS = $(SRC:%.c=$.d)

all: ${NAME}

$(NAME): $(LIBFT) $(OBJ) $(INCLUDE)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIBFT) $(LIBRARY)
	@echo "\n$(LGREEN)Create $(NAME) ✔$(NONE)\n"

%.o: %.c $(INCLUDE)
	@$(CC) $(CFLAGS) -c -MMD -o $@ $<
	@echo "$(GREEN)File $< compiled ✔$(NONE)"

-include $(DEPS)

$(LIBFT):
	@echo "$(ORANGE)\nCompilando libft$(NONE)"
	@make --no-print-directory -C libft/

clean:	libft_clean
	@$(RM) $(OBJ) $(DEPS)
	@echo "$(RED)Deleted .o files$(NONE)"
	@echo "$(RED)Deleted .d files$(NONE)"

libft_clean:
	@make --no-print-directory clean -C libft/

fclean: clean libft_fclean
	@$(RM) $(NAME)
	@echo "$(RED)$(NAME) Deleted$(NONE)"

libft_fclean:
	@make --no-print-directory fclean -C libft/

re: fclean all

.PHONY: all clean fclean re