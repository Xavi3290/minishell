# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: xroca-pe <xroca-pe@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/21 19:54:24 by xroca-pe          #+#    #+#              #
#    Updated: 2024/05/22 15:38:14 by xroca-pe         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = cc
CFLAGS = -Wall -Werror -Wextra 
RM = rm -f
INCLUDE = includes/minishell.h Makefile
LIBRARY = -lreadline -lhistory
LIBFT = libft/libft.a

SRC = src/main.c src/init.c src/tokenaizer.c src/free_data.c src/utils.c
	  
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
