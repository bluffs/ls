# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jyakdi <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/09/06 11:40:46 by jyakdi            #+#    #+#              #
#    Updated: 2017/09/06 15:19:51 by jyakdi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ls
SRC = ft_ls.c ft_flag.c ft_tools.c
OBJ = $(SRC:.c=.o)
LIBFT = libft/libft.a
CC = gcc
OPTION = -c -Iinc/
FLAG =

all : $(NAME)

$(NAME) : $(OBJ)
	make -Clibft
	$(CC) -o $(NAME) $(FLAG) $(OBJ) $(LIBFT)

$(OBJ) : $(addprefix src/, $(SRC))
	$(CC) $(FLAG) $(OPTION) $(addprefix src/, $(SRC))

clean :
	make clean -Clibft
	rm -rf $(OBJ)

fclean : clean
	make fclean -Clibft
	rm -rf $(NAME)

re : fclean all
