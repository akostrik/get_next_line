# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: akostrik <akostrik@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/17 14:32:35 by akostrik          #+#    #+#              #
#    Updated: 2022/12/05 17:22:55 by akostrik         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS    = main.c workspace/get_next_line.c workspace/get_next_line_utils.c
#OBJS    = ${SRCS:.c=.o}
CC      = cc
BUFSIZE = -D BUFFER_SIZE=5

all: #${OBJS}
	clear
#	(cd ./workspace && make)
	${CC} ${BUFSIZE} ${SRCS}
	./a.out -e

#%.o: %.c 
#	${CC} ${BUFSIZE} -c -o $@ $< 

fclean: clean
	(cd workspace && make fclean)
	rm -f a.out

clean:
	(cd workspace && make clean)
	rm -f ${OBJS}

re:
	fclean a