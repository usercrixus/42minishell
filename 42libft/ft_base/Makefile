OBJS = \
	ft_calloc.o \
	ft_isascii.o \
	ft_itoa.o \
	ft_memcpy.o \
	ft_putchar_fd.o \
	ft_putstr_fd.o \
	ft_strdup.o \
	ft_strlcat.o \
	ft_strncmp.o \
	ft_strtrim.o \
	ft_toupper.o \
	ft_atoi.o \
	ft_isalnum.o \
	ft_isdigit.o \
	ft_memchr.o \
	ft_memmove.o \
	ft_putendl_fd.o \
	ft_split.o \
	ft_striteri.o \
	ft_strlen.o \
	ft_strnstr.o \
	ft_substr.o \
	ft_bzero.o \
	ft_isalpha.o \
	ft_isprint.o \
	ft_memcmp.o \
	ft_memset.o \
	ft_putnbr_fd.o \
	ft_strchr.o \
	ft_strjoin.o \
	ft_strmapi.o \
	ft_strrchr.o \
	ft_tolower.o \
	ft_strlcpy.o \
	ft_split_size.o \

all: libft.a

libft.a: $(OBJS)
	ar rcs $@ $^

%.o: %.c \
	cc -c $< -Wall -Wextra -Werror -g3 -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f libft.a

re: fclean all

.PHONY: all clean fclean re
