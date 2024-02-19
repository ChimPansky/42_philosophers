include colors.mk

NAME = lib_atomic
CC = cc
CFLAGS = -Wall -Werror -Wextra #-Wpedantic
 CFLAGS += -g -Og #-fsanitize=address,undefined,leak
CFLAGS += -g
INCLUDE_DIR = ./
HEADER = $(INCLUDE_DIR)lib_atomic.h

SRC_FILES = ft_atomic_fetch \
			ft_atomic_init \
			ft_atomic_destroy \
			ft_atomic_load \
			ft_atomic_store

SRC = $(addsuffix .c, $(SRC_FILES))

OBJ = $(SRC:.c=.o)

$(NAME): $(OBJ) $(HEADER)
	ar -rs $(NAME).a $(OBJ)
	@echo "$(GREEN)Library $(NAME).a created!$(DEF_COLOR)"

%.o : %.c $(HEADER)
	$(CC) -I $(INCLUDE_DIR) $(CFLAGS) -c $< -o $@

all: $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME).a

re: fclean all

.PHONY: all clean fclean re
