OBJS = \
	ft_base.o \
	ft_power.o \

all: libftmath.a

libftmath.a: $(OBJS)
	ar rcs $@ $^

%.o: %.c \
	cc -c $< -Wall -Wextra -Werror -g3 -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f libftmath.a

re: fclean all

.PHONY: all clean fclean re
