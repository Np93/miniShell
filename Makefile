# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rmonney <marvin@42lausanne.ch>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/25 19:09:32 by rmonney           #+#    #+#              #
#    Updated: 2022/05/12 05:07:31 by rmonney          ###   ########.fr        #
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
				ft_cd_tool.c\
				cmd_not_found.c\
				sig_handler.c\
				execve_default.c\
				execve_default2.c\
				welcome1.c\
				welcome2.c\
				ft_termios.c\
				ft_atoi.c\
				ft_itoa.c\
				ft_readline.c\
				launch_redirect.c\
				search_redirect.c\
				search_redirect2.c\
				search_redirect3.c\
				init_redirect.c\
				unquoter.c\
				redirect_utils.c\
				redirecter1and2.c\
				redirecter3.c\
				redirecter5.c\
				ft_strcmp.c\
				ft_putendl_fd.c\
				ft_env2.c\
				redirecter4.c\
				hd_utils.c\
				hd_utils2.c\

OBJS		= ${SRCS:.c=.o}

INCLUDE2	= -lreadline -I${HOME}/.brew/Cellar/readline/8.1.2/include/ -L${HOME}/.brew/Cellar/readline/8.1.2/lib/

INCLUDE		= -lreadline -L${HOME}/.brew/opt/readline/lib -I${HOME}/.brew/opt/readline/lib

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

lldb:
			gcc -g3 ${SRCS} ${INCLUDE} -o ${NAME}
	
.PHONY:		all clean fclean re good docker sani
