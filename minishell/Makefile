SRCS	= $(shell find . -name "minishell_*.c")

OBJS	= ${SRCS:.c=.o}

NAME	= minishell

HEADER	= minishell.h

CC		= gcc

MAKELIB	= make -C ./libft/

MAKEGNL = make -C ./gnl/

RM		= rm -f

CFLAGS	= -Wall -Wextra -Werror

all:	${NAME}

%.o: %.c $(HEADER)
		${CC} ${CFLAGS} -I. -c $< -o ${<:.c=.o}

${NAME}: ${OBJS}
		@${MAKELIB}
		@cp ./libft/libft.a .
		@${MAKEGNL}
		@cp ./gnl/gnl.a . 
		@${CC} ${CFLAGS} ${OBJS} -o ${NAME} -I. libft.a gnl.a

clean:
		${RM} ${OBJS}
		${RM} ./libft/*.o
		${RM} ./gnl/*.o

fclean:	clean
		${RM} ${NAME}
		${RM} ./libft/libft.a
		${RM} ./gnl/gnl.a
		${RM} libft.a
		${RM} gnl.a

re:		fclean all

.PHONY:		re all clean fclean
