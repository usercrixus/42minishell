NAME = minishell

MAKEFLAGS += --no-print-directory

LIBFT_LIB = 42libft.a

OBJS = \
		main.o \
		input/input.o \
		input/commands_array.o \
		input/here_doc.o \
		input/input_array.o \
		input/output_array.o \
		input/special_split.o \
		input/reconstruct_quote.o \
		input/pipe_array.o \
		input/verify_syntax.o \
		input/reconstruct_space.o \
		input/reconstruct_env_var.o \
		input/reconstruct_utils.o \
		pipeline/path.o \
		pipeline/pipeline.o \
		signals/signals.o \
		builtins/export.o \
		builtins/pwd.o \
		builtins/cd.o \
		builtins/cd_utils.o \
		builtins/echo.o \
		builtins/env.o \
		builtins/pwd.o \
		builtins/unset.o \
		builtins/builtin_integration.o \
		builtins/ft_exit.o \
		utils.o \

all: $(LIBFT_LIB) $(NAME)

$(NAME): $(OBJS)
	@echo "\nCOMPILING MINISHELL...\n"
	cc $^ -g3 42libft/ft_base/libft.a 42libft/ft_str/libftstr.a -lreadline -o $@
	@echo "\033[1;32m./minishell created\n"

%.o: %.c
	cc -c $< -Wall -Wextra -Werror -g3 -o $@

$(LIBFT_LIB):
	make -C ./42libft all

clean:
	rm -f $(OBJS)
	make -C ./42libft clean

fclean: clean
	make -C ./42libft fclean
	@echo "\033[0;31mDeleting minishell executable..."
	rm -f minishell
	@echo "\033[0;31mDone."

re: clean fclean all

.PHONY: all clean fclean re 