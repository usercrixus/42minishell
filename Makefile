MAKEFLAGS += --no-print-directory

OBJS = \
		main.o \
		input/input.o \
		input/commands_array.o \
		input/here_doc.o \
		input/input_array.o \
		input/input.o \
		input/output_array.o \
		input/utils.o \
		input/special_split.o \
		input/reconstruct_quote.o \
		input/special_split_helper.o \
		input/reconstruct_quote_helper.o \
		input/pipe_array.o \
		input/verify_syntax.o \
		pipeline/path.o \
		pipeline/pipeline.o \
		pipeline/utils.o \
		signals/signals.o \
		builtins/export.o \
		builtins/pwd.o \
		builtins/cd.o \
		builtins/echo.o \
		builtins/env.o \
		builtins/pwd.o \
		builtins/unset.o \
		builtins/builtin_integration.o \
		builtins/ft_exit.o \

all: submodule 42libft.a minishell

minishell: $(OBJS)
	cc $^ -g3 42libft/ft_base/libft.a 42libft/ft_str/libftstr.a -lreadline -o $@

%.o: %.c
	cc -c $< -Wall -Wextra -Werror -g3 -o $@

submodule:
	git submodule update --init --recursive

42libft.a:
	make -C ./42libft all

clean:
	rm -f $(OBJS)
	make -C ./42libft clean

fclean: clean
	rm -f minishell
	make -C ./42libft fclean

re: clean fclean all

.PHONY: clean fclean re 42libft.a 