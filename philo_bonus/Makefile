include colors.mk

NAME = philo_bonus
CC = cc
CFLAGS = -Wall -Werror -Wextra
CFLAGS += -g
#CFLAGS += -g -Og -fsanitize=thread
#CFLAGS += -g -Og -fsanitize=address,undefined,leak
LFLAGS = -L$(LIB_ATOMIC_DIR) -l_atomic
LIB_ATOMIC_DIR = lib_atomic
LIB_ATOMIC = $(LIB_ATOMIC_DIR)/lib_atomic.a
SOURCE_DIR = src
OBJ_DIR = objs
PH_HEADERS = $(NAME).h ph_messages.h

PH_FILENAMES = \
	philo_bonus \
	args_validation \
	init_destroy \
	parent_level \
	monitoring \
	child_level \
	routine \
	time \
	utils \
	error_handling

SRC = $(addsuffix .c, $(addprefix $(SOURCE_DIR)/,$(PH_FILENAMES)))
OBJ = $(SRC:.c=.o)

all: $(NAME)

bonus: all

$(NAME): $(OBJ) $(LIB_ATOMIC)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(LFLAGS)
	@echo "$(GREEN)Executable $(NAME) created!$(DEF_COLOR)"

$(LIB_ATOMIC):
	@make -C $(LIB_ATOMIC_DIR) all clean

lib_atomic: $(LIB_ATOMIC)

%.o : %.c $(PH_HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

test1: $(NAME)	# dont eat - just die
	./$(NAME) 1 1000 500 100

test2: $(NAME)	# all live
	./$(NAME) 7 1000 250 250

test3: $(NAME)	# all live
	./$(NAME) 20 2000 990 1000

test4: $(NAME)	# all live
	./$(NAME) 200 2000 99 100

test5: $(NAME)	# all live, eat 7 times and sim stops
	./$(NAME) 7 1000 250 250 7

test6: $(NAME)	# all live, eat 70 times and sim stops
	./$(NAME) 300 2000 80 10 70

test7: $(NAME)	# all live
	./$(NAME) 8 805 400 400

test8: $(NAME)	# some1 dies
	./$(NAME) 8 799 400 400

test9: $(NAME)	# all live
	./$(NAME) 11 1000 330 500

test10: $(NAME)	# all live
	./$(NAME) 150 180 50 50

test11: $(NAME)	# all live
	./$(NAME) 2 102 50 45

kill_all:
	pgrep -f $(NAME) | xargs kill

valgrind:
	valgrind --trace-children=yes --track-origins=yes --leak-check=full --show-leak-kinds=all --track-fds=all ./$(NAME) 8 799 400 400

.PHONY: all bonus clean fclean re kill_all valgrind
