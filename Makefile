# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jeongmin <jeongmin@student.42seoul.kr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/04 21:52:18 by wonyang           #+#    #+#              #
#    Updated: 2023/03/11 21:49:17 by jeongmin         ###   ########seoul.kr   #
#                                                                              #
# **************************************************************************** #

# define compile options
NAME		= cub3d
LIBFT		= libft
LIBFT_HEADER = libft.h
LIBFT_LIB	= $(LIBFT)/libft.a

GNL		   = get_next_line
GNL_HEADER = get_next_line.h

HEADERS		= -I$(LIBFT) \
			  -I$(GNL) \
			  -I./

LIBS		= -lft -L$(LIBFT)

CFLAGS		= -Wall -Werror -Wextra


# parsing part source files
PARSING_DIR		= parsing/

_PARSING_SRCS	= parse_map.c \
				  check_map.c \
				  ds_queue.c

PARSING_SRCS	= $(addprefix $(PARSING_DIR), $(_PARSING_SRCS))

#ft_func source files
FUNC_DIR		= ft_func/

_FUNC_SRCS	= error_exit.c \
			  file.c \
			  memory.c \
			  lst.c \
			  math.c

FUNC_SRCS	= $(addprefix $(FUNC_DIR), $(_FUNC_SRCS))

#ft_func source files
GNL_DIR		= $(GNL)/

_GNL_SRCS	= get_next_line.c \
			  get_next_line_utils.c

GNL_SRCS	= $(addprefix $(GNL_DIR), $(_GNL_SRCS))

# main source files
SRCS		= main.c 

OBJS		= $(SRCS:%.c=%.o) \
			  $(PARSING_SRCS:%.c=%.o) \
			  $(FUNC_SRCS:%.c=%.o) \
			  $(GNL_SRCS:%.c=%.o)

# define compile commands
$(NAME) : 	$(OBJS) $(LIBFT_LIB)
			cc $(CFLAGS) -o $(NAME) $(OBJS) $(LIBS)

all	:		$(NAME)

$(LIBFT_LIB):
			make bonus -C $(LIBFT)/

%.o	: 		%.c
			cc $(CFLAGS) -c $^ $(HEADERS) -o $@

clean	:
			rm -f $(OBJS)
			make clean -C $(LIBFT)

fclean	:	
			make clean
			rm -f $(NAME)
			make fclean -C $(LIBFT)

re	:		
			make fclean
			make all

.PHONY	:	all clean fclean re