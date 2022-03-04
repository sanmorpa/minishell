SRCS =		main.c ft_check.c ft_outils1.c ft_outils2.c ft_commands.c ft_env.c ft_exec.c \
			ft_export.c ft_export_outils.c ft_lst_outils.c ft_unset.c ft_echo.c ft_cd.c

OBJS    =   ${SRCS:.c=.o}

NAME	= 	minishell

CFLAGS	=	-Wall -Wextra -Werror -g3 -fsanitize=address

READ	=	-lreadline #-L /Users/$(USER)/.brew/opt/readline/lib -I /Users/$(USER)/.brew/opt/readline/include

CC		=	gcc

RM		=	rm -f

DIRLIBFT =  ./libft/libft.a

MAKELIBFT = cd ./libft/ && ${MAKE}

MAKELIBFT_B = cd ./libft/ && ${MAKE} bonus

all:		${NAME}

${NAME}:	${OBJS}
			${MAKELIBFT}
			${MAKELIBFT_B}
			${CC} ${CFLAGS} -o ${NAME} ${OBJS} ${DIRLIBFT} ${READ}

clean:
			${RM} ${OBJS}

fclean:		clean
			${RM} ${NAME}
			${MAKELIBFT} fclean

re:			fclean ${NAME}

.PHONY:		all clean fclean re
