# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/09/14 19:30:25 by mchardin          #+#    #+#              #
#    Updated: 2021/09/19 17:16:32 by mchardin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

PREFIX_INIT	=	./srcs/init/

PREFIX_SCAN =	./srcs/scan/

PREFIX_MLX	=	./srcs/mlx/

INCLUDES	=	./includes/

INCLUDES_L	=	./libft/includes/

SRCS_INIT	=	$(addprefix $(PREFIX_INIT), initialisation.c main.c)

SRCS_SCAN	=	$(addprefix $(PREFIX_SCAN), draw.c utils.c window.c keys.c screenshot.c)

NB_SRCS		=	$(SRCS_INIT) $(SRCS_SCAN)

OBJS		=	${NB_SRCS:.c=.o}

CC			=	clang

CFLAGS		=	-g -Ofast -Wall -Werror -Wextra -I $(INCLUDES) -I $(INCLUDES_L) -I$(PREFIX_MLX) 

RM 			=	rm -f

MAKE_LIBFT	=	$(MAKE) -C./libft/

MAKE_MLX	=	$(MAKE) -C$(PREFIX_MLX)

MLX_SYS		=	-lmlx -lm -lXext -lX11 -L$(PREFIX_MLX) -L/usr/lib/

LIBFT		=	-L./libft/ -lft

NAME		= 	fractol

$(NAME) :		all

makelib :
				$(MAKE_LIBFT)

makemlx :
				$(MAKE_MLX)

all :			./includes/fractol.h $(OBJS) makelib makemlx
				$(CC) $(OBJS) $(MLX_SYS) $(LIBFT) -lm -o $(NAME)

clean :
				$(RM) $(OBJS)
				$(MAKE_LIBFT) clean
				$(MAKE_MLX) clean

fclean :		clean
				$(RM) $(NAME)
				$(MAKE_LIBFT) fclean
				$(MAKE_MLX) clean

re :			fclean all

.PHONY :		makelib makemlx all clean fclean re