# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ynascime <yannssouza@outlook.com>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/09/12 12:45:43 by ynascime          #+#    #+#              #
#    Updated: 2026/09/13 19:59:07 by ynascime         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	codexion
SRCS		=	main.c \
				parser/parser.c \
				parser/init_data.c \
				threads/start_threads.c \
				simulation/coders.c \
				simulation/manage_dongles.c

OBJS		=   $(SRCS:%.c=%.o)
CC			=   cc
CFLAGS		=   -g -Wall -Wextra -Werror -pthread -I include
HEADER		=   include/codexion.h

all:	$(NAME)

$(NAME):	$(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

%.o:	%.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re:	fclean all

.PHONY: all clean fclean re
