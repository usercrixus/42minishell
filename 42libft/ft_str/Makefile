OBJS = \
	ft_str_char_array.o \
	ft_str_creation.o \
	ft_str_push.o \
	ft_str_troncate.o \
	

all: libftbase.a libftstr.a

libftbase.a:
	make -C ../ft_base all

libftstr.a: $(OBJS)
	cp ../ft_base/libft.a $@
	ar rcs $@ $^

%.o: %.c
	cc -c $< -Wall -Wextra -Werror -g3 -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f libftstr.a

re: fclean all

.PHONY: all clean fclean re
