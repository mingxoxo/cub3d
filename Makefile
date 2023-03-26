# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jeongmin <jeongmin@student.42seoul.kr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/04 21:52:18 by wonyang           #+#    #+#              #
#    Updated: 2023/03/26 18:45:38 by jeongmin         ###   ########seoul.kr   #
#                                                                              #
# **************************************************************************** #

# define compile options
NAME		= cub3d
LIBFT		= libft
LIBFT_HEADER = libft.h
LIBFT_LIB	= $(LIBFT)/libft.a

GNL		   = get_next_line
GNL_HEADER = get_next_line.h

MLX		   = mlx_opengl

HEADERS		= -I$(LIBFT) \
			  -I$(GNL)

LIBS		= -lft -L$(LIBFT) -Lmlx_opengl -lmlx -framework OpenGL -framework Appkit

CFLAGS		= -Wall -Werror -Wextra


# parsing part source files
PARSING_DIR		= parsing/

_PARSING_SRCS	= parse.c \
				  parse_info.c \
				  parse_map.c \
				  check_map.c \
				  ds_queue.c \
				  parse_color.c \
				  get_image.c

PARSING_SRCS	= $(addprefix $(PARSING_DIR), $(_PARSING_SRCS))

# render part source files
RENDER_DIR		= render/

_RENDER_SRCS	= init.c \
				  render.c \
				  screen.c \
				  core.c

RENDER_SRCS	= $(addprefix $(RENDER_DIR), $(_RENDER_SRCS))

# ft_func source files
FUNC_DIR		= ft_func/

_FUNC_SRCS	= error_exit.c \
			  file.c \
			  memory.c \
			  lst.c \
			  math.c

FUNC_SRCS	= $(addprefix $(FUNC_DIR), $(_FUNC_SRCS))

# GNL source files
GNL_DIR		= $(GNL)/

_GNL_SRCS	= get_next_line.c \
			  get_next_line_utils.c

GNL_SRCS	= $(addprefix $(GNL_DIR), $(_GNL_SRCS))

# main source files
SRCS		= main.c \
			  init.c \
			  key_press.c \
			  $(PARSING_SRCS) \
			  $(RENDER_SRCS) \
			  $(FUNC_SRCS)


# mandatory bonus
MANDATORY_SRCS	= $(addprefix mandatory/, $(SRCS))
MANDATORY_HEAD	= -Imandatory \
				  $(HEADERS)

_BONUS_SRCS		= $(addprefix bonus/, $(SRCS))
BONUS_SRCS		= $(patsubst %.c, %_bonus.c, $(_BONUS_SRCS)) \
				  bonus/event_bonus.c \
				  bonus/minimap_bonus.c
				  
BONUS_HEAD		= -Ibonus \
				  $(HEADERS)

MANDATORY_OBJS	= $(MANDATORY_SRCS:%.c=%.o)
BONUS_OBJS		= $(BONUS_SRCS:%.c=%.o)
GNL_OBJS		= $(GNL_SRCS:%.c=%.o)

ifdef WITH_BONUS
	OBJ_FILES = $(BONUS_OBJS)
	DELETE_FILES = $(MANDATORY_OBJS)
	HEADER = $(BONUS_HEAD)
else
	OBJ_FILES = $(MANDATORY_OBJS)
	DELETE_FILES = $(BONUS_OBJS)
	HEADER	= $(MANDATORY_HEAD)
endif

# define compile commands
$(NAME) : 	$(OBJ_FILES) $(LIBFT_LIB) $(GNL_OBJS)
			@rm -f $(DELETE_FILES)
			@make -C $(MLX)
			cc $(CFLAGS) -o $(NAME) $(OBJ_FILES) $(GNL_OBJS) $(LIBS)

all	:		$(NAME)

bonus:
			@make WITH_BONUS=1 all

$(LIBFT_LIB):
			make bonus -C $(LIBFT)/

%.o	: 		%.c
			cc $(CFLAGS) -c $^ $(HEADER) -o $@

clean	:
			rm -f $(MANDATORY_OBJS) $(BONUS_OBJS) $(GNL_OBJS)
			make clean -C $(LIBFT)
			make clean -C $(MLX)

fclean	:	
			make clean
			rm -f $(NAME)
			make fclean -C $(LIBFT)

re	:		
			make fclean
			make all

.PHONY	:	all clean fclean re bonus
