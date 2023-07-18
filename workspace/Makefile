# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: akostrik <akostrik@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/17 13:57:13 by akostrik          #+#    #+#              #
#    Updated: 2022/12/01 16:31:19 by akostrik         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS    = get_next_line_A.c get_next_line_utils_A.c
OBJS    = ${SRCS:.c=.o}
HDRS    = .

all: get_next_line_A.a

get_next_line_A.a: ${OBJS}
	cc -g $(OBJS) -o get_next_line_A 

%.o: %.c 
	cc -Wall -Wextra -Werror -c -o $@ $<

clean:
	rm -f ${OBJS}

fclean: clean
	rm -f get_next_line_A.a

re: fclean all

.PHONY: all clean fclean re

