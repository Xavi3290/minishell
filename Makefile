# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cgaratej <cgaratej@student.42barcel>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/21 19:54:24 by xroca-pe          #+#    #+#              #
#    Updated: 2024/06/10 22:46:18 by cgaratej         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

GNL= libft/get_next_line/libftget_next_line.a
PRINTF= libft/ft_printf/libftprintf.a

NAME = minishell
CC = cc
CFLAGS = -Wall -Werror -Wextra -fsanitize=address
RM = rm -f
INCLUDE = includes/minishell.h Makefile
LIBRARY = -Lreadline -lreadline -lhistory -ltermcap
LIBFT = libft/libft.a
BUILD_DIR = build

GREEN=\033[32m
LGREEN=\033[1;92m
ORANGE=\033[33m
RED = \033[1;91m
NONE=\033[0m

#SRC = src/main.c src/init.c src/tokenaizer.c src/tokenaizer2.c \
	  src/tokenaizer3.c src/free_data.c src/utils.c \
	  src/parse.c src/expand.c
SRC = $(shell find . -name '*.c')

DEPS = src/main.c src/init.c src/tokenaizer.c src/tokenaizer2.c \
	  src/tokenaizer3.c src/free_data.c src/utils.c \
	  src/parse.c src/expand.c
	  
OBJ = $(SRC:%.c=$(BUILD_DIR)/%.o)
DEPS = $(SRC:%.c=$(BUILD_DIR)/%.d)

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT) $(INCLUDE)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIBFT) $(GNL) $(PRINTF) $(LIBRARY)
	@echo "\n$(LGREEN)Create $(NAME) ✔$(NONE)"

$(BUILD_DIR)/%.o: %.c $(INCLUDE)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c -MMD -o $@ $<
	@echo "$(LGREEN)File $< compiled ✔$(NONE)"

$(LIBFT):
	@echo "$(ORANGE)\nCompilando libft$(NONE)"
	@make --no-print-directory -C libft/

clean:	libft_clean
	@$(RM) $(OBJ)
	@rm -rf $(BUILD_DIR)
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
