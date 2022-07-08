SRCS =		main.c ./builtins/commands.c ./builtins/echo.c ./builtins/cd.c\
			./builtins/env.c ./builtins/export_outils.c ./builtins/export.c \
			./builtins/unset.c ./builtins/exit.c ./outils/lst_outils.c ./outils/outils1.c \
			./outils/outils2.c ./outils/outils.c ./parser/dqt_exception.c \
			./parser/parser.c ./parser/quotes.c ./executer/simple.c ./signals/handler.c \
			

OBJS    =   ${SRCS:.c=.o}

NAME	= 	minishell

CFLAGS	=	-Wall -Wextra -Werror

READ	=	-lreadline

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
			@${MAKELIBFT} fclean

re:			fclean ${NAME}

.PHONY:		all clean fclean re
