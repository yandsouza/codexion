# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ynascime <yannssouza@outlook.com>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/09/12 12:45:43 by ynascime          #+#    #+#              #
#    Updated: 2026/09/12 13:41:37 by ynascime         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	codexion
SRCS		=	main.c \
				parser/parser.c

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
