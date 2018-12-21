# **************************************************************************** #
#                                                           LE - /             #
#                                                               /              #
#    Makefile                                         .::    .:/ .      .::    #
#                                                  +:+:+   +:    +:  +:+:+     #
#    By: schebbal <marvin@le-101.fr>                +:+   +:    +:    +:+      #
#                                                  #+#   #+    #+    #+#       #
#    Created: 2018/11/14 10:53:12 by schebbal     #+#   ##    ##    #+#        #
#    Updated: 2018/12/01 18:17:46 by schebbal    ###    #+. /#+    ###.fr      #
#                                                          /                   #
#                                                         /                    #
# **************************************************************************** #

#Color
GREEN 	= \e[92m
END 	= \e[97m
END2	= \e[0m
GREEN2	= \e[92;7m


NAME = fillit

#Compil
CC = gcc
CFLAGS = -Wall -Werror -Wextra  

#-fsanitize=address -g 

#Dir
PATH_SRC = ./
HEADER = ./fillit.h

SRCF = fillit.c \
	   valid_tetriminos.c \
	   get_grid.c \
	   solve_tetriminos.c \
	   main.c \
	   get_next_line.c

SRC = $(addprefix $(PATH_SRC), $(SRCF))

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	@ make -s -C libft
	@ $(CC) -L ./libft/ -lft -o $(NAME) $(OBJ) 
	@printf "\napp built...................................................... \
	$(GREEN)[ok]$(END)\n"

clean:
	@ make -C libft/ clean
	@ rm -f $(OBJ)
	@printf "remove object.................................................. \
	$(GREEN)[ok]$(END)\n"

fclean: clean
	@ make -C libft/ fclean
	@ /bin/rm -f $(NAME)
#	@printf "remove libft................................................... \
#	$(GREEN)[ok]$(END)\n"

re: fclean all

.PHONY: all clean fclean re

.SILENT: $(OBJ)