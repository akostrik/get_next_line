# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: akostrik <akostrik@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/17 13:57:13 by akostrik          #+#    #+#              #
#    Updated: 2022/11/30 22:13:26 by akostrik         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Le Makefile compile ftlib à l’aide de son Makefile, puis compiler le projet

NAME    = libftprintf.a
SRCS    = get_next_line.c get_next_line_utils.c
OBJS    = ${SRCS:.c=.o}
HDRS    = .
CFLAGS  = -Wall -Wextra -Werror
CC      = gcc

all: ${NAME}

${NAME}: ${OBJS}
	ar rc ${NAME} ${OBJS} 

%.o: %.c 
	${CC} ${CFLAGS} -c -o $@ $< -L./libft -lft 

cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 <files>.c

clean:
	rm -f ${OBJS}

fclean: clean
	rm -f ${NAME} 
	rm -f a.out

re: fclean all


.PHONY: all clean fclean re

