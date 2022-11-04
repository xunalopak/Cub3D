# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rchampli <rchampli@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/02 15:54:47 by rchampli          #+#    #+#              #
#    Updated: 2022/10/23 09:49:33 by rchampli         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

CC = gcc
FLAGS = -Wall -Wextra -Werror -g3 -fsanitize=address
AR = ar rcs
RM = rm -f

FILES = $(shell find ./ -type f -name "*.c" | cut -c 3-)

			
SRCS_DIR = ./
SRCS = $(addprefix $(SRCS_DIR), $(FILES))

OBJS_DIR = ./
OBJS = $(addprefix $(OBJS_DIR), $(FILES:.c=.o))

.c.o: $(SRCS)
	$(CC) $(CFLAGS) -c -o $@ $<

$(NAME): $(OBJS)
	$(AR) $@ $^

all: $(NAME)

bonus: $(OBJS_B)
	$(AR) $(NAME) $^
	
clean:
	$(RM) $(OBJS) $(OBJS_B)
	
fclean: clean
	$(RM) $(NAME)

re: clean all

.PHONY: all bonus clean fclean re