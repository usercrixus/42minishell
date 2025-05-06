NAME = minishell

MAKEFLAGS += --no-print-directory

LIBFT_LIB = srcs/42libft.a

OBJS = \
		srcs/main.o \
		srcs/input/input.o \
		srcs/input/commands_array.o \
		srcs/input/here_doc.o \
		srcs/input/input_array.o \
		srcs/input/output_array.o \
		srcs/input/special_split.o \
		srcs/input/reconstruct_quote.o \
		srcs/input/pipe_array.o \
		srcs/input/verify_syntax.o \
		srcs/input/reconstruct_space.o \
		srcs/input/reconstruct_env_var.o \
		srcs/input/reconstruct_utils.o \
		srcs/pipeline/path.o \
		srcs/pipeline/pipeline.o \
		srcs/signals/signals.o \
		srcs/builtins/export.o \
		srcs/builtins/pwd.o \
		srcs/builtins/cd.o \
		srcs/builtins/cd_utils.o \
		srcs/builtins/echo.o \
		srcs/builtins/env.o \
		srcs/builtins/pwd.o \
		srcs/builtins/unset.o \
		srcs/builtins/builtin_integration.o \
		srcs/builtins/ft_exit.o \
		srcs/utils/utils.o \

all: $(LIBFT_LIB) $(NAME)

$(NAME): $(OBJS)
	cc $^ -g3 srcs/42libft/ft_base/libft.a srcs/42libft/ft_str/libftstr.a -lreadline -o $@

%.o: %.c
	cc -c $< -Wall -Wextra -Werror -g3 -o $@

$(LIBFT_LIB):
	make -C srcs/42libft all

clean:
	rm -f $(OBJS)
	make -C srcs/42libft clean

fclean: clean
	make -C srcs//42libft fclean
	rm -f minishell

re: clean fclean all

.PHONY: all clean fclean re 