all: libft.a libftmath.a libftprintf.a libftstr.a libftgnl.a

libft.a:
	make -C ft_base all

libftmath.a:
	make -C ft_math all

libftprintf.a:
	make -C ft_printf all

libftstr.a:
	make -C ft_str all
	
libftgnl.a:
	make -C ft_gnl all

clean:
	make -C ft_base clean
	make -C ft_math clean
	make -C ft_printf clean
	make -C ft_str clean
	make -C ft_gnl clean

fclean: clean
	make -C ft_base fclean
	make -C ft_math fclean
	make -C ft_printf fclean
	make -C ft_str fclean
	make -C ft_gnl fclean

re: fclean all

.PHONY: all clean fclean re
