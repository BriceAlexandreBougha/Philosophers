SRC	=	src/main.c              \
        src/init.c              \
        src/do_philosopher.c    \
        src/print_action.c      \
        src/time.c              \
        src/manage_fork.c       \
        src/monitor.c

OBJ	=	$(SRC:.c=.o)

NAME	=	philosophers

CC	=	cc

CFLAGS	=	-Wall -Wextra -Werror

INCLUDE =   include

all:	$(NAME)

%.o:	%.c
	$(CC) $(CFLAGS) -c $< -o $@  -I $(INCLUDE)

$(NAME):	$(OBJ)
	$(CC) -o $(NAME) $(OBJ)

clean:
	find . -name "*~" -name "#*#" -delete
	rm -rf $(OBJ)

fclean:	clean
	rm -rf $(NAME)

re:	fclean	all

.PHONY:	all	clean	fclean