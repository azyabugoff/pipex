# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sesnowbi <sesnowbi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/07 18:33:46 by sesnowbi          #+#    #+#              #
#    Updated: 2021/07/09 19:28:37 by sesnowbi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= pipex
LIBFT_D	= ./libft
LIBFT_A	= libft.a
LIBFT_H = libft.h
LIBFT	= libft/libft.a

SRCS	= main.c exit_errs.c other_utils.c utils_2dim_arr.c free_utils.c exec_pipe.c exec_bin_pipe.c

INC		= includes/pipex.h
DEPS	= $(INC) $(LIBFT_D)/$(LIBFT_H)
OBJS	= $(SRCS:.c=.o)

CC		= gcc
RM		= /bin/rm -f
CFLAGS	= -g -Wall -Werror -Wextra# -fsanitize=address
FLAGS	= -g -Llibft -lft -Wall -Werror -Wextra# -fsanitize=address

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c $< -include $(INC) -o $(<:.c=.o)

$(NAME):		$(OBJS) $(LIBFT)
					$(CC) $(FLAGS) $(OBJS) -o $(NAME)

all:			$(NAME)

$(LIBFT) :	NONE
				$(MAKE) -C $(LIBFT_D)

clean:
				$(RM) $(OBJS)
				$(MAKE) clean -C $(LIBFT_D)

fclean:			clean
					$(RM) $(NAME)
					$(MAKE) fclean -C $(LIBFT_D)

re:				fclean all

.PHONY:			all clean fclean re NONE
