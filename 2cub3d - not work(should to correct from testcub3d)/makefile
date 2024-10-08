# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rkrechun <rkrechun@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/11 14:14:12 by rkrechun          #+#    #+#              #
#    Updated: 2024/09/11 15:32:11 by rkrechun         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Project name
NAME = cub3D

# Compiler and flags
CC = gcc  -g -fsanitize=address
FLAGS = -Wall -Wextra -Werror -I$(MLX_DIR) -I$(HEADER_DIR)
RM = rm -rf

# Header files
HEADER_SRCS = cub3d.h
HEADER_DIR = libc/
HEADER =  $(HEADER_SRCS)

# Source files
MPATH_SRCS = cub3d.c keys.c render.c textures.c
MPATH_DIR = sourse/
MPATH =  $(MPATH_SRCS)
OBJ_M = $(MPATH:.c=.o)

# MLX library path
MLX_DIR = mlx

# MLX library linking flags (adjust if needed)
MLX_LIBS = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm

# Rule to create .o files from .c files
%.o: %.c $(HEADER) Makefile
	@$(CC) $(FLAGS) -c $< -o $@

# Rule to link .o files into the final executable
$(NAME): $(OBJ_M)
	@$(CC) $(OBJ_M) $(MLX_LIBS) -o $(NAME)

# Default rule to build the project
all: $(NAME)

# Rule to remove object files
clean:	
	@$(RM) $(OBJ_M)

# Rule to remove object files and executable
fclean: clean
	@$(RM) $(NAME)

# Rule to recompile the project
re: fclean all

.PHONY: all clean fclean re
