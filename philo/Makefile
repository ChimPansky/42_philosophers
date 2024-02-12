NAME = philo
CC = cc
CFLAGS = -Wall -Werror -Wextra #-Wpedantic
CFLAGS += -g #-Og -fsanitize=address,undefined,leak
LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a
#IFLAGS = -I include
#IFLAGS = -I $(LIBFT_DIR)/include -I include
SOURCE_DIR = .
OBJ_DIR = objs
PH_HEADERS = $(NAME).h ph_messages.h

include $(LIBFT_DIR)/colors.mk

PH_FILENAMES = \
	philo \
	utils \
	error_handling

MS_FILENAMES += \

SRC = $(addsuffix .c, $(addprefix $(SOURCE_DIR)/,$(PH_FILENAMES)))
OBJ = $(addsuffix .o, $(addprefix $(OBJ_DIR)/,$(PH_FILENAMES)))

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)
	@echo "$(GREEN)Executable $(NAME) created!$(DEF_COLOR)"

$(LIBFT):
	@make -C $(LIBFT_DIR) all clean

lft:
	@make -C $(LIBFT_DIR) all clean

$(OBJ_DIR)/%.o : %.c $(PH_HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

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
