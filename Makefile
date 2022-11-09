# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rchampli <rchampli@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/18 04:05:51 by rchampli          #+#    #+#              #
#    Updated: 2022/11/09 16:11:06 by jalamell         ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

NAME = Cub3D

SRCS := $(subst $(SRC_DIR)/,,$(shell find $(SRC_DIR) -type f -name "*.c" | tr "\n" " "))

CC = gcc

CFLAG = -Wall -Wextra -Werror -MD -g -fsanitize=address
LINFLAG = -lm -lbsd -lX11 -lXext
MACFLAG = -framework OpenGL -framework AppKit

INC_DIR = ./includes
SRC_DIR = ./sources
MLX_DIR = ./mlx_linux
LIB_DIR = ./libft
OBJ_DIR = ./.obj

LIB := $(addprefix $(LIB_DIR)/, libft.a)
MLX := $(addprefix $(MLX_DIR)/, libmlx.a)

OBJS	:= $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))
DEPS	:= $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.d))

all:		$(NAME)

linux: $(OBJS) $(LIB) $(MLX)
	$(CC) -o $(NAME) -I $(MLX_DIR) -I $(LIB_DIR) -I $(INC_DIR) $^ $(MLX_DIR)/libmlx.a $(CFLAG) $(LINFLAG)

$(NAME): $(OBJS) $(LIB) $(MLX)
	$(CC) -o $(NAME) -I $(MLX_DIR) -I $(LIB_DIR) -I $(INC_DIR) $^ $(MLX_DIR)/libmlx.a $(CFLAG) $(MACFLAG)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c Makefile | $(OBJ_DIR)
	$(CC) $(CFLAG) -c -I$(INC_DIR) -I$(MLX_DIR) -I$(LIB_DIR) $< -o $@

$(LIB):
	make -C $(LIB_DIR)

$(MLX):
	make -C $(MLX_DIR)

$(OBJ_DIR):
	mkdir -p $@

clean:
	make -C $(LIB_DIR) clean
	make -C $(MLX_DIR) clean
	rm -rf $(OBJ_DIR)

fclean: clean
	make -C $(LIB_DIR) fclean
	rm -f $(NAME)

re:	fclean all

.PHONY: all clean fclean re
#.SILENT:
-include $(DEPS)
