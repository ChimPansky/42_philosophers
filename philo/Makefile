include colors.mk

NAME = philo
CC = cc	# TODO: change this to cc
CFLAGS = -Wall -Werror -Wextra #-Wpedantic
CFLAGS += -g -Og #-fsanitize=thread #-fsanitize=address,undefined,leak
#CFLAGS += -g -Og -fsanitize=address,undefined,leak
LFLAGS = -L$(LIB_ATOMIC_DIR) -l_atomic
LIB_ATOMIC_DIR = lib_atomic
LIB_ATOMIC = $(LIB_ATOMIC_DIR)/lib_atomic.a
#IFLAGS = -I include
#IFLAGS = -I $(LIBFT_DIR)/include -I include
SOURCE_DIR = .
OBJ_DIR = objs
PH_HEADERS = $(NAME).h ph_messages.h

PH_FILENAMES = \
	philo \
	args_validation \
	simulation \
	routine \
	monitoring \
	time \
	utils \
	error_handling

MS_FILENAMES += \

SRC = $(addsuffix .c, $(addprefix $(SOURCE_DIR)/,$(PH_FILENAMES)))
OBJ = $(addsuffix .o, $(addprefix $(OBJ_DIR)/,$(PH_FILENAMES)))

all: $(NAME)

$(NAME): $(OBJ) $(LIB_ATOMIC)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(LFLAGS)
	@echo "$(GREEN)Executable $(NAME) created!$(DEF_COLOR)"

$(LIB_ATOMIC):
	@make -C $(LIB_ATOMIC_DIR) all clean

lib_atomic: $(LIB_ATOMIC)

$(OBJ_DIR)/%.o : %.c $(PH_HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

test1: $(NAME)	# dont eat - just die
	./$(NAME) 1 800 200 200

test2: $(NAME)	# all live TODO: but some1 still dies..
	./$(NAME) 5 800 200 200

test3: $(NAME)	# all live, eat 7 times and sim stops TODO: remove thinking and sleeping logs after last eat
	./$(NAME) 5 800 200 200 7

test4: $(NAME)	# all live
	./$(NAME) 4 410 200 200

test5: $(NAME)	# some1 dies
	./$(NAME) 4 310 200 200

test6: $(NAME)	# all live
	./$(NAME) 11 1000 330 500

valgrind:
	valgrind --trace-children=yes --track-origins=yes --leak-check=full --show-leak-kinds=all --track-fds=all ./$(NAME) 5 800 200 200 7

helgrind:
	valgrind --tool=helgrind ./$(NAME) 4 410 200 200

.PHONY: all bonus clean fclean re test valgrind helgrind
