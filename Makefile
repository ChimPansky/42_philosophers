NAME = minishell
CC = cc
CFLAGS = -Wall -Werror -Wextra #-Wpedantic
CFLAGS += -g #-Og -fsanitize=address,undefined,leak
LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a
IFLAGS = -I $(LIBFT_DIR)/include
LFLAGS = -lreadline -L$(LIBFT_DIR) -lft
SOURCE_DIR = src
MS_HEADER = $(SOURCE_DIR)/$(NAME).h

include $(LIBFT_DIR)/colors.mk

MS_FILENAMES = \
	app.c \
	exit_error.c \
	minishell.c \
	prompt.c \
	signals.c

MS_FILENAMES += \
	built_ins/built_in.c \
	built_ins/cd.c \
	built_ins/echo.c \
	built_ins/env.c \
	built_ins/exit.c \
	built_ins/export.c \
	built_ins/pwd.c \
	built_ins/unset.c

MS_FILENAMES += \
	executor/execute_in_child.c \
	executor/execute_on_chain.c \
	executor/executor.c \
	executor/path_finder.c \
	executor/redirections.c

MS_FILENAMES += \
	helpers/rl_wrapper.c \
	helpers/string_utils.c

MS_FILENAMES += \
	lexer/lexer_cmd_seps.c \
	lexer/lexer_redir.c \
	lexer/lexer_subshell.c \
	lexer/lexer_word.c \
	lexer/lexer.c

MS_FILENAMES += \
	parser/expander_utils.c \
	parser/expander_specialisations.c \
	parser/expander.c \
	parser/heredoc_expander.c \
	parser/parser_specialisations.c \
	parser/parser.c \
	parser/wildcards.c

MS_FILENAMES += \
	structures/list_commands.c \
	structures/list_tokens.c \
	structures/list_var_minishell.c \
	structures/list_variables.c \
	structures/redirs.c \
	structures/variable.c

SRC = $(addprefix $(SOURCE_DIR)/,$(MS_FILENAMES))

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(LFLAGS)
	@echo "$(GREEN)Executable $(NAME) created!$(DEF_COLOR)"

$(LIBFT):
	@make -C $(LIBFT_DIR) all clean

lft:
	@make -C $(LIBFT_DIR) all clean

%.o : %.c $(MS_HEADER)
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
