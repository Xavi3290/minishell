# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cgaratej <cgaratej@student.42barcel>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/21 19:54:24 by xroca-pe          #+#    #+#              #
#    Updated: 2024/08/14 11:06:18 by cgaratej         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = cc -g
CFLAGS = -Wall -Werror -Wextra -fsanitize=address -fsanitize=leak
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

BUILD_DIR = build

SRC = src/main.c src/init.c src/tokenaizer.c src/tokenaizer2.c \
	  src/tokenaizer3.c src/free_data.c src/utils.c \
	  src/parse.c src/expand.c src/built-ins/ft_env.c src/built-ins/ft_pwd.c \
	  src/built-ins/ft_cd.c src/expand2.c src/expand3.c src/built-ins/ft_export_utils.c\
	  src/expand4.c src/error_manager.c src/built-ins/ft_exit.c \
	  src/built-ins/ft_echo.c src/syntax_manager.c src/syntax_utils.c \
	  src/built-ins/ft_export.c src/built-ins/ft_unset.c \
	  src/parse2.c src/parse3.c src/parse4.c src/free_tools.c \
	  src/execution/execution_utils.c src/execution/process_management.c \
	  src/execution/command_execution.c src/signals.c src/ft_herdoc.c \
	  src/execution/exec_cmd_utils.c src/redirects_manager.c
	  
OBJ = $(SRC:%.c=$(BUILD_DIR)/%.o)
DEPS = $(SRC:%.c=$(BUILD_DIR)/$.d)

all: libft ${NAME}

$(NAME): $(OBJ) $(INCLUDE)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIBFT) $(LIBRARY)
	@echo "\n$(LGREEN)Create $(NAME) ✔$(NONE)\n"

$(BUILD_DIR)/%.o: %.c $(INCLUDE)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c -MMD -o $@ $<
	@echo "$(GREEN)File $< compiled ✔$(NONE)"

-include $(DEPS)

libft:
	@echo "$(ORANGE)\nCompilando libft$(NONE)"
	@$(LIBFT_MAKE)

clean:
	@$(RM) -r $(BUILD_DIR)
	@$(LIBFT_MAKE) clean
	@echo "$(RED)Deleted .o files and .d files$(NONE)"


fclean: clean
	@$(RM) $(NAME)
	@$(LIBFT_MAKE) fclean
	@echo "$(RED)$(NAME) Deleted$(NONE)"

re: fclean all

.PHONY: all clean fclean re libft