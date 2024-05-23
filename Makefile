NAME	:= fdf
CC		:= cc
SRC		:= fdf.c get_next_line/get_next_line.c get_next_line/get_next_line_utils.c
CFLAGS	:= -Wall -Wextra -Werror -g
LIBS	:= libft/libft.a ft_printf/libftprintf.a
OBJ		:= $(SRC:%.c=%.o)

all		: $(NAME)

$(NAME)	: $(OBJ)
	make -C ft_printf all
	make -C libft all
	$(CC) $(OBJ) $(LIBS) -lmlx -lXext -lX11 -lm -o $(NAME)

clean	:
	make -C ft_printf clean
	make -C libft clean
	rm $(OBJ)

fclean	:
	make -C ft_printf fclean
	make -C libft fclean
	rm $(OBJ) $(NAME)

re		: fclean all

.PHONY	: all clean fclean re
