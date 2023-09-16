# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vkhrabro <vkhrabro@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/24 22:15:16 by vkhrabro          #+#    #+#              #
#    Updated: 2023/09/16 20:08:22 by vkhrabro         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf
HEADER = fdf.h
LIBFT = libft/
MINILIBX = minilibx_macos/

SRC_F:= fdf get_next_line/get_next_line get_next_line/get_next_line_utils \
		drawing key_handles utility_functions utility_functions_2 utility_functions_3

FLAGS = -Wall -Wextra -Werror -g -MMD -Imlx
RM = rm -f
SRC = $(addsuffix .c, $(SRC_F))
OBJS = $(SRC:.c=.o)
DEPS = $(OBJS:.o=.d)

CC = gcc

%.o: %.c 
	@$(CC) $(FLAGS) -c $< -o $@

all: make_libs $(NAME)
	@echo "\033[1;32mThe project has been compiled successfully\033[0m"

make_libs:
	$(MAKE) -C $(LIBFT)
	$(MAKE) -C $(MINILIBX)
	@echo "\033[1;32mLibraries have been compiled successfully\033[0m"

$(NAME): $(OBJS) $(HEADER)
	$(CC) $(FLAGS) $(OBJS) -L$(LIBFT) -lft -L$(MINILIBX) -lmlx -framework OpenGL -framework AppKit -o $@

clean:
	$(RM) $(OBJS) $(DEPS)
	$(MAKE) -C $(LIBFT) clean
	$(MAKE) -C $(MINILIBX) clean

fclean: clean
	$(RM) $(NAME)
	$(MAKE) -C $(LIBFT) fclean

re: fclean all

.PHONY: re clean fclean all

-include $(DEPS)

