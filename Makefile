# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: xroca-pe <xroca-pe@student.42barcel>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/21 19:54:24 by xroca-pe          #+#    #+#              #
#    Updated: 2024/06/10 14:33:24 by xroca-pe         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

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
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIBFT) $(LIBRARY)

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
