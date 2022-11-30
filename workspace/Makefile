# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: akostrik <akostrik@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/17 13:57:13 by akostrik          #+#    #+#              #
#    Updated: 2022/11/30 12:49:12 by akostrik         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Le Makefile compile ftlib à l’aide de son Makefile, puis compiler le projet

NAME    = libftprintf.a
SRCS    = ft_printf.c put_functions.c little_functons.c
OBJS    = ${SRCS:.c=.o}
HDRS    = .
CFLAGS  = -Wall -Wextra -Werror
LIBFT   = libft.a
CC      = gcc

all: ${NAME}

${NAME}: ${LIBFT} ${OBJS}
	ar rc ${NAME} ${OBJS} 

%.o: %.c 
	${CC} ${CFLAGS} -c -o $@ $< -L./libft -lft 

clean:
	rm -f ${OBJS}
	(cd libft && make clean)

fclean: clean
	rm -f ${NAME} 
	rm -f a.out
	(cd libft && make fclean)

re: fclean all

${LIBFT}:
	(cd libft && make)

.PHONY: all clean fclean re

# cc -Wall -Wextra -Werror -c -o ft_printf.o ft_printf.c -L./libft -lft 
# clang: error: -lft: 'linker' input unused [-Werror,-Wunused-command-line-argument]

# gcc -Wall -Wextra -Werror -c -o ft_printf.o ft_printf.c -L./libft -lft 
# OK