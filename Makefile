# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jyakdi <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/09/06 11:40:46 by jyakdi            #+#    #+#              #
#    Updated: 2017/10/11 17:47:23 by jyakdi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ls
SRC = ft_ls.c ft_flag.c ft_tools.c ft_binary_tree.c ft_init.c ft_read_dir.c \
	 ft_print_rights.c ft_padding.c ft_tools2.c ft_tools3.c ft_register_tree.c \
	 ft_register_time.c ft_open_dir.c ft_open_dir2.c ft_tools4.c
OBJ = $(SRC:.c=.o)
LIBFT = libft/libft.a
CC = gcc
OPTION = -c -Iinc/
FLAG = -Wall -Werror -Wextra

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
