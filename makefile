# NAME = philo
# CC = gcc
# INCLUDES_DIR = ./includes
# INC = -I $(INCLUDES_DIR)
# CFLAGS = -Wall -Wextra -Werror $(INC)
# CFLAGS += -g sanitize=thread

# RM = rm
# RMFLAGS = -f
# SRC = src/main.c \
# 	src/philo_init.c \
# 	src/philo_utlis.c \
# 	src/philo.c

# OBJ_DIR = obj
# OBJ = $(addprefix $(OBJ_DIR)/, $(notdir $(SRC:.c=.o)))

# all: $(NAME)

# #$(NAME) -> $@
# $(NAME): $(OBJ)
# 	$(CC) $(OBJ) $(LIBFT) -o ${NAME}

# $(OBJ_DIR)/%.o: src/%.c
# 	$(CC) $(CFLAGS) -c $< -o $@

# $(NAME): $(OBJ)

# clean:
# 	$(RM) $(RMFLAGS) ${OBJ}

# fclean: clean
# 	$(RM) $(RMFLAGS) ${OBJ} ${NAME}

# re:	fclean all

# .PHONY: all clean fclean re

NAME = philo
CC = cc
INCLUDES_DIR = ./includes
INC = -I $(INCLUDES_DIR)
CFLAGS = -Wall -Wextra -Werror $(INC)
# CFLAGS += -g -fsanitize=thread

ifeq ($(CC),gcc)
	CFLAGS += -g -fsanitize=thread
endif
RM = rm
RMFLAGS = -f
SRC = src/main.c \
	  src/philo_init.c \
	  src/philo_utlis.c \
	  src/philo_utlis2.c \
	  src/philo.c \
	  src/all_free.c
OBJ_DIR = obj
OBJ = $(addprefix $(OBJ_DIR)/, $(notdir $(SRC:.c=.o)))

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $@

$(OBJ_DIR)/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(RMFLAGS) $(OBJ)

fclean: clean
	$(RM) $(RMFLAGS) $(NAME)

re: fclean all

.PHONY: all clean fclean re
