# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cgaratej <cgaratej@student.42barcel>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/21 19:54:24 by xroca-pe          #+#    #+#              #
#    Updated: 2024/06/10 16:38:47 by cgaratej         ###   ########.fr        #
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

SRC = src/main.c \
	  src/init.c \
	  src/tokenaizer.c \
	  src/tokenaizer2.c \
	  src/tokenaizer3.c \
	  src/free_data.c \
	  src/utils.c \
	  src/parse.c \
	  src/expand.c
	  
OBJ := $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT) $(INCLUDE)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIBFT) $(GNL) $(PRINTF) $(LIBRARY)

%.o: %.c $(INCLUDE)
	$(CC) $(CFLAGS) -c -o $@ $<

$(LIBFT):
	make -C libft/

clean:	libft_clean
	$(RM) $(OBJ)

libft_clean:
	make clean -C libft/

fclean: clean libft_fclean
	$(RM) $(NAME)

libft_fclean:
	make fclean -C libft/

re: fclean all

.PHONY: all clean fclean re
