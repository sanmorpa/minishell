SRCS =		main.c ./builtins/commands.c ./builtins/echo.c ./builtins/cd.c\
			./builtins/env.c ./builtins/export_outils.c ./builtins/export.c \
			./builtins/unset.c ./builtins/exit.c ./outils/lst_outils.c ./outils/outils1.c \
			./outils/outils.c ./parser/dqt_exception.c ./parser/parser.c \
			./parser/quotes.c ./executer/simple.c ./signals/handler.c ./executer/exec_utils.c ./executer/heredoc.c \
			./parser/parser_aux.c ./parser/split_og.c ./parser/cleaned.c ./parser/clean_comm.c \
			./parser/clean_redirect.c ./executer/heredocs_outils.c ./executer/exec_utils2.c ./parser/clean_outils.c \
			./parser/cleaned_aux.c ./parser/clean_dollars.c ./builtins/builtins_aux.c


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
