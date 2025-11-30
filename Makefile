CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread

SRC =	src/main.c	\

INCLUDE	=	include

OBJ = $(SRC:.c=.o)

philo: $(OBJ)
    $(CC) $(CFLAGS) -o philo $(OBJ) -I $(INCLUDE)

clean:
    rm -f $(OBJ)

fclean: clean
    rm -f philo

re: fclean philo
