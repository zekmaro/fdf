NAME	:= fdf
CC		:= cc
SRC		:=	fdf.c \
			get_next_line/get_next_line.c \
			get_next_line/get_next_line_utils.c \
			utils.c \
			parsing.c \
			drawing.c \
			initialisation.c 
CFLAGS	:= -Wall -Wextra -Werror -g
LIBS	:= libft/libft.a ft_printf/libftprintf.a minilibx_macos/libmlx.a
OBJ		:= $(SRC:.c=.o)

all		: $(NAME)

$(NAME)	: $(OBJ) fdf.h
	make -C ft_printf all
	make -C libft all
	$(CC) $(OBJ) $(LIBS) -framework OpenGL -framework AppKit -o $(NAME)

clean	:
	make -C ft_printf clean
	make -C libft clean
	rm -f $(OBJ)

fclean	:
	make -C ft_printf fclean
	make -C libft fclean
	rm -f $(OBJ) $(NAME)

re		: fclean all

.PHONY	: all clean fclean re
