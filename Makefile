# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alagroy- <alagroy-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/02/12 18:51:51 by alagroy-          #+#    #+#              #
#    Updated: 2019/03/15 16:57:30 by alagroy-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ls

SRCS = bt_sort.c ft_bt_ls.c ft_ls.c ft_lsl.c main.c rec.c start.c tools.c \
	   ft_display.c lstarg.c colors.c

OBJ = $(SRCS:.c=.o)

CC = gcc

INCLUDES = includes/

CFLAGS = -Wall -Wextra -Werror -I $(INCLUDES)

DFLAGS = -Wall -Werror -Wextra -g3 -fsanitize=address -I $(INCLUDES)

LFLAGS = -Wall -Werror -Wextra -g -I $(INCLUDES)

%.o: %.c
	@printf "\033[0;32m[ft_ls] Compilation [.o]\r"
	@$(CC) $(CFLAGS) -c $< -o $@
	@printf "\033[0;32m[ft_ls] Compilation [.o]\r"

all: $(NAME)

debug:
	$(CC) $(DFLAGS) -L . -lft $(SRCS) -o $(NAME)

leaks:
	$(CC) $(LFLAGS) -L . -lft $(SRCS) -o $(NAME)

$(NAME): $(OBJ)
	@printf "\033[0;32m[ft_ls] Compilation [OK]\n"
	@make -C libft
	@cp libft/libft.a .
	@printf "\033[0;32m[ft_ls] Linking [.o]\r"
	@$(CC) $(CFLAGS)  -L . -lft $(OBJ) -o $(NAME)
	@printf "\033[0;32m[ft_ls] Linking [OK]\n"

clean:
	@make -C libft clean
	@rm -f $(OBJ)
	@printf "\033[0;31m[ft_ls] Clean [OK]\n"

fclean: clean
	@make -C libft fclean
	@rm -f $(OBJ)
	@rm -f libft.a
	@printf "\033[0;31m[ft_ls] Fclean [OK]\n"

re: fclean all

.PHONY: fclean clean all re debug leaks
