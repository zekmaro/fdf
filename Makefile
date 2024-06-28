NAME	:= fdf
CC		:= cc
SRC		:=	get_next_line/get_next_line.c \
			get_next_line/get_next_line_utils.c \
			drawing.c \
			fdf.c \
			gradient.c \
			initialisations.c \
			memory_freeing.c \
			parsing.c \
			printing.c \
			rotations.c \
			transformations.c \
			utils.c
CFLAGS	:= -Wall -Wextra -Werror -g
LIBS	:= libft/libft.a ft_printf/libftprintf.a minilibx_macos/libmlx.a
OBJ		:= $(SRC:.c=.o)

all		: $(NAME)

$(NAME)	: $(OBJ) fdf.h
	make -C ft_printf all
	make -C libft all
	$(CC) $(OBJ) $(LIBS) -lmlx -lXext -lX11 -lm -o $(NAME)

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
