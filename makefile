NAME = philo
CC = cc
INCLUDES_DIR = ./includes
INC = -I $(INCLUDES_DIR)
CFLAGS = -Wall -Wextra -Werror $(INC)

RM = rm
RMFLAGS = -f
SRC = src/main.c \
	src/philo_init.c \
	src/philo_utlis.c \
	src/philo.c

OBJ_DIR = obj
OBJ = $(addprefix $(OBJ_DIR)/, $(notdir $(SRC:.c=.o)))

all: $(NAME)

#$(NAME) -> $@
$(NAME): $(OBJ)
	$(CC) $(OBJ) $(LIBFT) -o ${NAME}

$(OBJ_DIR)/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ)

clean:
	$(RM) $(RMFLAGS) ${OBJ}

fclean: clean
	$(RM) $(RMFLAGS) ${OBJ} ${NAME}

re:	fclean all

.PHONY: all clean fclean re
