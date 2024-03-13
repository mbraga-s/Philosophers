# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mbraga-s <mbraga-s@student.42lisboa.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/11 16:30:40 by mbraga-s          #+#    #+#              #
#    Updated: 2024/03/13 16:01:41 by mbraga-s         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRCS = main utils init threads routine

LIB = $(NAME).a

CC = cc
CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address

RM = rm -fr

all: $(NAME)

$(NAME): $(LIB)
		$(CC) $(CFLAGS) $(LIB) -o $(NAME)

$(LIB): $(SRCS:=.o)
		ar rc $(LIB) $(SRCS:=.o)

clean:
	$(RM)	$(SRCS:=.o)

fclean: clean
		$(RM)	$(NAME) $(NAME).a

re:	fclean	$(NAME)

.PHONY: clean fclean re