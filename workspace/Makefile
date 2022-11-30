# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: akostrik <akostrik@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/17 13:57:13 by akostrik          #+#    #+#              #
#    Updated: 2022/11/30 22:17:44 by akostrik         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Le Makefile compile ftlib à l’aide de son Makefile, puis compiler le projet

NAME    = get_next_line.a
SRCS    = get_next_line.c get_next_line_utils.c
OBJS    = ${SRCS:.c=.o}
HDRS    = .
CFLAGS  = -Wall -Wextra -Werror -D BUFFER_SIZE=42
CC      = gcc

all: ${NAME}

${NAME}: ${OBJS}

%.o: %.c 
	${CC} ${CFLAGS} -c -o $@ $<

clean:
	rm -f ${OBJS}

fclean: clean
	rm -f ${NAME} 

re: fclean all


.PHONY: all clean fclean re

