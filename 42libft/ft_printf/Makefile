OBJS = \
	ft_printf.o \
	ft_print_hex.o \
	ft_print_str.o \
	ft_print_char.o \
	ft_print_dec.o \

all: libftprintf.a

libftprintf.a: ./../ft_base/libft.a $(OBJS)
	# Combine libft.a and ftprintf objects into libftprintf.a
	cp ../ft_base/libft.a libftprintf.a
	ar rcs libftprintf.a $(OBJS)

./../ft_base/libft.a:
	make -C ../ft_base all

%.o: %.c
	cc -c $< -Wall -Wextra -Werror -g3 -o $@

clean:
	rm -f $(OBJS)
	make -C ./../ft_base clean

fclean: clean
	rm -f libftprintf.a test.out
	make -C ./../ft_base fclean

re: fclean all

.PHONY: all clean fclean re
