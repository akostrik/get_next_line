# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: akostrik <akostrik@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/17 14:32:35 by akostrik          #+#    #+#              #
#    Updated: 2022/11/30 23:55:01 by akostrik         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = main.c
OBJS = ${SRCS:.c=.o}
CC   = cc

all: ${OBJS}
	clear
	(cd ./workspace && make)
	ld main.o workspace/get_next_line.o workspace/get_next_line_utils.o
	./a.out

%.o: %.c 
	${CC} -c -o $@ $<
	
fclean: clean
	rm -f a.out
	(cd workspace && make fclean)

clean:
	(cd workspace && make clean)

re:
	fclean all