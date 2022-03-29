# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rmonney <marvin@42lausanne.ch>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/25 19:09:32 by rmonney           #+#    #+#              #
#    Updated: 2022/03/29 20:11:24 by rmonney          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #
SRCS		= 	main.c\
				search_fct.c\
				ft_echo.c\
				ft_strstr.c\
				ft_calloc.c\
				ft_strdup.c\
				ft_env.c\
				ft_pwd.c\
				ft_split.c\
				ft_strjoin.c\
				init.c\
				current_parser.c\
				current_parser2.c\
				error_handler.c\
				ft_cd.c\
				cmd_not_found.c\
				sig_handler.c\
				execve_default.c\
				execve_default2.c\
				welcome1.c\
				welcome2.c\
				ft_termios.c\
				ft_atoi.c\
				ft_itoa.c\

OBJS		= ${SRCS:.c=.o}

INCLUDE		= -lreadline -I${HOME}/.brew/Cellar/readline/8.1.1/include/ -L${HOME}/.brew/Cellar/readline/8.1.1/lib/

RM			= rm -f

SAN 		= -fsanitize=address

NAME		= minishell

DNAME		= dockedshell

FLAGS		= -Wall -Wextra -Werror

DFLAG		= -fcommon

CC			= gcc

.c.o:
			${CC} ${FLAGS} -c $< -o ${<:.c=.o}

${NAME}:	${OBJS}
			${CC} ${FLAGS} ${INCLUDE} -o ${NAME} ${OBJS}

all:		${NAME}

clean:
			${RM} ${OBJS}

fclean:		clean
			${RM} ${NAME} ${DNAME}

re:			fclean all

good:		${NAME} clean

sani:		${OBJS}
			${CC} ${FLAGS} ${SAN} ${INCLUDE} -o ${NAME} ${OBJS}

docker:
			${CC} ${DFLAG} ${FLAGS} ${SAN} ${INCLUDE} ${SRCS} -o ${DNAME}

.PHONY:		all clean fclean re good docker sani
