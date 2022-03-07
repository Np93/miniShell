# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rmonney <marvin@42lausanne.ch>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/25 19:09:32 by rmonney           #+#    #+#              #
#    Updated: 2022/03/07 17:23:17 by rmonney          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #
SRCS		= 	main.c\
				echo.c\
				ft_strstr.c\
				ft_calloc.c\
				ft_strdup.c\

OBJS		= ${SRCS:.c=.o}

INCLUDE		= -lreadline

RM			= rm -f

NAME		= minishell

FLAGS		= -Wall -Wextra -Werror

CC			= gcc

.c.o:
			${CC} ${FLAGS} -c $< -o ${<:.c=.o}

${NAME}:	${OBJS}
			${CC} ${FLAGS} ${INCLUDE} -o ${NAME} ${OBJS}

all:		${NAME}

clean:
			${RM} ${OBJS}

fclean:		clean
			${RM} ${NAME}

re:			fclean all

.PHONY:		all clean fclean re
