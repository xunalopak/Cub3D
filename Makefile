# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rchampli <rchampli@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/18 04:05:51 by rchampli          #+#    #+#              #
#    Updated: 2022/11/02 11:33:32 by rchampli         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = Cub3D

SRCS = $(shell find ./sources/ -type f -name "*.c" | cut -c 3-)

CC = gcc

CFLAG = -Wall -Wextra -Werror -lm -lbsd -lX11 -lXext -g -fsanitize=address

INC_DIR = ./includes/
MLX_DIR = ./mlx_linux/
LIB_DIR = ./libft/

LIB = $(addprefix $(LIB_DIR), libft.a)
MLX = $(addprefix $(MLX_DIR), libmlx.a)

OBJS	= $(SRCS:.c=.o)

all:		$(NAME)

$(NAME): $(OBJS)
	make -C $(LIB_DIR)
	make -C $(MLX_DIR)
	$(CC) -o $(NAME) -I $(MLX_DIR) -I $(LIB_DIR) -I $(INC_DIR) $(OBJS) $(LIB) $(MLX) $(MLX_DIR)libmlx.a $(CFLAG) 
%.o: %.c
	$(CC) $(CFLAG) -c -I$(INC_DIR) -I$(MLX_DIR) -I$(LIB_DIR) $< -o $@

clean:
	cd $(LIB_DIR) && make clean
	cd $(MLX_DIR) && make clean
	@rm -f $(OBJS)

fclean: clean
	cd $(LIB_DIR) && make fclean
	@rm -f $(NAME)

re:	fclean all

.PHONY: all clean fclean re
.SILENT: