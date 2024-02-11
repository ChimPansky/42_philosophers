NAME = philosophers
CC = cc
CFLAGS = -Wall -Werror -Wextra #-Wpedantic
CFLAGS += -g #-Og -fsanitize=address,undefined,leak
LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a
IFLAGS = -I $(LIBFT_DIR)/include -I include
SOURCE_DIR = src
PH_HEADER = include/$(NAME).h

include $(LIBFT_DIR)/colors.mk

PH_FILENAMES = \
	philosophers.c

MS_FILENAMES += \

SRC = $(addprefix $(SOURCE_DIR)/,$(PH_FILENAMES))

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(LFLAGS)
	@echo "$(GREEN)Executable $(NAME) created!$(DEF_COLOR)"

$(LIBFT):
	@make -C $(LIBFT_DIR) all clean

lft:
	@make -C $(LIBFT_DIR) all clean

%.o : %.c $(PH_HEADER)
	$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

test: $(NAME)
	bash tests/test_runner.sh

valgrind:
	valgrind --trace-children=yes --track-origins=yes --leak-check=full --show-leak-kinds=all --track-fds=all ./$(NAME)

.PHONY: all bonus clean fclean re test lft
