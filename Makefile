# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rchampli <rchampli@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/18 04:05:51 by rchampli          #+#    #+#              #
#    Updated: 2022/11/27 22:04:41 by rchampli         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = Cub3D

SRCS = checker.c data_mlx_init.c event.c get_next_line.c intersect.c main.c parse_map.c parsing.c parsing_2.c quit.c render.c texture.c vec.c

CC = gcc

CFLAG = -Wall -Wextra -Werror -MD -O3 -g -fsanitize=address
LINFLAG = -lm -lbsd -lX11 -lXext
MACFLAG = -framework OpenGL -framework AppKit

INC_DIR = ./includes
SRC_DIR = ./sources
OBJ_DIR = ./.obj
LIB_DIR = ./libft
MLX_DIR_LIN = ./mlx_linux
MLX_DIR_MAC = ./mlx_macos

LIB := $(addprefix $(LIB_DIR)/, libft.a)
MLX_LIN := $(addprefix $(MLX_DIR_LIN)/, libmlx.a)
MLX_MAC := $(addprefix $(MLX_DIR_MAC)/, libmlx.a)

OBJS	:= $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))
DEPS	:= $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.d))

all:		$(NAME)

linux: $(OBJS) $(LIB) $(MLX_LIN)
	$(CC) -o $(NAME) -I $(MLX_DIR_LIN) -I $(LIB_DIR) -I $(INC_DIR) $^ $(MLX_DIR_LIN)/libmlx.a $(CFLAG) $(LINFLAG)

$(NAME): $(OBJS) $(LIB) $(MLX_MAC)
	$(CC) -o $(NAME) -I $(MLX_DIR_MAC) -I $(LIB_DIR) -I $(INC_DIR) $^ $(MLX_DIR_MAC)/libmlx.a $(CFLAG) $(MACFLAG)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c Makefile | $(OBJ_DIR)
	$(CC) $(CFLAG) -c -I$(INC_DIR) -I$(MLX_DIR_MAC) -I$(LIB_DIR) $< -o $@

$(LIB):
	make -C $(LIB_DIR)

$(MLX_LIN):
	make -C $(MLX_DIR_LIN)

$(MLX_MAC):
	make -C $(MLX_DIR_MAC)

$(OBJ_DIR):
	mkdir -p $@

clean:
	make -C $(LIB_DIR) clean
	make -C $(MLX_DIR_LIN) clean
	make -C $(MLX_DIR_MAC) clean
	rm -rf $(OBJ_DIR)

fclean: clean
	make -C $(LIB_DIR) fclean
	rm -f $(NAME)

re:	fclean all

.PHONY: all clean fclean re
#.SILENT:
-include $(DEPS)
