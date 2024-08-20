# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: xroca-pe <xroca-pe@student.42barcel>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/21 19:54:24 by xroca-pe          #+#    #+#              #
#    Updated: 2024/08/20 15:49:54 by xroca-pe         ###   ########.fr        #
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

SRC = src/main.c src/init.c src/tokenizer/tokenize_line.c src/tokenizer/token_operations.c \
	  src/tokenizer/token_word_and_parentheses.c src/utils/free_data.c src/utils/utils.c \
	  src/parsing/parse_tokens.c src/expand/expand_tokens.c src/built-ins/ft_env.c src/built-ins/ft_pwd.c \
	  src/built-ins/ft_cd.c src/expand/expand_variable.c src/expand/expand_utils.c src/built-ins/ft_export_utils.c\
	  src/expand/expand_wildcards.c src/errors/error_manager.c src/built-ins/ft_exit.c \
	  src/built-ins/ft_echo.c src/errors/syntax_manager.c src/errors/syntax_utils.c \
	  src/built-ins/ft_export.c src/built-ins/ft_unset.c \
	  src/parsing/handle_tokens.c src/parsing/command_utils.c src/parsing/command_creation.c src/utils/free_tools.c \
	  src/execution/execution_utils.c src/execution/process_management.c \
	  src/execution/command_execution.c src/signals/signals.c src/ft_herdoc.c \
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